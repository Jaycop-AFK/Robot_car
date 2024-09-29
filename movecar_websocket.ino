#include <WiFi.h>
#include <WebSocketsServer.h>
#include "MotorControl.h"

// สร้าง object สำหรับควบคุมมอเตอร์
MotorControl motorControl;

const char* ssid = "iPhone";
const char* password = "987654321";

// สร้าง WebSocket server บนพอร์ต 8080
WebSocketsServer webSocket = WebSocketsServer(8888);

// ตัวแปรสำหรับเก็บความเร็วของมอเตอร์
int currentSpeed = 100;  // เริ่มต้นที่ความเร็ว 100



void setup() {
  Serial.begin(115200);

  // เชื่อมต่อกับ Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // เริ่ม WebSocket server
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);

  Serial.println(WiFi.localIP());

  // สร้าง instance ของ MotorControl
  motorControl = MotorControl();

  // หยุดมอเตอร์ในตอนเริ่มต้น
  stopMotors();
}

void loop() {
  // ฟัง WebSocket events
  webSocket.loop();
}

// ฟังก์ชันหยุดมอเตอร์
void stopMotors() {
  motorControl.stop();
}

// Handle incoming WebSocket events
void onWebSocketEvent(uint8_t client_num, WStype_t type, uint8_t* payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("Client %u disconnected\n", client_num);
      stopMotors();  // หยุดมอเตอร์เมื่อ client ตัดการเชื่อมต่อ
      break;

    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(client_num);
        Serial.printf("Client %u connected from %s\n", client_num, ip.toString().c_str());
        String speedStr = String(currentSpeed);

        // Send the string to the client
        webSocket.sendTXT(client_num, speedStr);
        break;
    }

    case WStype_BIN:
      {
        if (length > 0) {
          Serial.printf("Client %u sent binary data: ", client_num);
          for (size_t i = 0; i < length; i++) {
            Serial.printf("%02X ", payload[i]);
          }
          Serial.println();

          if (length == 1) {
            // Handle single-byte commands
            switch (payload[0]) {
              case 0x04:
                currentSpeed = min(currentSpeed + 100, 255);  // Increase speed
                Serial.printf("Increased speed to %d\n", currentSpeed);
                break;
              case 0x05:
                currentSpeed = max(currentSpeed - 100, 100);  // Decrease speed
                Serial.printf("Decreased speed to %d\n", currentSpeed);
                break;
              case 0x06:

                Serial.printf("Default");
                break;
              case 0x07:

                Serial.printf("Default");
                break;
              case 0x08:

                Serial.printf("Default");
                break;
              case 0x09:

                Serial.printf("Default");
                break;
              case 0x10:

                Serial.printf("Default");
                break;
              case 0x11:

                Serial.printf("Default");
                break;
              case 0x12:

                Serial.printf("Default");
                break;
              case 0x13:

                Serial.printf("Default");
                break;
              case 0x14:

                Serial.printf("Default");
                break;
              case 0x1:

                Serial.printf("Default");
                break;
              default:
                stopMotors();  // Stop motors if unknown command
                break;
            }
          } else if (length == 5) {
            // Handle joystick data
            uint8_t direction = payload[0];
            uint16_t joystickX = (payload[1] << 8) | payload[2];
            uint16_t joystickY = (payload[3] << 8) | payload[4];
            Serial.printf("Joystick X: %d, Y: %d, Direction: %d\n", joystickX, joystickY, direction);

            // Existing motor control logic
            if (direction == 0x02) {
              if (joystickY >= 8) {
                motorControl.moveForward(currentSpeed);
                Serial.println("Motor moving forward");
              } else if (joystickY < 3) {
                motorControl.moveBackward(currentSpeed);
                Serial.println("Motor moving backward");
              } else {
                stopMotors();
              }
            } else if (direction == 0x01) {
              if (joystickX >= 8) {
                motorControl.turnLeft(currentSpeed);
                Serial.println("Motor turning left");
              } else if (joystickX < 3) {
                motorControl.turnRight(currentSpeed);
                Serial.println("Motor turning right");
              } else {
                stopMotors();
              }
            }
          }
            // Echo the data back to the client
            webSocket.sendBIN(client_num, payload, length);
          } else {
            stopMotors();  // Stop motors if no data
          }
          break;
        }
      }
  }
