<script lang="ts">
  import FrontFace from "$lib/components/preview/front-face.svelte";
  import { ESPLoader, Transport, type LoaderOptions } from "esptool-js";
  import * as xterm from "@xterm/xterm";
  import "@xterm/xterm/css/xterm.css";
  import { slide } from "svelte/transition";
  import { tick } from "svelte";

  const { Terminal } = xterm;

  const { data } = $props();

  let terminal: HTMLDivElement;
  let term: Terminal;

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
  async function console() {
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

  async function updateFirmware() {
    if (device === undefined) {
      device = await navigator.serial.requestPort({});
      transport = new Transport(device, true);
    }
    try {
      isConsoleClosed = false;
      const flashOptions = {
        transport,
        baudrate: 115200,
        terminal: espLoaderTerminal,
        debugLogging: true,
      } as LoaderOptions;
      esploader = new ESPLoader(flashOptions);

      chip = await esploader.main();

      // Temporarily broken
      // await esploader.flashId();
    } catch (e) {
      console.error(e);
      term.writeln(`Error: ${e.message}`);
    }
  }
</script>

<FrontFace page={0} live={true} userData={data.user} />

<button class="btn btn-primary mt-4" onclick={updateFirmware}
  >Update to Latest</button
>
<button
  class="btn btn-primary mt-4"
  onclick={isConsoleClosed ? console : stopConsole}
  >{isConsoleClosed ? "View" : "Hide"} Console</button
>
<div transition:slide class:hidden={isConsoleClosed}>
  <div bind:this={terminal}></div>
</div>
