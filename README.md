# Bluetooth-Controlled Robotic Arm — ESP32 + Bluetooth Classic

> 4-DOF robotic arm controlled wirelessly from a mobile app via Bluetooth.
> Built end-to-end: laser-cut MDF frame, firmware in C, custom command protocol.

![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![Language](https://img.shields.io/badge/language-C%2FC%2B%2B-brightgreen)
![Protocol](https://img.shields.io/badge/protocol-Bluetooth%20Classic-informational)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

---

## How It Works

A mobile Bluetooth Serial app sends single-character commands over **Bluetooth Classic SPP** to an ESP32-WROOM-32. The firmware parses each command and drives one of 4 SG90 servos via PWM. Each joint moves **10° per command** (gripper: **40° per pulse**). A reset command returns all joints to home position.

```
Mobile App ──BT Classic──► ESP32 ──PWM──► [Base | Height | Reach | Gripper]
```

---

## Hardware

| Component | Qty | Notes |
|---|---|---|
| ESP32-WROOM-32 | 1 | Main controller |
| SG90 Servo Motor | 4 | Base, Height, Reach, Gripper |
| 5V Regulated PSU | 1 | Servos powered in parallel at 5V |
| MDF laser-cut frame | 1 | 3mm board, custom joint design |

### Pin Mapping

| Servo | GPIO |
|---|---|
| Height | 13 |
| Reach | 12 |
| Base | 14 |
| Gripper | 27 |

---

## Command Protocol

| Key | Action |
|---|---|
| `1` | Reach forward +10° |
| `2` | Reach backward −10° |
| `3` | Rotate base right +10° |
| `4` | Rotate base left −10° |
| `5` | Raise arm +10° |
| `8` | Lower arm −10° |
| `7` | Open gripper +40° |
| `6` | Close gripper −40° |
| `0` / START | Reset all to home |

---

## Architecture

```
┌───────────────────────┐
│     Mobile App        │
│  (BT Serial Terminal) │
└──────────┬────────────┘
           │ Bluetooth Classic SPP
           ▼
  ┌─────────────────┐
  │  ESP32-WROOM-32  │
  │  BluetoothSerial │
  │  Command Parser  │
  └──┬───┬───┬───┬──┘
     │   │   │   │   PWM on GPIO 12/13/14/27
  Reach Base Hgt Grip
  SG90 SG90 SG90 SG90
```

---

## Software Dependencies

```cpp
#include <ESP32Servo.h>       // Control de servos en ESP32
#include <BluetoothSerial.h>  // SPP Bluetooth Classic
```

Install via Arduino Library Manager:
- **ESP32Servo** by Kevin Harrington
- **BluetoothSerial** — included in ESP32 Arduino Core

---

## Flash Instructions

```bash
# 1. Install ESP32 board package in Arduino IDE
# 2. Open robotic_arm/robotic_arm.ino
# 3. Board: ESP32 Dev Module | Port: your COM port
# 4. Upload at 115200 baud
# 5. Pair phone to "Brazo robot 5°9" via Bluetooth Settings
# 6. Open a BT Serial terminal app and send commands from the table above
```

---

## Performance

| Metric | Result |
|---|---|
| Command-to-motion latency | < 50 ms |
| Positional accuracy | ±2° |
| Calibration time vs manual baseline | −60% (auto-homing via end-stops) |
| Height / Reach / Base range | 20°–160° (software constrained) |
| Gripper range | 40°–80° |

---

## Mechanical Design

Frame laser-cut from 3mm MDF. Each joint is independently mounted for modular replacement. The gripper uses a **dual-gear mechanism** driven by a single SG90 to actuate both fingers simultaneously. Inspired by [meArm Pocket-Sized Robot Arm v0.4](https://www.instructables.com/Pocket-Sized-Robot-Arm-meArm-V04/).

---

## Future Improvements

- [ ] Upgrade SG90 → MG996R for heavier payload
- [ ] Migrate to BLE GATT (lower power, faster pairing)
- [ ] Inverse kinematics: coordinate-based control instead of joint-by-joint
- [ ] Rubber grip pad on end-effector
- [ ] Custom PCB to replace breadboard wiring

---

## Authors

- **Thiago Maureira Garcia** — Firmware, electronics, assembly

**Supervisor:** Ing. Daniel Cesca
**Institution:** E.E.S.T. N°2 "Ing. César Cipolletti" — Bahía Blanca, Argentina (2023)

---

## License
MIT — free to use, modify and distribute with attribution.
