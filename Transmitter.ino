#include <LiquidCrystal.h>

// Transmit rate of 5 bps
#define TX_RATE 5

// Pin assignments
#define TX_CLOCK 2
#define TX_DATA 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_RS 8
#define LCD_EN 9

const char *message = "Hello, world!";

void setup() {
  pinMode(TX_CLOCK, OUTPUT);
  pinMode(TX_DATA, OUTPUT);

  // Initialize the LCD
  LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print(message);

  for (int byte_idx = 0; byte_idx < strlen(message); byte_idx++){
    char tx_byte = message[byte_idx];

    // Turn off cursor
    lcd.noCursor();

    // Clear second line of the LCD
    lcd.setCursor(0,1);
    lcd.print("        ");
    
    // Point cursor to the character being transmitted
    lcd.setCursor(byte_idx, 0);

    // Turn cursor on
    lcd.cursor();
    
    for (int bit_idx = 0; bit_idx <8; bit_idx++){
      bool tx_bit = tx_byte & (0x80 >> bit_idx);

      digitalWrite(TX_DATA, tx_bit);
      /* Delay for half of bit time
      Used to set up a pulse clock to make the transmission and reciever more reliable and accurate */
      delay((1000 / TX_RATE) / 2);
      
      // Update the LCD
      lcd.noCursor();
      lcd.setCursor(bit_idx, 1);
      lcd.print(tx_bit ? "1" : "0");
      // Point cursor to the character being transmitted
      lcd.setCursor(byte_idx, 0);
      // Turn cursor on
      lcd.cursor();

      // Pulse Clock
      digitalWrite(TX_CLOCK, HIGH);
      delay((1000 / TX_RATE) / 2);
      digitalWrite(TX_CLOCK, LOW);
    }
  }
  digitalWrite(TX_DATA, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
