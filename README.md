# EspressoGameBox

> **Hand‑held multi‑game console powered by ESP32‑WROOM‑32E & ILI9341 TFT**

[![License: MIT + Attribution](https://img.shields.io/badge/license-MIT%2BAttribution-blue.svg)](LICENSE)

EspressoGameBox is a hobby project that turns an **ESP32‑WROOM‑32E**, an **ILI9341 TFT display**, tactile switches and an SD card into a tiny “download‑software” style game machine—think *Nintendo 3DS* e‑shop titles, but DIY.  It stores a lightweight menu/OS in flash while individual game binaries live on the SD card, so you can swap, add or remove titles without reflashing firmware.

> **Note:** I'm **LandedCoyote**, an entry‑level maker who began electronics and programming in 2024. English is not my first language and I'm still learning, so some sentences may sound a bit unusual—please bear with me! Development progresses whenever time allows, and feedback or pull requests are always welcome!

---

## Table of Contents

1. [Features](#features)
2. [Hardware](#hardware)
3. [Project Status](#project-status)
4. [Getting Started](#getting-started)
5. [Directory Layout](#directory-layout)
6. [Contributing](#contributing)
7. [License](#license)
8. [Acknowledgements](#acknowledgements)

---

## Features

* **Menu OS stored in flash** – choose games with a simple GUI rendered at 60 fps.
* **SD‑card game library** – drop compiled game files (`*.bin`) into `/games/` and they appear automatically.
* **Tactile‑switch controls** – D‑pad + buttons mapped via GPIO; debounce handled in software.
* **PCM sound playback** – tiny speaker driven by the built‑in DAC (planned).
* **Pluggable game API** – lightweight C/C++ interface so new games can target the box with minimal boilerplate (WIP).

## Hardware

| Part    | Example                                       | Notes                                    |
| ------- | --------------------------------------------- | ---------------------------------------- |
| MCU     | ESP32‑WROOM‑32E                               | 240 MHz dual‑core, Wi‑Fi/BLE             |
| Display | 2.4–2.8” ILI9341 TFT                          | SPI 40 MHz, 320 × 240                    |
| Storage | micro‑SD card module                          | FAT32                                    |
| Input   | 4× tactile switch (D‑pad) + 2× action buttons | Pull‑up resistors recommended            |
| Audio   | Small 8 Ω speaker                             | Driven via 1‑bit DAC / PWM + RC low‑pass |
| Power   | Li‑ion 3.7 V w/ boost to 5 V                  | or USB‑C 5 V                             |

*Schematic & KiCad files will be provided in `/hardware/` (work in progress).*

## Project Status

| Area                      | State                                  |
| ------------------------- | -------------------------------------- |
| Bootloader & menu OS      | ✅ Prototype boots and lists SD entries |
| Graphics driver (ILI9341) | ✅ Custom SPI driver, DMA blit engine   |
| Game API / SDK            | 🔄 Drafting headers                    |
| Audio playback            | ⏳ Not started                          |
| KiCad PCB                 | ⏳ Not started                          |
| Documentation             | 🔄 This README                         |

Overall status: **alpha** – usable for experimentation, not feature‑complete.

## Getting Started

> ⚠️ *Build & flash procedure is under construction; steps may change.*

```bash
# 1. Clone repository
$ git clone https://github.com/<your-github>/EspressoGameBox.git
$ cd EspressoGameBox

# 2. Install ESP‑IDF (v5.x) and add to PATH
$ . "$HOME/esp/esp-idf/export.sh"

# 3. Configure (select serial port, etc.)
$ idf.py menuconfig

# 4. Build & flash
$ idf.py flash monitor
```

Insert an SD card containing a `/games/` folder with compiled `*.bin` titles; the menu will discover and launch them.

### Dependencies

* **ESP‑IDF 5.x** (Arduino‑ESP32 core ≥ 3.0 will be supported later)
* Python 3.10+, CMake, Ninja

## Directory Layout

```text
EspressoGameBox/
├── firmware/      # ESP32 source (menu OS + libs)
│   ├── components/
│   └── main/
├── games/         # Sample game sources / binaries
├── hardware/      # KiCad schematics & PCB (TBD)
├── docs/          # Additional design docs
└── LICENSE
```

## Contributing

Pull requests, issues and feature suggestions are welcome!
Because this is the maintainer’s first multi‑person project, please:

1. **Open an issue first** to discuss major changes.
2. Follow the style guide in `CONTRIBUTING.md` (to be written).
3. Use clear commit messages (English preferred).
4. Keep PRs small and focused.

Beginners are encouraged—look for the `good first issue` label.

## License

This project is distributed under the **MIT License with Attribution**.

> You may use, modify and redistribute the source and derivatives, including commercial use, **provided that you:(1) include a link to this repository, and (2) credit “LandedCoyote” as the original author** in your README or documentation.

**Example credit snippet:**

```text
Based on EspressoGameBox by LandedCoyote (https://github.com/LandedCoyote/EspressoGameBox)
```

See the [LICENSE](LICENSE) file for the full text.

## Acknowledgements

* Espressif for the ESP-IDF
* All OSS libraries referenced under `/firmware/components/` (see their individual licenses)

---

*Happy hacking & enjoy a fresh shot of EspressoGameBox!*
