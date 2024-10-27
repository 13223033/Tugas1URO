#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

// Setup a matrix keypad with 4 rows and 4 columns
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Connect the pins from right to left to pin 2, 3, 4, 5,6,7,8,9
byte rowPins[ROWS] = {9,8,7,6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5,4,3,2}; //connect to the column pinouts of the keypad

// Mapping the key to the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Define the initial variables
String pass = "29012005"; //PASSWORD
int buzz = 11; 
int alarm = 12;
int PIR = 13;
int currentposition = 0;
int invalidcount = 0;
String keyPressed = "";

void setup() {
  Serial.begin(9600);

  // Initialize the LCD
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();

  // Define the pinMode
  pinMode(buzz, OUTPUT);
  pinMode(alarm, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  // Initial screen
  if (currentposition == 0) {
    displayscreen();
  }

  // Check if the PIR sensor detects any motion
  if (digitalRead(PIR) == HIGH) {
    digitalWrite(alarm, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INTRUDER ALERT!");
    delay(5000);
    lcd.clear();
    currentposition = 0;
  }

  // Get the key pressed
  char key = keypad.getKey();

  // Check what key is pressed
  if (key != NO_KEY && key != '#' && key != '*') { // if a 'number' key is pressed
    keyPressed.concat(key);
    Serial.print(keyPressed);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PASSWORD:");
    keypress();
    lcd.setCursor(0, 1);

    lcd.print(keyPressed);
    ++currentposition;
  } else if (key == '#') { // if the '#' key is pressed, for Enter key, and then checking if the password is correct
    if (keyPressed == pass) { // if the password is correct
      alarmoff();
      currentposition = 0;
      keyPressed = "";
    } else { // if the password is incorrect
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("INVALID PASSWORD");
      delay(5000);
      currentposition = 0;
      keyPressed = "";
    }
  } else if (key == '*' and keyPressed.length() > 0) { // if the '*' key is pressed, for Backspace key
    keyPressed.remove(keyPressed.length() - 1);
    Serial.print(keyPressed);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PASSWORD:");
    keypress();
    lcd.setCursor(0, 1);

    lcd.print(keyPressed);
    --currentposition;
  }
}

// Function to display the initial screen
void displayscreen() {
  lcd.setCursor(0, 0);
  lcd.print("ENTER THE CODE");
  lcd.setCursor(2, 1);
  lcd.print("TO TURN OFF ALARM!");
}

// Function to make the buzzer sound each time a key get pressed
void keypress() {
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz, LOW);
}

// Function to turn off the alarm
void alarmoff() {
  digitalWrite(alarm, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM TURNED OFF");
  delay(5000);
  lcd.clear();
}