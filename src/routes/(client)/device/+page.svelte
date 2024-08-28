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
