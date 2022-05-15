// Copyright (C) <2022> by [...]
#include "system.h"
#include "WiFiClient.h"
#include "config.h"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <Stepper.h>

/**
 * General System super-loop
 * Same as `void loop()` but only for the project
 */
void IoTSystem::loop() {
    // <-- USER CODE GOES HERE -->
    
    read_dht();
    read_fluid_lvl();

     if (temperature >= 25) { 
        digitalWrite(PUMP, LOW);
        digitalWrite(ALARM_LED, HIGH);
        pixels.fill(pixels.Color(255, 0, 0), 0, 10);
        pixels.setPixelColor(14, pixels.Color(255, 0, 0));
        pixels.setPixelColor(16, pixels.Color(255, 0, 0));
        pixels.setPixelColor(18, pixels.Color(255, 0, 0));
        pixels.show();
        delay(500);
        digitalWrite(ALARM_LED, LOW);
        pixels.clear();
        pixels.show();
    
    } else {
        digitalWrite(PUMP, HIGH);
        digitalWrite(ALARM_LED, LOW);

    }

    if (!client.connected()) {
        reconnect();
    }

    if(millis() - last_sent >= 2000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print((temperature >= 25) ? "Temp. too HIGH!" : "Temp. Ok");
        lcd.setCursor(0, 1);
        lcd.print((temperature >= 25) ? "Cooling NOW!" : "No need Cooling");
        verbose_values();
        publish_data();
        blynk_send_data();
        last_sent = millis();
    }

    client.loop();
    delay(100);    
}

IoTSystem::IoTSystem(
    char *_ssid,
    char *_pwd,
    char *_blynk_auth
) :
    _ssid(_ssid),
    _pwd(_pwd),
    _blynk_auth((char *) _blynk_auth),
    lcd(LiquidCrystal_I2C(LCD_ADDR, LCD_COLS, LCD_ROWS)), 
    dht(DHT(DHT_DATA_PIN, DHT22)),
    esp_client(WiFiClient()),
    client(PubSubClient(esp_client)),
    pixels(Adafruit_NeoPixel(NUMPIXELS, STRIP_PIN, NEO_GRB + NEO_KHZ800)),
    Motor(Stepper(SPU, IN1, IN3, IN2, IN4))
{
    // "Normal" constructor
    this->temperature = 0;
    this-> humidity = 0;
    this->fluid_level = 0;
}

/**
 * Setup wifi with SSID and Password
 */
void IoTSystem::setup_wifi() {
    // WiFi setup code
    delay(10);
    // We start by connecting to a WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(this->_ssid);

    WiFi.mode(WIFI_MODE_STA);
    WiFi.begin(this->_ssid, this->_pwd);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(1000);
}

/**
 * Setup necessary pins for System
 */
void IoTSystem::setup_pins() { 
    // Pin setup code
    pinMode(ALARM_LED, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(PUMP, OUTPUT); 
}
/**
 * Setup LCD Screen
 */
void IoTSystem::setup_lcd() {
    // LCD setup code
    lcd.init();         // starting LCD setup  
    lcd.backlight();    // turn on backlight (lcd.noBacklight(); turn off backlight).
}

void IoTSystem::setup_neopixel() {
    // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.begin();
    // Turn OFF all pixels ASAP
    pixels.show();
    // Setting up  britghness of the Neopixel strip
    pixels.setBrightness(BRIGHTNESS);    
}

void IoTSystem::setup_rgb_lights() {
    /* ========= | Set All Pixel Colors to 'OFF'| ============*/ 
    pixels.clear();

    /*============= | Tool Warehouse Lights | ================*/
    pixels.setPixelColor(0, pixels.Color(155, 155, 155));
    pixels.fill(pixels.Color(155, 0, 155), 1, 3);
    pixels.fill(pixels.Color(0, 0, 155), 4, 3);
    pixels.fill(pixels.Color(155, 155, 0), 7, 3);
    pixels.show();

    /*=========== | RFID Reader Lights | ===============*/
    pixels.setPixelColor(14, pixels.Color(0, 155, 0));
    pixels.setPixelColor(16, pixels.Color(0, 155, 0));
    pixels.setPixelColor(18, pixels.Color(0, 155, 0));
    pixels.show();
    delay(RGB_DELAY); 
    pixels.setPixelColor(14, pixels.Color(155, 64, 10));
    pixels.setPixelColor(16, pixels.Color(155, 64, 10));
    pixels.setPixelColor(18, pixels.Color(155, 64, 10));
    pixels.show();
    delay(RGB_DELAY);
    pixels.setPixelColor(14, pixels.Color(155, 0, 0));
    pixels.setPixelColor(16, pixels.Color(155, 0, 0));
    pixels.setPixelColor(18, pixels.Color(155, 0, 0));
    pixels.show();
    delay(RGB_DELAY);
    
/* ============ | Turning OFF All Lights | ===========  */
    pixels.clear();
    pixels.show();
    delay(RGB_DELAY);
}

void IoTSystem::setup_blinking_rgb() {

    /* ===== | truning ON all lights in red | ====== */
    pixels.fill(pixels.Color(255, 0, 0), 0, 10);
    pixels.setPixelColor(14, pixels.Color(255, 0, 0));
    pixels.setPixelColor(16, pixels.Color(255, 0, 0));
    pixels.setPixelColor(18, pixels.Color(255, 0, 0));
    pixels.show();
    delay(500);
    
    /* ========= |turnig off all lights| =============*/
    pixels.clear();
    pixels.show();
    delay(500); 

}

void IoTSystem::setup_speed() {
    Motor.setSpeed(5);
}

void IoTSystem::moving(int ANGLE) {
/*
Setting up the anlge function
360 degrees /2048 steps = 0.18 factor per degree
*/
    Motor.step(ANGLE/0.18);    
}


void IoTSystem::motor_prog_1() {
/* 
Motor programm 1
Tool selection order  1 -> 2 -> 3
*/
    //Motor.step(SPU);
    moving(-210);
    delay(DELAY_TOOL);
    //Motor.step(-SPU);
    moving(100);
    delay(DELAY_WORK);
    moving(-100);
    delay(DELAY_TOOL);
    moving(20);
    delay(DELAY_TOOL);
    moving(80);
    delay(DELAY_WORK);
    moving(-80);
    delay(DELAY_TOOL);
    moving(20);
    delay(DELAY_TOOL);
    moving(60);
    delay(DELAY_WORK);
    moving(-60);
    delay(DELAY_WORK);
    moving(170);
    delay(DELAY_TOOL);
}

void IoTSystem::motor_prog_2() {
/* 
Motor programm 2
Tool selection order  2 -> 3 -> 1
*/
    //Motor.step(SPU);
    moving(-190);
    delay(DELAY_TOOL);
    //Motor.step(-SPU);
    moving(80);
    delay(DELAY_WORK);
    moving(-80);
    delay(DELAY_TOOL);
    moving(20);
    delay(DELAY_TOOL);
    moving(60);
    delay(DELAY_WORK);
    moving(-60);
    delay(DELAY_TOOL);
    moving(-40);
    delay(DELAY_TOOL);
    moving(100);
    delay(DELAY_WORK);
    moving(-100);
    delay(DELAY_TOOL);
    moving(210);
    delay(DELAY_TOOL);   
}

void IoTSystem::motor_prog_3() {
/* 
Motor programm 2
Tool selection order   3 -> 1 -> 2
*/
    //Motor.step(SPU);
    moving(-170);
    delay(DELAY_TOOL);
    //Motor.step(-SPU);
    moving(60);
    delay(DELAY_WORK);
    moving(-60);
    delay(DELAY_TOOL);
    moving(-40);
    delay(DELAY_TOOL);
    moving(100);
    delay(DELAY_WORK);
    moving(-100);
    delay(DELAY_TOOL);
    moving(20);
    delay(DELAY_TOOL);
    moving(80);
    delay(DELAY_WORK);
    moving(-80);
    delay(DELAY_TOOL);
    moving(190);
    delay(DELAY_TOOL);

}


/**
 * Setup Blynk server with auth
 */
void IoTSystem::setup_blynk() {
    // Blynk setup code
    Blynk.begin(AUTH, SSID, PASS, BLYNK_IP, BLYNK_PORT);      // Blynk.begin(auth, ssid, pass, IPAdress(192.168.1.100), 8080)
    //timer.setInterval(1000L, myTimerEvent);     // setup a unction to be calles every second

}

void IoTSystem::setup_sensors() {
    dht.begin();
}

/**
 * Setup MQTT server
 */
void IoTSystem::setup_mqtt() {
    // MQTT setup code
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.connect(clientId.c_str(), "student", "iotproject2§&d");
    //client.setCallback(this->callback);
}

void IoTSystem::reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), "student", "iotproject2§&d")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void IoTSystem::read_dht() {
    this->temperature = dht.readTemperature();
    this->humidity = dht.readHumidity();
}

void IoTSystem::read_fluid_lvl() {

    float t = 0, h = 0;
    // Transmitting pulse
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
  
    // Waiting for pulse
    t = pulseIn(ECHO, HIGH);
    // Calculating distance 
    h = t / 14;
    h = h - 3.5;  // offset correction
    h = 57 - h;  // water height, 0 - 14.5 cm
    this->fluid_level = 2 * h;  // distance in %, 0-100 %

}

void IoTSystem::verbose_values() {
    Serial.printf(
        "Temperature: %2.2f °C | "
        "Humidity: %2.2f %% | "
        "Fluid Level: %2.2f %%\n", 
        temperature, 
        humidity, 
        fluid_level
    );
    
}

void IoTSystem::blynk_send_data() {
    Blynk.virtualWrite(V0, temperature);
    Blynk.virtualWrite(V1, humidity);
    Blynk.virtualWrite(V2, fluid_level);
}

/**
 * Get SSID string of connected WiFi network
 */
String IoTSystem::get_ssid() {
    return String(this->_ssid);
}

/**
 * Get authentication token for Blynk
 */
String IoTSystem::get_blynk_auth() {
    return String(this->_blynk_auth);
}

/**
 * Get temperature of current tool
 *
 * @return float temperature of current tool
 */
float IoTSystem::get_temperature() {
    return this->temperature;
}

/**
 * Get humidity of the system
 *
 * @return float humidity
 */
float IoTSystem::get_humidity() {
    return this->humidity;
}

/**
 * Get current fluid level for cooling
 *
 * @return float cooling fluid level
 */
float IoTSystem::get_fluid_level() {
    return this->fluid_level;
}

void IoTSystem::rfid_read() {

}

void IoTSystem::publish_data() {
    client.publish("dhbw/team12/value1", String(temperature).c_str(), true); // statt msg true
    client.publish("dhbw/team12/value2", String(humidity).c_str(), true); // statt msg true 
    client.publish("dhbw/team12/value3", String(fluid_level).c_str(), true);
}

void IoTSystem::publish_data(float _value1, float _value2, float _value3) {
    client.publish("dhbw/team12/value1", String(_value1).c_str(), true); // statt msg true
    client.publish("dhbw/team12/value2", String(_value2).c_str(), true); // statt msg true 
    client.publish("dhbw/team12/value3", String(_value3).c_str(), true); 
}
