<script lang="ts">
  import FrontFace from "$lib/components/preview/front-face.svelte";
  import {
    ESPLoader,
    Transport,
    type FlashOptions,
    type LoaderOptions,
  } from "esptool-js";
  import * as xterm from "@xterm/xterm";
  import "@xterm/xterm/css/xterm.css";
  import { slide } from "svelte/transition";
  import { tick } from "svelte";
  import { base } from "$app/paths";
  import bootImg from "./arduino-bootLabel.jpeg";

  const { Terminal } = xterm;

  const { data } = $props();

  let terminal: HTMLDivElement;
  let term: Terminal;

  let screenType: "" | "BW" | "BWR" = $state("");
  let downloadURL = $derived(`${base}/device/firmware/${screenType}/`);

  const espLoaderTerminal = {
    clean() {
      term.clear();
    },
    writeLine(data: string) {
      term.writeln(data);
    },
    write(data: string) {
      term.write(data);
    },
  };
  $effect(() => {
    term = new Terminal({ rows: 30 });
    if (!terminal) return;
    term.open(terminal);
  });

  let device: SerialPort | undefined;
  let transport: Transport | undefined;
  let chip: string | null = null;
  let esploader: ESPLoader;

  let isConsoleClosed = $state(true);
  async function startConsole() {
    isConsoleClosed = false;
    await tick();
    if (device === undefined) {
      device = await navigator.serial.requestPort({});
      transport = new Transport(device, true);
    }
    await transport.connect(115200);

    while (true && !isConsoleClosed) {
      const val = await transport.rawRead();
      if (typeof val !== "undefined") {
        term.write(val);
      } else {
        break;
      }
    }
  }

  function cleanUp() {
    device = undefined;
    transport = undefined;
    chip = null;
  }

  const stopConsole = async () => {
    isConsoleClosed = true;
    if (transport) {
      await transport.disconnect();
      await transport.waitForUnlock(1500);
    }
    term.reset();
    cleanUp();
  };

  let progress = $state(0);

  const bufferToString = (buffer: ArrayBuffer) => {
    const bytes = new Uint8Array(buffer);
    return bytes.reduce(
      (string, byte) => string + String.fromCharCode(byte),
      ""
    );
  };

  async function updateFirmware() {
    if (!screenType) {
      alert("Please select a screen type");
      return;
    }
    progress = 1;
    // Download latest firmware
    const response = await fetch(downloadURL);
    if (!response.ok) {
      alert("Failed to download firmware");
      return;
    }
    const firmware = await response.arrayBuffer();
    progress = 15;
    if (device === undefined) {
      device = await navigator.serial.requestPort({});
      transport = new Transport(device, true);
    }
    progress = 20;
    try {
      isConsoleClosed = false;
      const loaderOpts = {
        transport,
        baudrate: 115200,
        terminal: espLoaderTerminal,
        debugLogging: true,
      } as LoaderOptions;
      esploader = new ESPLoader(loaderOpts);

      chip = await esploader.main();
      progress = 45;

      // Temporarily broken
      // await esploader.flashId();

      const flashOptions: FlashOptions = {
        fileArray: [
          {
            data: bufferToString(firmware),
            address: 0x0,
          },
        ],
        flashSize: "keep",
        flashMode: "dio",
        flashFreq: "80m",
        eraseAll: false,
        compress: true,
        reportProgress: (_fileIndex, written, total) => {
          progress = 50 + (written / total) * 50;
        },
      } as FlashOptions;
      await esploader.writeFlash(flashOptions);
    } catch (e: any) {
      console.error(e);
      term.writeln(`Error: ${e.message}`);
    }
  }
</script>

<FrontFace page={0} live={true} userData={data.user} />

<div class="flex flex-col items-center gap-4">
  <div class="font-sans prose w-full max-w-screen-md">
    <p>
      Welcome to the RSB device update tool! You can use this to install the
      latest version. <strong
        >Heads up: you should only do this if your device isn't working, or
        there's an update you know about.</strong
      > To get started:
    </p>
    <ol class="list-decimal list-inside mt-4 mx-4 flex flex-col gap-3">
      <li>
        Find out whether your device uses a black and white or black, white, and
        red display, and set the dropdown below. <strong
          >Not sure? If your device spends 20 seconds flashing the screen when
          you turn it on, it's black+white+red.</strong
        >
      </li>
      <li>
        Open the case of your device, and pull out the circuit board that the
        USB plugs into
      </li>
      <li>
        Find the tiny little button to the right of the USB port - you will need
        this in a couple steps:
        <img
          src={bootImg}
          alt="Illustration of where the button is"
          class="max-w-sm mx-auto"
        />
      </li>
      <li>Plug the device into your computer's USB port</li>
      <li>Click "Update to latest" below</li>
      <li>
        When the message "https://rsb.nz/ wants to connect to a serial port"
        appears, select the device with a name starting with "CP2102 USB TO
        UART..." but DO NOT click connect.
      </li>
      <li>
        <strong
          >Hold down the tiny button you found earlier, and click connect</strong
        >
      </li>
      <li>
        Wait for the progress bar to finish and the device to make a noise, then
        unplug! You're done.
      </li>
    </ol>
    <p class="mt-4">
      <strong
        >Hearing one high beep then two lows, and is the screen not updating?
        Make sure all the wires are securely plugged into the circuit board you
        pulled out. The display might be loose!</strong
      >
    </p>
  </div>
  <div class="deviceOptions">
    <select
      bind:value={screenType}
      class="select select-bordered w-full max-w-xs"
    >
      <option value="" disabled selected>Screen Type?</option>
      <option value="BW">Black and White</option>
      <option value="BWR">Black White Red</option>
    </select>
  </div>
  <div class="flex gap-2">
    <button class="btn btn-primary" onclick={updateFirmware}
      >Update to Latest</button
    >
    <button
      class="btn btn-primary flex-col"
      onclick={isConsoleClosed ? startConsole : stopConsole}
    >
      <div>{isConsoleClosed ? "View" : "Hide"} Console</div>
      <div class="text-sm">(for troubleshooting)</div>
    </button>
  </div>
</div>
{#if progress > 0}
  <progress
    transition:slide
    class="progress w-full [&::-webkit-progress-value]:transition-all"
    value={progress}
    max="100"
  ></progress>
{/if}

<div transition:slide class:hidden={isConsoleClosed}>
  <div bind:this={terminal}></div>
</div>
