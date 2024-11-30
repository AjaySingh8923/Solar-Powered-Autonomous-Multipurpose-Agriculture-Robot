//SOLAR POWER AGRICULTURE BOT -- AGROBOT

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <IRremote.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Initialize LCD
#define RECV_PIN 11  // IR Receiver Pin
IRrecv irrecv(RECV_PIN);  // IR Receiver
decode_results results;

#define enA 9  // Enable Pin L298 Motor Driver
#define in1 5  // Motor 1 Pin L298
#define in2 4  // Motor 1 Pin L298
#define in3 3  // Motor 2 Pin L298
#define in4 7  // Motor 2 Pin L298
#define enB 6  // Enable Pin L298 Motor Driver
#define sowingServo A2  // Sowing Servo Pin
#define pump A3  // Water Pump Pin
#define buzz 13  // Buzzer Pin

int Speed = 150;  // Motor speed (0-255)
int s1, s2, s3;   // Sensor readings

void setup() { 
  Serial.begin(9600);  // Initialize Serial Communication
  lcd.begin();
  lcd.backlight();
  
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
  
  lcd.print("   Welcome To ");
  lcd.setCursor(0, 1);
  lcd.print("Agriculture Robot");
  delay(4000);
  lcd.clear();
  
  lcd.print("Sowing & Watering");
  delay(2000);
  
  pinMode(enA, OUTPUT);  // Motor Driver Pins
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(sowingServo, OUTPUT);  // Sowing Servo Pin
  pinMode(pump, OUTPUT);  // Water Pump Pin
  pinMode(buzz, OUTPUT);  // Buzzer Pin

  irrecv.enableIRIn();  // Start the IR receiver

  analogWrite(enA, Speed);  // Set motor speed
  analogWrite(enB, Speed);  // Set motor speed
  delay(500);
}

void loop() {
  if (irrecv.decode(&results)) {
    long int decCode = results.value;
    Serial.println(decCode);  // Print IR code for debugging
    irrecv.resume();  // Receive the next value

    // Example: IR remote control for different functionalities
    if (decCode == 0x1FE48B7) {  // Example IR button code for Forward
      forword();
      lcd.clear();
      lcd.print("Moving Forward");
    } 
    else if (decCode == 0x1FE58A7) {  // Example IR button code for Backward
      backword();
      lcd.clear();
      lcd.print("Moving Backward");
    }
    else if (decCode == 0x1FE6897) {  // Example IR button code for Left Turn
      turnLeft();
      lcd.clear();
      lcd.print("Turning Left");
    }
    else if (decCode == 0x1FEB04F) {  // Example IR button code for Right Turn
      turnRight();
      lcd.clear();
      lcd.print("Turning Right");
    }
    else if (decCode == 0x1FEE01F) {  // Example IR button code for Sowing
      sowing();
      lcd.clear();
      lcd.print("Sowing Seeds");
    }
    else if (decCode == 0x1FEF00F) {  // Example IR button code for Water Pump
      waterPump();
      lcd.clear();
      lcd.print("Water Pump ON");
    }
    else if (decCode == 0x1FE906F) {  // Example IR button code for Stop
      Stop();
      lcd.clear();
      lcd.print("Stopping");
    }
    
    delay(500);
  }
}

// Motor control functions
void forword() {  // Move Forward
  digitalWrite(in1, HIGH);  // Right Motor forward Pin
  digitalWrite(in2, LOW);   // Right Motor backward Pin
  digitalWrite(in3, LOW);   // Left Motor backward Pin
  digitalWrite(in4, HIGH);  // Left Motor forward Pin
}

void backword() {  // Move Backward
  digitalWrite(in1, LOW);   // Right Motor forward Pin
  digitalWrite(in2, HIGH);  // Right Motor backward Pin
  digitalWrite(in3, HIGH);  // Left Motor backward Pin
  digitalWrite(in4, LOW);   // Left Motor forward Pin
}

void turnRight() {  // Turn Right
  digitalWrite(in1, LOW);   // Right Motor forward Pin
  digitalWrite(in2, HIGH);  // Right Motor backward Pin
  digitalWrite(in3, LOW);   // Left Motor backward Pin
  digitalWrite(in4, HIGH);  // Left Motor forward Pin
}

void turnLeft() {  // Turn Left
  digitalWrite(in1, HIGH);  // Right Motor forward Pin
  digitalWrite(in2, LOW);   // Right Motor backward Pin
  digitalWrite(in3, HIGH);  // Left Motor backward Pin
  digitalWrite(in4, LOW);   // Left Motor forward Pin
}

void Stop() {  // Stop Motors
  digitalWrite(in1, LOW);  // Right Motor forward Pin
  digitalWrite(in2, LOW);  // Right Motor backward Pin
  digitalWrite(in3, LOW);  // Left Motor backward Pin
  digitalWrite(in4, LOW);  // Left Motor forward Pin
}

void sowing() {
  // Activate sowing mechanism (servo or motor)
  servoPulse(sowingServo, 90);  // Rotate servo for sowing action
  delay(1000);
  servoPulse(sowingServo, 0);   // Return servo to original position
}

void waterPump() {
  digitalWrite(pump, HIGH);  // Turn on water pump
  delay(5000);  // Run pump for 5 seconds
  digitalWrite(pump, LOW);   // Turn off water pump
}

void servoPulse(int pin, int angle) {
  int pwm = (angle * 11) + 500;  // Convert angle to microseconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50);  // Servo refresh cycle
}

// Solar Power (Simulated for this example)
void checkSolarPower() {
  int solarVoltage = analogRead(A0);  // Read solar voltage (simulated)
  if (solarVoltage < 200) {
    lcd.clear();
    lcd.print("Low Solar Power");
  } else {
    lcd.clear();
    lcd.print("Solar Power OK");
  }
}
