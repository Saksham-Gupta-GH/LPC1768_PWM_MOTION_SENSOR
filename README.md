# LPC1768_PWM_MOTION_SENSOR
# 🤖 Motion-Triggered Welcome System using LPC1768

A simple embedded project that uses an **IR sensor**, **PWM-controlled LED**, and **16x2 LCD** to detect motion (like a hand waving), brighten an LED, and display a **WELCOME** message on the LCD.

---

## 📸 Demo

![Hardware Setup](images/hardware_setup.png)
*Image of actual circuit setup (optional)*

---

## 🧠 How It Works

- **IR Sensor** detects the presence of a hand (active LOW).
- If motion is detected:
  - LED gradually brightens using **PWM**.
  - LCD displays **"WELCOME"**.
- If no motion:
  - LED dims gradually.
  - LCD screen is cleared.

---

## 🔧 Hardware Requirements

| Component             | Description                     |
|----------------------|---------------------------------|
| LPC1768 Development Board | ARM Cortex-M3 Microcontroller     |
| 16x2 LCD              | For displaying the welcome message |
| IR Proximity Sensor   | To detect motion                |
| LED                  | Controlled via PWM              |
| Resistors, Breadboard, Jumper Wires | For basic connections    |
| Power Supply (5V)    | External or via USB             |

---

## 🧾 Pin Configuration

| LPC1768 Pin | Function         |
|-------------|------------------|
| P0.8        | IR Sensor Input  |
| P1.23       | PWM1.4 Output (LED) |
| P0.23–P0.26 | LCD Data Lines (D4–D7) |
| P0.27       | LCD RS           |
| P0.28       | LCD EN           |

---

## 🛠️ Software Requirements

- [Keil uVision 4 or 5](https://www.keil.com/)
- NXP LPC17xx CMSIS libraries
- Flash Magic (or similar) to program the board

---

## 📁 Project Structure

