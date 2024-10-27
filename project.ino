#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // atur address LCD I2C ke 0x27 untuk tampilan 16 karakter dan 2 baris

// Mengatur keypad matriks dengan 4 baris dan 4 kolom
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Hubungkan pin dari kanan ke kiri (di hardware Keypad-nya) ke pin 2, 3, 4, 5, 6, 7, 8, 9
byte rowPins[ROWS] = {9,8,7,6}; //hubungkan ke pin baris dari keypad
byte colPins[COLS] = {5,4,3,2}; //hubungkan ke pin kolom dari keypad

// Memetakan key ke keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Mendefinisikan variabel awal
String pass = "29012005"; // PASSWORD
int buzz = 11; 
int alarm = 12;
int PIR = 13;
int currentposition = 0;
int invalidcount = 0;
String keyPressed = "";

void setup() {
  Serial.begin(9600);

  // Inisialisasi LCD
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();

  // Mendefinisikan pinMode
  pinMode(buzz, OUTPUT);
  pinMode(alarm, OUTPUT);
  pinMode(PIR, INPUT);
}

void loop() {
  // Tampilan awal
  if (currentposition == 0) {
    displayscreen();
  }

  // Periksa apakah sensor PIR mendeteksi gerakan
  if (digitalRead(PIR) == HIGH) {
    digitalWrite(alarm, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PERINGATAN PENCURI!");
    delay(5000);
    lcd.clear();
    currentposition = 0;
  }

  // Get key yang ditekan
  char key = keypad.getKey();

  // Periksa key apa yang ditekan
  if (key != NO_KEY && key != '#' && key != '*') { // jika key berbentuk angka ditekan
    keyPressed.concat(key);
    Serial.print(keyPressed);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("KATA SANDI:");
    keypress();
    lcd.setCursor(0, 1);

    lcd.print(keyPressed);
    ++currentposition;
  } else if (key == '#') { // jika key '#' ditekan (sebagai tombol Enter), kemudian memeriksa apakah password benar
    if (keyPressed == pass) { // jika password benar
      alarmoff();
      currentposition = 0;
      keyPressed = "";
    } else { // jika password salah
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("KATA SANDI SALAH");
      delay(5000);
      currentposition = 0;
      keyPressed = "";
    }
  } else if (key == '*' && keyPressed.length() > 0) { // jika key '*' ditekan, sebagai tombol Backspace
    keyPressed.remove(keyPressed.length() - 1);
    Serial.print(keyPressed);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("KATA SANDI:");
    keypress();
    lcd.setCursor(0, 1);

    lcd.print(keyPressed);
    --currentposition;
  }
}

// Fungsi untuk menampilkan layar awal
void displayscreen() {
  lcd.setCursor(0, 0);
  lcd.print("MASUKKAN KODE");
  lcd.setCursor(0, 1);
  lcd.print("UNTUK MEMATIKAN ALARM!");
}

// Fungsi untuk membuat buzzer berbunyi setiap kali keypad ditekan
void keypress() {
  digitalWrite(buzz, HIGH);
  delay(50);
  digitalWrite(buzz, LOW);
}

// Fungsi untuk mematikan alarm
void alarmoff() {
  digitalWrite(alarm, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ALARM DIMATIKAN");
  delay(5000);
  lcd.clear();
}
