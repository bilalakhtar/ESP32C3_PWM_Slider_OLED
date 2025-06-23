#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <U8g2lib.h>
#include <Wire.h>


// ==== OLED SETUP ====
#define OLED_SDA 5
#define OLED_SCL 6
#define OLED_RESET U8X8_PIN_NONE
U8G2_SSD1306_72X40_ER_F_HW_I2C u8g2(U8G2_R0, OLED_RESET, OLED_SCL, OLED_SDA);

// ==== Wi-Fi AP credentials ====
const char* ssid = "c3_pwn";
const char* password = "esp321234";

// ==== PWM and analog pins ====
const int pwmPin = 2;     // GPIO2 for PWM
const int potPin = A0;    // GPIO0 on ESP32-C3 boards for analog input

// ==== PWM config ====
const int pwmFreq = 5000;
const int pwmResolution = 10; // 10-bit = 0–1023

String sliderValue = "512";  // default
int currentPWM = 512;

const char* PARAM_INPUT = "value";
AsyncWebServer server(80);

// ==== HTML Page ====
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32-C3 PWM Control</title>
  <style>
    body { font-family: Arial; text-align: center; padding: 20px; }
    .slider { width: 300px; margin: 20px auto; }
  </style>
</head>
<body>
  <h2>ESP32-C3 PWM Control</h2>
  <p>PWM Value: <span id="textSliderValue">%SLIDERVALUE%</span></p>
  <input type="range" id="pwmSlider" min="0" max="1023" value="%SLIDERVALUE%" class="slider" oninput="updateSliderPWM(this)">
  <script>
    function updateSliderPWM(element) {
      var value = element.value;
      document.getElementById("textSliderValue").innerText = value;
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/slider?value=" + value, true);
      xhr.send();
    }
  </script>
</body>
</html>
)rawliteral";


// ==== Replaces placeholders ====
String processor(const String& var) {
  if (var == "SLIDERVALUE") {
    return sliderValue;
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(OLED_SDA, OLED_SCL);
  u8g2.begin();

  // Initialize display with welcome text
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(5, 20, "ESP32-C3");
  u8g2.sendBuffer();
  delay(1000);

  // Setup PWM using new API
  ledcAttach(pwmPin, pwmFreq, pwmResolution);
  ledcWrite(pwmPin, currentPWM);

  // Start Wi-Fi in AP mode
  WiFi.softAP(ssid, password);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  // Web route for slider UI
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor); // ✅ with processor()
  });

  // Web route for slider value
  server.on("/slider", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("value")) {
      sliderValue = request->getParam("value")->value();
      currentPWM = sliderValue.toInt();
      ledcWrite(pwmPin, currentPWM);
    }
    request->send(200, "text/plain", "OK");
  });

  server.begin();
}

void loop() {
  int potValue = analogRead(potPin);  // Read potentiometer

  // Display on OLED
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setCursor(0, 15);
  u8g2.print("PWM: ");
  u8g2.print(currentPWM);
  u8g2.setCursor(0, 35);
  u8g2.print("Pote: ");
  u8g2.print(potValue);
  u8g2.sendBuffer();

  delay(200);  // Refresh interval
}
