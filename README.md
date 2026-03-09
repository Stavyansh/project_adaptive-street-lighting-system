# Smart Cascaded Street Lighting System

This project is a simple Arduino-based adaptive street lighting prototype that uses ambient light sensing and motion detection to control multiple street lights. The goal is to reduce unnecessary power usage by keeping lights off during the day, running them at low brightness at night, and increasing brightness only where motion is detected.

The system uses a single LDR to determine whether it is day or night and three IR sensors to detect motion in different zones. Each IR sensor controls its own LED, creating a cascaded lighting arrangement where each light operates independently while sharing the same ambient light controller.

---

## Hardware Used

Arduino Uno  
LDR (Light Dependent Resistor)  
10k potentiometer for adjusting light sensitivity  
3 IR obstacle sensors  
3 LEDs  
3 × 1kΩ resistors for current limiting  
Breadboard or protoboard  
Jumper wires  

---

## Pin Connections

LDR → A0  
IR sensor 1 → D10  
IR sensor 2 → D9  
IR sensor 3 → D8  

LED 1 → D6  
LED 2 → D5  
LED 3 → D3  

PWM pins are used for the LEDs so their brightness can be controlled using `analogWrite()`.

---

## System Behaviour

The LDR continuously measures ambient light levels. When the environment is bright (daytime), the system keeps all LEDs turned off. When the light level drops below a defined threshold, the Arduino switches to night mode.

In night mode the LEDs operate at dim brightness by default. If an IR sensor detects motion near its corresponding zone, the brightness of that LED increases to full intensity while the others remain dim. This simulates a smart street lighting system that only illuminates areas where activity is detected.

---

## Arduino Code and Explanation

The first part of the program defines all the pins used in the circuit.
```
int ldrPin = A0;
int ir1 = 10;
int ir2 = 9;
int ir3 = 8;
int led1 = 6;
int led2 = 5;
int led3 = 3;
int threshold = 500;
```
ldrPin is connected to the LDR which provides an analog voltage based on ambient light.
ir1, ir2, and ir3 correspond to the three IR motion sensors.
led1, led2, and led3 control the LEDs representing street lights.
threshold defines the boundary between day and night conditions.

The setup function runs once when the Arduino starts and initializes the pins.
```
void setup() {
  Serial.begin(9600);

  pinMode(ir1, INPUT);
  pinMode(ir2, INPUT);
  pinMode(ir3, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}
```
The IR sensors are configured as inputs and the LEDs are configured as outputs. Serial communication is also started so the LDR readings can be monitored during testing.
Inside the loop function the Arduino continuously reads the ambient light level.
```
int ldrValue = analogRead(ldrPin);
Serial.print("LDR: ");
Serial.println(ldrValue);
```
The LDR returns a value between 0 and 1023. Lower values correspond to darker environments while higher values correspond to brighter conditions.

The next part checks whether it is night.
```
if (ldrValue < threshold)
```
If the light level is below the threshold, the system assumes it is dark and activates the lighting logic. Otherwise it remains in day mode and all LEDs stay off.

During night mode the program reads the state of each IR sensor.
```
int ir1State = digitalRead(ir1);
int ir2State = digitalRead(ir2);
int ir3State = digitalRead(ir3);
```
Most IR obstacle sensors output LOW when motion or an object is detected.

The LEDs are then controlled using PWM.
```
if (ir1State == LOW) analogWrite(led1, 255);
else analogWrite(led1, 80);
```
Two brightness levels are used:
0 → LED off
80 → dim brightness
255 → full brightness

When motion is detected, the corresponding LED switches to full brightness. When no motion is present, the LED remains dim.

The same logic is applied to all three sensor–LED pairs.

If the system detects daytime, all LEDs are turned off.
```
else {
  analogWrite(led1, 0);
  analogWrite(led2, 0);
  analogWrite(led3, 0);
}
```
This ensures the lights do not operate during the day.

---

## Applications

Energy efficient street lighting systems
Motion activated outdoor lighting
Smart city infrastructure prototypes
Embedded systems learning projects

