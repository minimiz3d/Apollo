#if 0
/*
* Magic_Tune
*
* This program will receive an amplified analog signal, compare the pitch, and control the servo motor while displaying output LEDs
*/
//Libraries required for servo control and usage of the Atmega’s internal timer
#include
#include "WProgram.h"

//Global variables to be used
int x;
int y;
int lastx;
int lasty;
long timer;
int idle_timer;
int threshold;
int cross_count;
int in_tune;
int average_val;
int pitch_diff;

int upper_bound;
int lower_bound;
int avg_cross;
int avg_counter;
int avg_upper;
int avg_lower;
float a, b;

int timer_divide;
int divide_by;

int string_select;
int select_pin_val;

int analogPin = 0; // analog to digital pin for signal input

int led_high = 13; // this LED will show user if a string's pitch is too high
int led_ok = 12; // this LED will show user if a string's pitch is correct
int led_low = 11; // this LED will show user if a string's pitch is too low

// these pins will light up to show which string the Atmega is comparing values for
int led_e4 = 10;
int led_b3 = 9;
int led_g3 = 8;
int led_d3 = 7;
int led_a2 = 6;
int led_e2 = 5;

int button_pin = 3; // input pin for user using a button to switch strings
int servoPin = 2; // control pin for servo motor

void setup() {
    // Set up timer 1 to generate an interrupt every 1 microsecond
    TCCR1A = 0x00;
    TCCR1B = (_BV(WGM12) | _BV(CS12));
    OCR1A = .071;
    TIMSK1 = _BV(OCIE1A);

    x = 0;
    lastx = 0;
    y = 0;
    lasty = 0;

    timer = 0;
    cross_count = 0;
    avg_cross = 0;
    avg_counter = 0;
    string_select = 0;

    //Set the input and output pins
    pinMode(button_pin, INPUT);
    pinMode(servoPin, OUTPUT);
    pinMode(led_high, OUTPUT);
    pinMode(led_ok, OUTPUT);
    pinMode(led_low, OUTPUT);
    pinMode(led_e4, OUTPUT);
    pinMode(led_b3, OUTPUT);
    pinMode(led_g3, OUTPUT);
    pinMode(led_d3, OUTPUT);
    pinMode(led_a2, OUTPUT);
    pinMode(led_e2, OUTPUT);

    Serial.begin(9600);	// Opens serial port, sets data rate to 9600 bps
}

// Nothing is done in the Arduino loop, since timing is off.
void loop() {
}

// Timer function running every microsecond
ISR(TIMER1_COMPA_vect) {
    timer++;
    idle_timer++;

    // Read button press to determine which string is to be detected
    if (timer % 100 == 0) {
        select_pin_val = digitalRead(button_pin);

        if (select_pin_val == HIGH) {
            string_select = ((string_select + 1) % 6);
            Serial.print("string: ");
            Serial.println(string_select);
        }
    }


    // Depending on which string is selected, the proper variables are set
    switch (string_select) {
        case 0:
            digitalWrite(led_e4, LOW); // sets the proper LED on, all else off
            digitalWrite(led_b3, LOW);
            digitalWrite(led_g3, LOW);
            digitalWrite(led_d3, LOW);
            digitalWrite(led_a2, LOW);
            digitalWrite(led_e2, HIGH);

            a = 0.045;
            b = 0.9099;
            threshold = 150;
            upper_bound = 77;
            lower_bound = 33;
            avg_upper = 57;
            in_tune = 55;	// This is the “in tune” average of cross counts for the string.
            avg_lower = 53;
            timer_divide= 2000;
            divide_by = 3;

            break;
        case 1:
            digitalWrite(led_e4, LOW); // sets the proper LED on, all else off
            digitalWrite(led_b3, LOW);
            digitalWrite(led_g3, LOW);
            digitalWrite(led_d3, LOW);
            digitalWrite(led_a2, HIGH);
            digitalWrite(led_e2, LOW);

            a = 0.0592;
            b = 0.8816;
            threshold = 150;
            upper_bound = 88;
            lower_bound = 44;
            avg_upper = 67;
            in_tune = 65;	// This is the “in tune” average of cross counts for the string.
            avg_lower = 63;
            timer_divide = 2000;
            divide_by = 3;

            break;
        case 2:
            digitalWrite(led_e4, LOW); // sets the proper LED on, all else off
            digitalWrite(led_b3, LOW);
            digitalWrite(led_g3, LOW);
            digitalWrite(led_d3, HIGH);
            digitalWrite(led_a2, LOW);
            digitalWrite(led_e2, LOW);

            a = 0.0797;
            b = 0.8406;
            threshold = 150;
            upper_bound = 117;
            lower_bound = 63;
            avg_upper = 97;
            in_tune = 95;	// This is the “in tune” average of cross counts for the string.
            avg_lower = 93;
            timer_divide = 2000;
            divide_by = 3;

            break;
        case 3:
            digitalWrite(led_e4, LOW); // sets the proper LED on, all else off
            digitalWrite(led_b3, LOW);
            digitalWrite(led_g3, HIGH);
            digitalWrite(led_d3, LOW);
            digitalWrite(led_a2, LOW);
            digitalWrite(led_e2, LOW);

            a = 0.0730;
            b = 0.8541;
            threshold = 130;
            upper_bound = 50;
            lower_bound = 15;
            avg_upper = 29;
            in_tune = 27;	// This is the “in tune” average of cross counts for the string.
            avg_lower = 26;
            timer_divide = 500;
            divide_by = 4;

            break;
        case 4:
            digitalWrite(led_e4, LOW); // sets the proper LED on, all else off
            digitalWrite(led_b3, HIGH);
            digitalWrite(led_g3, LOW);
            digitalWrite(led_d3, LOW);
            digitalWrite(led_a2, LOW);
            digitalWrite(led_e2, LOW);

            a = 0.1270;
            b = 0.7459;
            threshold = 140;
            upper_bound = 50;
            lower_bound = 15;
            avg_upper = 35;
            in_tune = 34;	// This is the “in tune” average of cross counts for the string.
            avg_lower = 33;
            timer_divide = 500;
            divide_by = 4;

            break;
        case 5:
            digitalWrite(led_e4, HIGH); // sets the proper LED on, all else off
            digitalWrite(led_b3, LOW);
            digitalWrite(led_g3, LOW);
            digitalWrite(led_d3, LOW);
            digitalWrite(led_a2, LOW);
            digitalWrite(led_e2, LOW);

            a = 0.1648;
            b = 0.6705;
            threshold = 150;
            upper_bound = 60;
            lower_bound = 20;
            avg_upper = 47;
            in_tune = 45;	// This is the “in tune” average of cross counts for the string.
            avg_lower = 43;
            timer_divide = 500;
            divide_by = 4;

            break;
    }

    check_crossings();

    // After the string input has been idle for a while, we take the average of a number of cross counts that were in bound.
    if (idle_timer == 10000) {
        Serial.println("AVG AVG LOOK HERE AVG AVG");
        average_val = avg_cross / divide_by;
        Serial.println(average_val);

        // If else statements for tuner lights
        if ((average_val < avg_lower) && (average_val > 0)) {
            // Turn off all string display lights to conserve power
            digitalWrite(led_e4, LOW);
            digitalWrite(led_b3, LOW);
            digitalWrite(led_g3, LOW);
            digitalWrite(led_d3, LOW);
            digitalWrite(led_a2, LOW);
            digitalWrite(led_e2, LOW);

            // Sets the proper tuning LED on, all else off
            digitalWrite(led_high, LOW);
            digitalWrite(led_ok, LOW);
            digitalWrite(led_low, HIGH);

            pitch_diff = in_tune - average_val;
            Serial.print("Pitch Difference Low: ");
            Serial.println(pitch_diff);

            // If the tuning is off by a questionably high amount, count it as an error in reading and do not turn the peg.
            // Otherwise tune the peg for a period of time. This time depends on how far off the read average is.
            if (pitch_diff < 20)
                for(long i = 0; i < pitch_diff * 36000; i++) {
                    digitalWrite(servoPin, HIGH); // start the pulse
                    delayMicroseconds(15); // pulse width
                    digitalWrite(servoPin, LOW); // stop the pulse
                }
        }

        // Don't turn the peg if the guitar is in tune.
        else if ((average_val >= avg_lower && average_val <= avg_upper) || (average_val == 0)) {
            // Sets the proper tuning LED on, all else off
            digitalWrite(led_high, LOW);
            digitalWrite(led_ok, HIGH);
            digitalWrite(led_low, LOW);
        }

        else if (average_val > avg_upper) {
            // Turn off all string display lights to conserve power
            digitalWrite(led_e4, LOW);
            digitalWrite(led_b3, LOW);
            digitalWrite(led_g3, LOW);
            digitalWrite(led_d3, LOW);
            digitalWrite(led_a2, LOW);
            digitalWrite(led_e2, LOW);

            // Sets the proper tuning LED on, all else off
            digitalWrite(led_high, HIGH);
            digitalWrite(led_ok, LOW);
            digitalWrite(led_low, LOW);

            pitch_diff = average_val - in_tune;
            Serial.print("Pitch Difference High: ");
            Serial.println(pitch_diff);

            // If the tuning is off by a questionably high amount, count it as an error in reading and do not turn the peg.
            // Otherwise tune the peg for a period of time. This time depends on how far off the read average is.
            if (pitch_diff < 20)
                for(long i = 0; i < pitch_diff * 270000; i++) {
                    digitalWrite(servoPin, HIGH); // start the pulse
                    delayMicroseconds(2); // pulse width
                    digitalWrite(servoPin, LOW); // stop the pulse
                }
        }

        // Reset all variables used for pitch detection
        cross_count = 0;
        avg_cross = 0;
        avg_counter = 0;
    }

    // We take the average of cross counts after the first value in bound. We dismiss the first value since it is usually inaccurate
    // for finding a good average.
    if (timer % timer_divide == 0){
        if (cross_count > lower_bound && cross_count < upper_bound) {
            if (avg_counter >= 1 && avg_counter < (divide_by + 1)) {
                avg_cross = avg_cross + cross_count;
                Serial.print("Runnin Avg cross sum: ");
                Serial.println(avg_cross);
            }
            avg_counter++;
        }
        Serial.print("cross_count: ");
        Serial.println(cross_count);
        cross_count = 0;
    }
}

void check_crossings() {
    lastx = x;
    lasty = y;
    x = analogRead(analogPin); // Read the input pin
    y = a * x + a * lastx + b * lasty; // Apply Butterworth filter to eliminate high frequencies

    // If the string crosses it's set threshold, add it to the count. If there are no crossings, the idle timer will begin to run.
    if (lasty > threshold and y < threshold) {
        cross_count++;
        idle_timer = 0;
    }
}
#endif
