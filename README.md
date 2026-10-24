# VL53L0X I2C Template and Breakout Board

This repository contains reference material for a VL53L0X time-of-flight sensor breakout board and a reusable, transport-agnostic C module for communicating with a sensor device over I2C.

The template provides a host-side interface for the command protocol implemented by the target device firmware. It is not a drop-in replacement for ST's native VL53L0X API; confirm that your device firmware uses the command and ranging-frame format expected by this module.

## Contents

- [`vl53l0x_template.h`](vl53l0x_template.h) and [`vl53l0x_template.c`](vl53l0x_template.c): reusable C API and implementation.
- [`vl53l0x_template_demo.c`](vl53l0x_template_demo.c): one-shot, continuous, and multi-device demonstration helpers.
- [`example_main.c`](example_main.c): PSoC Creator I2C integration example.
- [`breakout schematics.pdf`](breakout%20schematics.pdf): breakout board schematic.
- [`images/`](images/): board and multi-sensor setup images.

## Board Overview

The breakout exposes power and I2C through connector J1. It has onboard weak 10 kOhm I2C pull-ups; cut jumpers J2 and J3 if using external pull-ups.

### J1 connector pins

| Pin | Connection |
| --- | --- |
| 1 (square) | VDD, 3 V to 5.5 V |
| 2 | SDA |
| 3 | SCL |
| 4 | NU |
| 5 | GND |

### Board images

![Breakout board back](images/breakout%20brd%20back.jpg)
![Breakout board front](images/breakout%20brd%20front.jpg)
![Multiple sensors on the same I2C bus](images/multiple%20sensors%20on%20the%20same%20I2C%20bus.jpeg)

## Quick Start

1. Add `vl53l0x_template.h` and `vl53l0x_template.c` to your C project.
2. Implement the I2C read and write callbacks for your platform. Return `0` on success and a nonzero value on failure.
3. Optionally provide a millisecond delay callback.
4. Fill a `vl53l0x_template_cfg_t` with the callbacks and polling configuration, then call `vl53l0x_template_init`.
5. Use the measurement or command functions with the device's I2C address.

See [`example_main.c`](example_main.c) for a PSoC Creator integration example.

## API Highlights

- `vl53l0x_template_get_measurement` and `vl53l0x_template_get_measurements`
- `vl53l0x_template_read_ranging_frame`
- `vl53l0x_template_set_new_address`
- `vl53l0x_template_set_ranging_timing`
- `vl53l0x_template_start_offset_cal` and `vl53l0x_template_start_xtalk_cal`
- `vl53l0x_template_set_vcsel_periods`
- `vl53l0x_template_status_text` and `vl53l0x_template_convert_range`

The parsed measurement includes range, status, signal and ambient rates, ambient and signal rates per SPAD, and SPAD count. The template supports ranges in millimeters, centimeters, or inches.
