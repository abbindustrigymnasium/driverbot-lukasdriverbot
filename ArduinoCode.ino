#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>

// WiFi and MQTT broker configuration
const char* ssid = "ABB_Gym_IOT";          // Replace with your WiFi SSID
const char* password = "Welcome2abb";  // Replace with your WiFi password
const char* mqtt_server = "broker.emqx.io";   // MQTT broker

WiFiClient espClient;
PubSubClient client(espClient);

// Motor control pins
const int motorPinRightDir = 0; // D2
const int motorPinRightSpeed = 5; // D1

// Servo control
Servo steeringServo;
const int SERVO_PIN = D7; // Choose a pin to connect the servo

// Function to set up WiFi connection
void setup_wifi() {
    Serial.println("Connecting to WiFi...");
    int wifi_timeout = 10; // Set timeout in seconds
    int wifi_attempts = 5; // Set maximum number of attempts
    for (int i = 0; i < wifi_attempts; i++) {
        if (WiFi.begin(ssid, password)) {
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
            }
            Serial.println("WiFi connected.");
            return;
        }
        if (i == wifi_attempts - 1) {
            Serial.println("WiFi connection failed.");
            return;
        }
        delay(1000);
    }
}

// Callback function to process incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
    String message;
    for (unsigned int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println("Message received: " + message);

    // Process the received message to control the motor
    if (message == "Forward") {
        digitalWrite(motorPinRightDir, LOW);
        analogWrite(motorPinRightSpeed, 1024); // Adjust speed as needed
    } else if (message == "Backwards") {
        digitalWrite(motorPinRightDir, HIGH);
        analogWrite(motorPinRightSpeed, 1024); // Adjust speed as needed
    } else if (message == "Stop") {
        analogWrite(motorPinRightSpeed, 0);
    } else if (message == "Left") {
        steeringServo.write(45); 
    } else if (message == "Right") {
        steeringServo.write(135); 
    } else {
        Serial.println("Unknown message received.");
    }
}

// Function to reconnect to MQTT broker if connection is lost
void reconnect() {
    while (!client.connected()) {
        Serial.print("Attempting MQTT connection...");
        int mqtt_attempts = 5; // Set maximum number of attempts
        for (int i = 0; i < mqtt_attempts; i++) {
            if (client.connect("ESP8266Client")) {
                Serial.println("connected");
                // Subscribe to the control topic
                client.subscribe("control/topic");
                return;
            }
            if (i == mqtt_attempts - 1) {
                Serial.println("MQTT connection failed.");
                return;
            }
            delay(1000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    
    // Set up motor control pins as outputs
    pinMode(motorPinRightDir, OUTPUT);
    pinMode(motorPinRightSpeed, OUTPUT);
    
    // Initialize servo and attach it to the specified pin
    steeringServo.attach(SERVO_PIN);
    
    // Set up WiFi connection
    setup_wifi();
    
    // Set up MQTT client
    client.setServer(mqtt_server, 1883);
    
    // Set callback function for incoming MQTT messages
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    
    // Run MQTT client loop to handle incoming messages and send messages
    client.loop();

    // Check for motor overheating and stop movement if necessary
    if (motor_overheating()) {
        analogWrite(motorPinRightSpeed, 0);
        delay(1000);
        motor_cool_down();
    }

    // Check for servo overheating and stop movement if necessary
    if (servo_overheating()) {
        steeringServo.detach();
        delay(1000);
        steeringServo.attach(SERVO_PIN);
    }
}

// Functions to check for motor overheating and cool down components
bool motor_overheating() {

}

void motor_cool_down() {
  
}

bool servo_overheating() {
  
}

void servo_cool_down() {
  
}
