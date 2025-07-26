#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// LCD connection (using PORTD)
#define LCD_DATA PORTD
#define ctrl PORTB
#define en PB2
#define rw PB1
#define rs PB0

// Function to send command to LCD
void LCD_cmd(unsigned char cmd) {
    LCD_DATA = cmd;
    ctrl = (0 << rs) | (0 << rw) | (1 << en);
    _delay_ms(1);
    ctrl = (0 << rs) | (0 << rw) | (0 << en);
    _delay_ms(50);
}

// Function to send data to LCD
void LCD_write(unsigned char data) {
    LCD_DATA = data;
    ctrl = (1 << rs) | (0 << rw) | (1 << en);
    _delay_ms(1);
    ctrl = (1 << rs) | (0 << rw) | (0 << en);
    _delay_ms(50);
}

// LCD initialization
void LCD_init() {
    LCD_cmd(0x38); // 8-bit, 2-line, 5x7
    LCD_cmd(0x0C); // Display ON, cursor OFF
    LCD_cmd(0x06); // Auto-increment cursor
    LCD_cmd(0x01); // Clear display
    _delay_ms(50);
}

// Send a string to LCD
void LCD_string(char *str) {
    while (*str) {
        LCD_write(*str++);
    }
}

// Servo motor control (OC1A pin - PB1)
void servo_rotate() {
    // Fast PWM Mode
    DDRB |= (1 << PB1);
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler 8
    ICR1 = 19999; // 20ms period

    // Rotate to 90 degree
    OCR1A = 1500;
    _delay_ms(1000);

    // Back to 0 degree
    OCR1A = 1000;
    _delay_ms(1000);

    // Stop
    TCCR1A = 0;
    TCCR1B = 0;
}

// Main Function
int main(void) {
    DDRD = 0xFF; // LCD data as output
    DDRB |= (1 << en) | (1 << rw) | (1 << rs); // LCD control pins
    DDRC &= ~(1 << PC0); // IR Sensor input
    DDRC &= ~(1 << PC1); // Ultrasonic Echo
    DDRC |= (1 << PC2);  // Ultrasonic Trigger
    DDRB |= (1 << PB3);  // Buzzer output

    LCD_init();

    int wasteCount = 0;

    while (1) {
        if ((PINC & (1 << PC0)) == 0) { // IR detects object
            _delay_ms(200);
            
            // Trigger ultrasonic
            PORTC |= (1 << PC2);
            _delay_us(10);
            PORTC &= ~(1 << PC2);

            // Wait for echo
            while ((PINC & (1 << PC1)) == 0);
            TCNT1 = 0;
            TCCR1B |= (1 << CS11); // Start timer
            while ((PINC & (1 << PC1)) != 0);
            TCCR1B = 0;

            int time = TCNT1;
            int distance = time / 58;

            if (distance < 10) {
                wasteCount++;
                LCD_cmd(0x01); // Clear display
                LCD_string("Waste Detected!");
                _delay_ms(1000);

                LCD_cmd(0x01);
                LCD_string("Reward Dispensing");

                // Buzz and rotate servo
                PORTB |= (1 << PB3);
                servo_rotate();
                _delay_ms(1000);
