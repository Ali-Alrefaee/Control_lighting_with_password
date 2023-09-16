/**********************************************************************************************/
/** Desc    : Control room lighting with a password                                     */
/** Author  : 3li Al_Refaee                                                                 */
/** Date    : 8 july 2023                                                                  */
/** version : 1.0v                                                                        */
/*****************************************************************************************/

#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>



const String password = "1234567";
String password_entered;

const byte ROWS = 4; // 4 lines
const byte COLS = 3; // 3 columns
char keys [ROWS] [COLS] ={
  { '1', '2', '3'},
  { '4', '5', '6'},
  { '7', '8', '9'},
  { '*', '0', '#'}
};
// Connect the keyboard to 10 11 12 (columns) and 6 7 8 9  (lines)
byte rowPins [ROWS] = {6,7,8,9}; // Lines
byte colPins [COLS] = {10,11,12}; // Columns

const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Initialize an instance of the keypad class
Keypad keypad = Keypad(makeKeymap (keys), rowPins, colPins, ROWS, COLS);
void setup(){
  lcd.begin(16, 2);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  // to activate the HOLD state
  unsigned int time_hold = 4;
  keypad.setHoldTime(time_hold);
  // Anti rebound
  unsigned int time_anti_rebond = 4; // 4 ms
  keypad.setDebounceTime(time_anti_rebond);

//  lcd.init();
//  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Don't wake ALI,");
   lcd.setCursor(0,1);
  lcd.print(" Please.");
  delay(5000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter password: ");
  lcd.setCursor(0,1);
  password_entered = "";

  while(password_entered.length() <7){
    char key = keypad.getKey ();
    if(key != NO_KEY){
      password_entered += key;
      lcd.print(key);
    }
  }
  if(password_entered == password){
    delay(500);
    digitalWrite(13, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OK,you did it !");
    delay(5000);
    //digitalWrite(12, LOW);
  }
  else{
    delay(500);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("hahahah password");
    lcd.setCursor(0,1);
    lcd.print(" ERROR bitch !");
    digitalWrite(13, LOW);
    delay(5000);
  }
}
