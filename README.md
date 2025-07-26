# Reverse-Vending-Machine
This Reverse Vending Machine (RVM) project simulates an automated system that accepts waste items such as plastic bottles or cans and rewards users for recycling. Using sensors and actuators connected to an ATmega328P microcontroller (Arduino Uno), the machine detects waste, counts it, displays information on an LCD, activates a buzzer, and rotates a servo motor to dispense a reward.

⚙️ Features
✅ Detects the presence of waste using an IR Sensor

✅ Measures distance with an Ultrasonic Sensor for confirmation

✅ Displays messages and count on a 16x2 LCD

✅ Activates a buzzer when waste is inserted

✅ Dispenses reward using a servo motor

✅ Written entirely in Embedded C (AVR-GCC style)

🧠 Components Used
Component	Description
IR Sensor	Detects object placed in the slot
Ultrasonic Sensor	Measures distance to validate object
16x2 LCD	Displays status and waste count
Buzzer	Alerts user when object is inserted
Servo Motor	Dispenses reward (like a token)
Arduino Uno / ATmega328P	Core microcontroller
Breadboard & Wires	For circuit prototyping
Power Supply	5V regulated source

🔌 Pin Configuration
Component	Arduino Pin	Description
IR Sensor OUT	A0 (PC0)	Waste detection
Ultrasonic Echo	A1 (PC1)	Distance measurement
Ultrasonic Trig	A2 (PC2)	Distance measurement
Servo Motor	PB1 (OC1A)	Reward rotation control
Buzzer	PB3	Beep on waste insert
LCD Data Pins	PORTD	LCD display data
LCD Control Pins	PB0, PB1, PB2	RS, RW, EN

🔧 How It Works
User inserts a waste item

IR sensor detects the object.

Ultrasonic sensor confirms valid distance (to reduce false triggers).

LCD displays “Waste Detected” and reward info.

Buzzer sounds to confirm.

Servo motor rotates to dispense a token or reward.

Count is incremented and displayed on the LCD.

💻 Code Highlights
Developed in Embedded C using AVR registers (avr/io.h, util/delay.h)

Uses Timer1 for PWM-based servo motor control

Simple LCD driver functions implemented manually

Efficient interrupt-free design suitable for low-power embedded systems

🧪 Testing & Simulation
You can test this project:

On real hardware (Arduino Uno + Sensors + LCD)

Or use simulation tools like Proteus or TinkerCAD

Make sure to connect a common ground between all components.

Calibrate ultrasonic sensor if distance isn't accurate.

Reward mechanism (servo) can be replaced with LED or coin dispenser.

