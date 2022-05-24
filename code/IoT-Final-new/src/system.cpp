// Copyright (C) <2022> by IoT-Project-Team-12-DHBW-Stuttgart-TWIE19B
// including all the necessary libraries for the project
#include "system.h"
#include "WiFiClient.h"
#include "config.h"
#include <Arduino.h>
#include <BlynkSimpleEsp32.h>
#include <CheapStepper.h>

// creating new object `iot`  from IoTSystem class
IoTSystem iot(SSID, PASS, AUTH);

/**
 * 
 * General System super-loop
 * Same as `void loop()` but only for the project
 * 
 */
void IoTSystem::loop() {

    digitalWrite(PUMP, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Choose");
    lcd.setCursor(0, 1);
    lcd.print("Program [1/2/3]");
    Blynk.run();
}

/* -- | this is the loop for handling the overheat and sending sensor data | -- */ 
void IoTSystem::sensor_loop() {
   
    read_dht();
    read_fluid_lvl();

     if (temperature >= MAX_TEMP) { 
        move_to_op(COOLING);
        //bot.sendMessage(CHAT_ID, "Temperature too HIGH! Cooling now!");
        delay(500);
        digitalWrite(PUMP, LOW);
        digitalWrite(ALARM_PIEZO, HIGH);
        pixels.fill(pixels.Color(255, 0, 0), 0, 10);
        pixels.fill(pixels.Color(255, 0, 0), 15, 2);
        pixels.fill(pixels.Color(255, 0, 0), 18, 2);
        pixels.fill(pixels.Color(255, 0, 0), 21, 2);
        pixels.show();
        delay(800);
        digitalWrite(ALARM_PIEZO, LOW);
        pixels.clear();
        pixels.show(); 
    } else {
        move_to_op(WORKING);
        pixels.clear();
        pixels.show();
        digitalWrite(PUMP, HIGH);
        digitalWrite(ALARM_PIEZO, LOW);
    }
    if (!client.connected()) {
        reconnect();
    }

    if(millis() - last_sent >= 2000) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print((temperature >= MAX_TEMP) ? "Temp. too HIGH!" : "Temp. Ok");
        lcd.setCursor(0, 1);
        lcd.print((temperature >= MAX_TEMP) ? "Cooling NOW!" : "No need Cooling");
        verbose_values();
        publish_data();
            
        blynk_send_data();
        last_sent = millis();
    }
    client.loop();
    delay(100);
}

/* =================== | creating the IoTSystem class | ==================== */
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
    //motor(Stepper(SPU, IN1, IN3, IN2, IN4)),
    ssPins{SS_1_PIN, SS_2_PIN, SS_3_PIN},
    stepper_cur_pos(0),
    cur_op(Operation::IDLE),
    stepper(CheapStepper(IN1, IN2, IN3, IN4)),
    reader_uids{READER_0_UIDS, READER_1_UIDS, READER_2_UIDS}
    //bot(UniversalTelegramBot(BOTtoken, secure_client))
{
    // "Normal" constructor, setting first values
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
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Setting up");
    lcd.setCursor(0,1);
    lcd.print("WiFi");
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
    //secure_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    wifi_enabled = true;
    delay(1000);
}
/**
 * Setup necessary pins for System
 */
void IoTSystem::setup_pins() { 
    // Pin setup code
    pinMode(ALARM_PIEZO, OUTPUT);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(PUMP, OUTPUT); 
}
/**
 * Setup LCD Screen
 */
void IoTSystem::setup_lcd() {
    // LCD setup code
    Wire.begin(I2C_SDA, I2C_SCL);
    lcd.init();         // starting LCD setup  
    lcd.backlight();    // turn on backlight (lcd.noBacklight(); turn off backlight).
}

/* ============= | Setting up Neopixel RGB Strip | =========== */
void IoTSystem::setup_neopixel() {
    // INITIALIZE NeoPixel strip object (REQUIRED)
    pixels.begin();
    // Turn OFF all pixels ASAP
    pixels.show();
    // Setting up  britghness of the Neopixel strip
    pixels.setBrightness(BRIGHTNESS);    
}

/* --------------- | setting up rfid readers | -------------- */
void IoTSystem::setup_reader() {
    SPI.begin(); // Init SPI bus
    for (uint8_t reader = 0; reader < NR_OF_READERS; reader++) {
        mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN); // Init each MFRC522 card
        Serial.printf("Reader [%d]: ", reader);
        mfrc522[reader].PCD_DumpVersionToSerial();
    }
}

/* ================= | STEPPER MOTOR FUNCTIONS | ================= */
void IoTSystem::setup_speed() {
    stepper.setRpm(10);
    //motor.setSpeed(5);
}
/* ------------------- | angle setup function | ----------------   */
float IoTSystem::get_angle() {
    return ceil(stepper.getStep() * ANGLE_TO_STEP);
}

void IoTSystem::update_position(int angle) {
/*
Setting up the anlge function
360 degrees /4096 steps = 0.08.... factor per degree
*/
    //motor.step(angle / ANGLE_TO_STEP);
    stepper.moveDegrees((angle < 0) ? false : true, (angle < 0) ? -angle : angle);
    this->stepper_cur_pos = (((this->stepper_cur_pos + angle) % 360) + 360) % 360;
}

// ----------- | Stepper programs | -------------------------

void IoTSystem::tool_prog_1() {
/* 
Motor programm 1
Tool selection order  3 -> 2 -> 1
*/

    lcd.clear();
    move_to_op(TOOL3);
    while(!is_right_tool(READER_2));
    delay(1000);

    int start = millis();
    while (millis() - start <= 10000) {
        sensor_loop();
    }

    move_to_op(TOOL3);
    delay(1000);

    move_to_op(TOOL2);
    lcd.clear();
    while(!is_right_tool(READER_1));
    delay(1000);

    int start_1 = millis();
    while (millis() - start_1 <= 10000) {
        sensor_loop();
    }
    
    move_to_op(TOOL2);
    delay(1000);

    move_to_op(TOOL1);
    lcd.clear();
    while(!is_right_tool(READER_0));
    delay(1000);

    int start_2 = millis();
    while (millis() - start_2 <= 10000) {
        sensor_loop();
    }

    move_to_op(TOOL1);
    delay(1000);

    move_to_op(IDLE);
    delay(1000);    
    lcd.clear();
}

void IoTSystem::tool_prog_2() {
/* 
Motor programm 2
Tool selection order  1 -> 2 -> 3
*/

    lcd.clear();
    move_to_op(TOOL1);
    while(!is_right_tool(READER_0));
    delay(1000);

    int start = millis();
    while (millis() - start <= 100000) {
        sensor_loop();
    }

    move_to_op(TOOL1);
    delay(1000);

    move_to_op(TOOL2);
    lcd.clear();
    while(!is_right_tool(READER_1));
    delay(1000);

    int start_1 = millis();
    while (millis() - start_1 <= 100000) {
        sensor_loop();
    }
    
    move_to_op(TOOL2);
    delay(1000);

    move_to_op(TOOL3);
    lcd.clear();
    while(!is_right_tool(READER_2));
    delay(1000);

    int start_2 = millis();
    while (millis() - start_2 <= 100000) {
        sensor_loop();
    }

    move_to_op(TOOL3);
    delay(1000);

    move_to_op(IDLE);
    delay(1000);    
    lcd.clear();
}

void IoTSystem::tool_prog_3() {
/* 
Motor programm 3
Tool selection order   2 -> 3 -> 1
*/

    move_to_op(TOOL2);
    lcd.clear();
    while(!is_right_tool(READER_1));
    delay(1000);

    int start_1 = millis();
    while (millis() - start_1 <= 100000) {
        sensor_loop();
    }
    
    move_to_op(TOOL2);
    delay(1000);

    move_to_op(TOOL3);
    lcd.clear();
    while(!is_right_tool(READER_2));
    delay(1000);

    int start_2 = millis();
    while (millis() - start_2 <= 100000) {
        sensor_loop();
    }

    move_to_op(TOOL3);
    delay(1000);

    lcd.clear();
    move_to_op(TOOL1);
    while(!is_right_tool(READER_0));
    delay(1000);

    int start = millis();
    while (millis() - start <= 100000) {
        sensor_loop();
    }

    move_to_op(TOOL1);
    delay(1000);

    move_to_op(IDLE);
    delay(1000);    
    lcd.clear();

}
/* -------------- | move to specified area | ----------------- */
void IoTSystem::move_to_op(Operation op) {
    switch (op) {
        case IDLE:
            update_position(IDLE_ANGLE - stepper_cur_pos);
            delay(2000);
            break;
        case WORKING:
            update_position(WORKING_ANGLE - stepper_cur_pos);
            delay(2000);
            break;
        case COOLING:
            update_position(COOLING_ANGLE - stepper_cur_pos);
            delay(2000);
            break;
        case TOOL1:
            update_position(TOOL1_ANGLE - stepper_cur_pos);
            delay(2000);
            break;
        case TOOL2:
            update_position(TOOL2_ANGLE - stepper_cur_pos);
            delay(2000);
            break;
        case TOOL3:
            update_position(TOOL3_ANGLE - stepper_cur_pos);
            delay(2000);
            break;
        default:
            update_position(IDLE_ANGLE - stepper_cur_pos);
            delay(2000);
            break;
    }
    this->cur_op = op;
}

/* =============== | Setup Blynk server with auth | ================== */
/**
 * Setup Blynk server with auth
 */
void IoTSystem::setup_blynk() {
    // Blynk setup code
    if (!wifi_enabled) {
        return;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Setting up");
    lcd.setCursor(0,1);
    lcd.print("Blynk");
    Blynk.begin(AUTH, SSID, PASS, BLYNK_IP, BLYNK_PORT);      
    // Blynk.begin(auth, ssid, pass, IPAdress(192.168.1.100), 8080)
    //timer.setInterval(1000L, myTimerEvent);     
    // setup a unction to be calles every second
    blynk_enabled = true;
    delay(1000);
    lcd.clear();
}

/* ======================= | Sensor setup | =========================== */
void IoTSystem::setup_sensors() {
    dht.begin();
}

/* ===================== | Setup MQTT server | ========================= */
void IoTSystem::setup_mqtt() {
    if (!wifi_enabled){
        return;
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Setting up");
    lcd.setCursor(0,1);
    lcd.print("MQTT");
    // MQTT setup code
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.connect(clientId.c_str(), "student", "iotproject2§&d");
    //client.setCallback(this->callback);
    mqtt_enabled = true;
    delay(1000);
}
// --------------------- | Reconnect Function | --------------------------
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

/* ==================== | Reading Sensor Data | ====================== */

// -------------------- | Temperature sensor | ---------------------------
void IoTSystem::read_dht() {
    this->temperature = dht.readTemperature();
    this->humidity = dht.readHumidity();
}

// --------------- | Ultrasonic sensor for fluid lvl | --------------------
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
/* ------------- | printing values in serial monitor | ---------------- */
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
/* -------------- | sending data to the blynk cloud | ----------------- */
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

/* -------------------- | reading out rfid uid tag values | ---------------- */
void IoTSystem::dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}
/* ------------------------ | tool checking function | ---------------------- */
bool IoTSystem::is_right_tool(uint8_t reader) {
    bool uid_check[NUM_UIDS] = {false};
    switch (reader) {
        case READER_0:
            pixels.fill(pixels.Color(255, 255, 255), 0, 3);
            break;
        case READER_1:
            pixels.fill(pixels.Color(255, 255, 255), 3, 3);
            break;
        case READER_2:
            pixels.fill(pixels.Color(255, 255, 255), 6, 3);
            break;
    }
    if(mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial()) {
        // Serial.print("Card UID: ");
        // dump_byte_array(mfrc522[reader].uid.uidByte, mfrc522[reader].uid.size);
        // std::array is a container that encapsulates fixed size arrays. 
        for (int i = 0; i < NUM_UIDS; ++i) {   
            std::array<uint8_t, 4> read_byte;
            std::move(
                std::begin(mfrc522[reader].uid.uidByte),
                std::end(mfrc522[reader].uid.uidByte),
                read_byte.begin()
            );
            std::array<uint8_t, 4> needed_byte;
            std::move(
                std::begin(reader_uids[reader][i]),
                std::end(reader_uids[reader][i]),
                needed_byte.begin()
            );
            if (read_byte == needed_byte) {
                uid_check[i] = true;
            }
        }
        // picking right warehouse rgb lights for each reader 
        mfrc522[reader].PICC_HaltA();
        // Stop encryption on PCD
        mfrc522[reader].PCD_StopCrypto1();
        for (int i = 0; i < NUM_UIDS; ++i) {
            if (uid_check[i] == true) {
                switch (reader) {
                    case READER_0:
                        pixels.fill(pixels.Color(0, 255, 0), 15, 2);
                        break;
                    case READER_1:
                        pixels.fill(pixels.Color(0, 255, 0), 18, 2);
                        break;
                    case READER_2:
                        pixels.fill(pixels.Color(0, 255, 0), 21, 2);
                        break;

                }
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.printf("Right tool");
                pixels.show();
                delay(2000);
                pixels.clear();
                pixels.show();
                lcd.clear();
                return true;
            }
        }
        switch (reader) {
            case READER_0:
                pixels.fill(pixels.Color(255, 0, 0), 15, 2);
                break;
            case READER_1:
                pixels.fill(pixels.Color(255, 0, 0), 18, 2);
                break;
            case READER_2:
                pixels.fill(pixels.Color(255, 0, 0), 21, 2);
                break;

        }
        pixels.show();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.printf("Wrong tool");
        delay(2000);
        lcd.clear();
        return false;
    } else {
        mfrc522[reader].PICC_HaltA();
        // Stop encryption on PCD
        mfrc522[reader].PCD_StopCrypto1();
        lcd.setCursor(0, 0);
        lcd.printf("Waiting for");
        lcd.setCursor(0, 1);
        lcd.printf("reader: %d", reader);
        switch (reader) {
            case READER_0:
                pixels.fill(pixels.Color(255, 90, 0), 15, 2);
                break;
            case READER_1:
                pixels.fill(pixels.Color(255, 90, 0), 18, 2);
                break;
            case READER_2:
                pixels.fill(pixels.Color(255, 90, 0), 21, 2);
                break;

        }
        pixels.show();
        return false;
    } 
}

/* ---------------------- | publishing data via mqtt | --------------------- */
void IoTSystem::publish_data() {
    client.publish("dhbw/team12/value1", String(temperature).c_str(), true);
    client.publish("dhbw/team12/value2", String(humidity).c_str(), true);
    client.publish("dhbw/team12/value3", String(fluid_level).c_str(), true);
}

void IoTSystem::publish_data(float _value1, float _value2, float _value3) {
    client.publish("dhbw/team12/value1", String(_value1).c_str(), true);
    client.publish("dhbw/team12/value2", String(_value2).c_str(), true);
    client.publish("dhbw/team12/value3", String(_value3).c_str(), true); 
}
/* ------ | implementation of virtual pins for program selection | ---------- */
BLYNK_WRITE(V3) {
    int val = param.asInt();
    if (val)
        iot.tool_prog_1(); 
}

BLYNK_WRITE(V4) {
    int val = param.asInt();
    if (val)
        iot.tool_prog_2(); 
}

BLYNK_WRITE(V5) {
    int val = param.asInt();
    if(val)
        iot.tool_prog_3(); 
}