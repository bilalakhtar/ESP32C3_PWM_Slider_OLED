# ESP32-C3 PWM Slider with OLED Display

This project enables PWM control on an ESP32-C3 microcontroller using a **web-based slider** and displays the current PWM value and potentiometer input on an **OLED screen**. It works completely offline using the ESP32's Access Point mode.

![ESP32-C3 PWM OLED Demo](https://user-images.githubusercontent.com/your-image-placeholder.png)

---

## ✨ Features

- 📶 Wi-Fi Access Point (no internet needed)
- 🌐 Web interface with real-time slider (0–1023)
- ⚡ PWM signal output using new ESP32-C3 `ledcAttach()`
- 📟 OLED display shows PWM value + analog potentiometer reading
- 🎛️ Live PWM control from your browser

---

## 🔧 Hardware Used

- ✅ [ESP32-C3 Dev Module](https://www.espressif.com/en/products/socs/esp32-c3)
- ✅ SSD1306-compatible 72x40 OLED display (I2C)
- ✅ Potentiometer (connected to A0)
- ✅ Any device with a web browser (phone/laptop)

---

## 📁 Project Structure

<pre> ESP32C3_PWM_Slider_OLED/
  ├── ESP32C3_PWM_Slider_OLED.ino ← Main Arduino sketch
  ├── README.md ← Project documentation 
</pre>

---

## 🚀 Getting Started

### 1. Upload to ESP32-C3

- Open the `.ino` file in Arduino IDE or PlatformIO
- Select **Board**: ESP32C3 Dev Module
- Install required libraries:
  - `ESPAsyncWebServer`
  - `AsyncTCP`
  - `U8g2` by olikraus

### 2. Connect to ESP Access Point

- After upload, connect your phone or PC to the AP:
- SSID: c3_pwn
- Password: esp321234

- Open browser and go to: `http://192.168.4.1`


---

## 🧠 Future Improvements

- Save PWM value to flash to retain after reset
- Add fade-in/out animation with `ledcFade`
- Enable Wi-Fi station mode for home network
- Add MQTT/WebSocket for IoT control

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).

---

## 🙌 Credits

Developed by [@bilalakhtar](https://github.com/bilalakhtar)
