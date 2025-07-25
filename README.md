# 🤖 Motion-Triggered Welcome System using LPC1768

A simple embedded project using the **LPC1768 microcontroller**, **IR proximity sensor**, **PWM-controlled LED**, and a **16x2 LCD display**. When motion is detected (like a hand wave), the system brightens the LED and displays a **WELCOME** message on the LCD.

---

## 🧠 How It Works

- An **IR Sensor** detects motion (presence of a hand).
- When motion is detected:
  - A **PWM-controlled LED** gradually brightens.
  - A **WELCOME** message is shown on the **LCD**.
- When motion stops:
  - The LED dims gradually.
  - The LCD is cleared.

---

## 🔧 Hardware Requirements

| Component             | Description                             |
|----------------------|-----------------------------------------|
| **LPC1768**           | ARM Cortex-M3 Microcontroller board     |
| **16x2 LCD**          | Display module for messages             |
| **IR Proximity Sensor** | Detects presence of hand/motion        |
| **LED**               | Indicates motion via brightness         |
| **Resistors**         | For current limiting (LED)              |
| **Breadboard + Jumper Wires** | For circuit connection          |
| **Power Supply (5V)** | Via USB or external source              |

---

## 📌 Pin Configuration (LPC1768)

| Pin       | Purpose                  |
|-----------|--------------------------|
| P0.8      | Input from IR sensor     |
| P1.23     | PWM1.4 output to LED     |
| P0.23–26  | LCD data lines (D4–D7)   |
| P0.27     | LCD RS (Register Select) |
| P0.28     | LCD EN (Enable)          |

---

## 🛠️ Software Requirements

- [Keil uVision 4/5](https://www.keil.com/)
- CMSIS library for LPC17xx
- Flash Magic (or equivalent for programming the board)

---


