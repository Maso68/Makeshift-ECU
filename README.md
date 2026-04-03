# Makeshift ECU — RPM & Temperature Monitor

This is a small project I built to simulate a basic ECU-style system. It reads RPM using a hall‑effect sensor, measures temperature with a DS18B20 sensor, shows everything on an OLED display, and sends the data over serial so a Python script can log and graph it. It’s a simple setup, but it ties together embedded code, sensors, and data visualization in a way that feels like a real engine‑monitoring system.

---

## What the Project Does

**On the Arduino side:**
- Counts pulses from a hall sensor to calculate RPM  
- Reads temperature in Fahrenheit from a DS18B20  
- Displays both values on a 128×64 OLED  
- Sends `temperature,rpm` over serial once per second  
- Shows a “TOO HOT” warning if the temp goes above 80°F  

**On the Python side:**
- Logs incoming serial data to a CSV file  
- Plots temperature and RPM over time on a dual‑axis graph  
- Gives a quick visual of how the system behaves during a run  

---

## Hardware Used

- Arduino (Uno/Nano/etc.)  
- Hall‑effect sensor  
- DS18B20 temperature sensor  
- SSD1306 OLED display (I2C)  
- USB cable for serial communication  

---

## Files in This Repo

| File | Purpose |
|------|---------|
| **RMPTEMPPROJECT.ino** | Arduino code for reading sensors and updating the OLED |
| **RPMTEMPPROJECT.py** | Python script for logging and graphing the data |
| **README.md** | This documentation |

---

## How It Works (Quick Breakdown)

### RPM
The hall sensor triggers an interrupt on pin 2.  
The code counts pulses for one second, then converts that to RPM.

### Temperature
The DS18B20 is read using the DallasTemperature library.  
The value is displayed and sent over serial.

### Display
The OLED shows:
- Temperature  
- RPM  
- A warning if the temperature gets too high  

### Logging & Graphing
The Python script:
1. Opens the COM port  
2. Logs all incoming data to a CSV  
3. Creates a plot with temperature and RPM on separate axes  

---

## Future Things I Might Add

- More sensors (TPS, coolant temp, etc.)  
- CAN bus simulation  
- SD card logging  
- A small PCB version  
- A nicer UI or dashboard  

---

## Author

**Benjamin Lust**  
Mechanical Engineering @ UVM  
Interested in embedded systems, mechanical systems, and anything engineering.
