# 🌊 Automatic Flood Warning and Gate Control System

An Arduino-based system that monitors water levels in real time and automatically triggers a warning alarm and opens a flood gate when water exceeds a safe threshold.

---

## 📌 Features

- Reads water level from an analog sensor
- Averages 10 readings to reduce noise and false triggers
- Visual alert via **Green** and **Red LEDs**
- Audible **buzzer alarm** (3-second beep sequence)
- **Servo motor** simulates automatic flood gate opening/closing
- Self-resetting — no user interaction required
- Live readings via **Serial Monitor**

---

## 🛠️ Hardware Required

| Component              | Quantity |
|------------------------|----------|
| Arduino Uno            | 1        |
| Water Level Sensor     | 1        |
| Servo Motor (SG90/MG90S) | 1      |
| Green LED              | 1        |
| Red LED                | 1        |
| 220Ω Resistor          | 2        |
| Active/Passive Buzzer  | 1        |
| Breadboard             | 1        |
| Jumper Wires           | As needed |
| USB Cable              | 1        |

---

## ⚡ Wiring

| Component              | Arduino Pin |
|------------------------|-------------|
| Water Sensor (Signal)  | A0          |
| Water Sensor (VCC)     | 5V          |
| Water Sensor (GND)     | GND         |
| Green LED              | D6          |
| Red LED                | D7          |
| Buzzer                 | D8          |
| Servo (Signal)         | D9          |
| Servo (VCC)            | 5V          |
| Servo (GND)            | GND         |

> **Note:** If the servo causes the Arduino to reset or stutter, power it from an external 5V supply with a shared GND.

---

## 📚 Library Required

- **Servo.h** — Built into the Arduino IDE, no installation needed.

---

## 🚀 Getting Started

1. Wire the components as shown in the wiring table above.
2. Open the `.ino` file in **Arduino IDE**.
3. Connect your Arduino Uno via USB.
4. Select the correct **Board** and **Port** under `Tools`.
5. Click **Upload**.
6. Open **Serial Monitor** at `9600 baud` to view live water level readings.

---

## ⚙️ How It Works

```
Sensor reads water level (average of 10 samples)
            │
     waterLevel >= 500?
       ┌────┴────┐
      YES        NO
       │          │
  Green LED ON   Red LED ON
  Red LED OFF    Green LED OFF
  Buzzer alarm   Gate closes (if open)
  Gate opens
```

| Condition         | Green LED | Red LED | Buzzer   | Servo     |
|-------------------|-----------|---------|----------|-----------|
| Water < 500       | OFF       | ON      | Silent   | 0° Closed |
| Water ≥ 500       | ON        | OFF     | 3s Alarm | 90° Open  |
| Water drops again | OFF       | ON      | Silent   | 0° Closed |

The system uses a `gateOpen` flag to ensure the buzzer and servo trigger **only once per flood event**, not on every loop cycle.

---

## 📟 Serial Monitor Output

```
Water Level: 312
Water Level: 497
Water Level: 503    ← Flood triggered
Water Level: 489
Water Level: 290    ← Gate closing
```

---

## 🎛️ Calibration

The default flood threshold is `500`. To adjust it for your sensor:

1. Open Serial Monitor and observe readings with the sensor **dry** (typically < 50).
2. Submerge the sensor to your **target water level** and note the reading.
3. Set a threshold between the two values by editing this line in the code:

```cpp
if (waterLevel >= 500)  // ← change 500 to your calibrated value
```

---

## 📁 Project Structure

```
flood-warning-system/
├── flood_warning_system.ino   # Main Arduino sketch
└── README.md                  # This file
```

---

## 🔮 Possible Upgrades

- Add an **I2C LCD** to display live readings and status
- Replace blocking `delay()` with `millis()` for non-blocking operation
- Integrate **ESP8266/ESP32** for Wi-Fi alerts or cloud monitoring
- Add a **GSM module** (SIM800L) for SMS flood notifications
- Use an **HC-SR04 ultrasonic sensor** for non-contact, corrosion-free measurement

---

## 👤 Author

**Mandeep Kafle**
BIT Student — Bhaktapur Multiple Campus
GitHub: [Mandeep21ss](https://github.com/Mandeep21ss)

---

## 📄 License

This project is open-source and free to use for educational purposes.
