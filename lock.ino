#include <Keypad.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>

const int rs = 14, en = 15, d4 = 16, d5 = 17, d6 = 18, d7 = 19;
char keypressed;

const byte ROWS = 4; /* four rows */
const byte COLS = 4; /* four columns */
/* define the symbols on the buttons of the keypads */
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {4,5,6,7}; /* connect to the row pinouts of the keypad */
byte colPins[COLS] = {8,9,10,11}; /* connect to the column pinouts of the keypad */

char a[10]={'0','1','2','3','4','5','6','7','8','9'};
char PIN_buff_1[4]; char PIN_buff_2[4];
int q = 1;int m;int NewPinMatchCount;
int start_pos; int end_pos;
int p;int Access;int count;
char PIN[4]= {'4','5','4','5'};
int i; int c; int Cursor;

/* initialize an instance of class NewKeypad */
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(){
Serial.begin(9600);
startscreen();

}

void loop(){
  //Serial.print("in main loop");
  Access = 0; count = 0;p=0;
  keypressed = customKeypad.getKey();
     if(keypressed == '*')
    {
      //changing PIN
      keypressed = NO_KEY;
      ChangePin();
      startscreen();
    }
    
  if(keypressed == '#')
    {
      keypressed = NO_KEY;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print(" A   B    C   D ");
      EnterPin();    
      if (count == 4)
        verify();
      startscreen();
  } 
}
 



void ChangePin(){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Enter old Pin");
      Cursor = 0; c = 0; i=0;
      
      while(i < sizeof(PIN)){
          keypressed = customKeypad.getKey();
          if(keypressed != NO_KEY && keypressed != 'C'){
                  
                  lcd.setCursor(Cursor,1);                               
                  lcd.print(keypressed);
                  delay(500);
                  lcd.setCursor(Cursor,1);
                  lcd.print("*");
                  Serial.print("Cursor");Serial.println(Cursor);
                  Cursor++;
                  if(keypressed == PIN[i]){
                      c++;
                      Serial.print("c");Serial.println(c);Serial.print("i");Serial.println(i);
                  }
                  Serial.println(keypressed);
                  i++;
                  keypressed = NO_KEY;
                  }
            if (keypressed == 'C'){
             break; 
            }
          }
      if(c == 4){
        Serial.print("here");
        lcd.clear();
        lcd.print("Correct");
        delay(750);
        NewPinMatchCount = 0;
        keypressed = NO_KEY;
        ToGetnewPinOnce();
        keypressed = NO_KEY;
        ToGetnewPinAgain();
        CheckNewPin();
      }
      else{
        lcd.clear();
        lcd.print("Wrong Pin!");
        delay(750);
      }
}

void ToGetnewPinOnce(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter new PIN");
  i = 0; Cursor = 0;
  while(i < sizeof(PIN_buff_1)){
       keypressed = customKeypad.getKey();
       if(keypressed != NO_KEY && keypressed != 'C'){
        Serial.println(keypressed);
        lcd.setCursor(Cursor,1);                               
        lcd.print(keypressed);
        delay(500);
        lcd.setCursor(Cursor,1);
        lcd.print("*");
        Serial.print("Cursor");Serial.println(Cursor);
        Cursor++;
        PIN_buff_1[i] = keypressed;
        i++;
        keypressed = NO_KEY;
        }
        if (keypressed == 'C'){
               break; 
            }
  }
}

void ToGetnewPinAgain(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter it Again");
  i = 0; Cursor = 0;
   while(i < sizeof(PIN_buff_1) ){
       keypressed = customKeypad.getKey();
       if(keypressed != NO_KEY && keypressed != 'C'){
        Serial.println(keypressed);
        lcd.setCursor(Cursor,1);                               
        lcd.print(keypressed);
        delay(500);
        lcd.setCursor(Cursor,1);
        lcd.print("*");
        Serial.print("Cursor");Serial.println(Cursor);
        Cursor++;
        PIN_buff_2[i] = keypressed;
        i++;
        keypressed = NO_KEY;
        }
        if (keypressed == 'C'){
               break; 
            }
  }
}

void CheckNewPin(){
  for(int i = 0; i < 4; i++){
    if(PIN_buff_1[i] == PIN_buff_2[i])
      NewPinMatchCount++;
      Serial.print("NewPinMatchCount");Serial.println(NewPinMatchCount);
  }  
  if(NewPinMatchCount == 4){
    lcd.clear();
    lcd.print("PIN Changed");
    delay(1250);
    for(i=0 ; i<sizeof(PIN) ; i++){
        PIN[i]=PIN_buff_2[i];         //the code array now receives the new code
        EEPROM.put(i, PIN[i]);        //And stores it in the EEPROM
    }        
  }
  else{
    lcd.clear();
    lcd.print("PINs Dont Match!");
    delay(1250);
    NewPinMatchCount = 0;
    keypressed = NO_KEY;
    ToGetnewPinOnce();
    keypressed = NO_KEY;
    ToGetnewPinAgain();
    CheckNewPin();
  }
}

void EnterPin()
{
 //reshuffle(a,&q); 
    printseries(a);
    //Serial.print("in enter pin loop");
    //Serial.println(keypressed);Serial.print("Access");Serial.println(Access);Serial.print("count");Serial.println(count);
    while(count < sizeof(PIN) ){
          keypressed = customKeypad.getKey();
        
            if (keypressed == 'A'){
            start_pos = 0; end_pos = 2;count++; 
            match(a,PIN,start_pos, end_pos);
            reshuffle(a,&q);
            //Serial.print("Access");Serial.println(Access);Serial.print("count");Serial.println(count);
            }
            if (keypressed == 'B'){
              start_pos = 2; end_pos = 5;count++; 
              match(a,PIN,start_pos, end_pos);
              reshuffle(a,&q);
             // Serial.print("Access");Serial.println(Access);Serial.print("count");Serial.println(count);
            }
            if (keypressed == 'C'){
              
              start_pos = 5; end_pos = 8;count++;
              match(a,PIN,start_pos, end_pos);
              reshuffle(a,&q);
             // Serial.print("Access");Serial.println(Access);Serial.print("count");Serial.println(count);
            }
            if (keypressed == 'D'){
              
              start_pos = 8; end_pos = 10;count++;
              match(a,PIN,start_pos, end_pos);
              reshuffle(a,&q);
             // Serial.print("Access");Serial.println(Access);Serial.print("count");Serial.println(count);
            }
            if (keypressed == '5'){
               break; 
            }
        }
 // keypressed = NO_KEY;// verify();  Serial.println("in verify loop"); 
  
}



void reshuffle(char a[],int *q)
{
 // Serial.println("reshuffle");
      if(*q == 1)
        {
        reshuffleone(a, 10, 0); *q = 0;
        }
      
      else
        {
        swap(&a[0],&a[9]);
        reshuffleone(a, 8, 1);//Serial.print(q);
        *q=1;
        }
}
      
void reshuffleone(char a[] ,int n,int m)
{
  for (int j = m; j < n; j++)
        {
            swap(&a[j],&a[j+1]);
            j++;
        }
  printseries(a);
}

void swap(char* x,char* y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}


void printseries(char a[]){ 
  int j=0;
  lcd.setCursor(0,0);
  for (int i = 0; i<10; i++)
  {
    if(i == 2 || i == 5 || i == 8){
    lcd.print("  ");
    }
    
    lcd.print(a[j]);
    j++;
  }
  
}

void match(char a[], char PIN[],int start_pos,int end_pos){
 // Serial.println("match");
  for(int i = start_pos; i < end_pos; i++) {
   // Serial.println("p");Serial.println(p);
    if (PIN[p] == a[i]){
      Access++;
     // Serial.print("Access");Serial.print(Access);Serial.print("count");Serial.print(count);
      
      p++;
    }
  }
}

void verify(){
  //Serial.println("in verify loop");
  if(Access == 4){
        lcd.clear();
        lcd.print("Access Granted!");delay(800);
        //Serial.print("Access");Serial.print(Access);Serial.print("count");Serial.print(count);
        
        //Serial.print(keypressed);
        }
     else{
        lcd.clear();
        lcd.print("Wrong PIN!");delay(850);Serial.print("Wrong PIN!");
        //Serial.print("Access");Serial.print(Access);Serial.print("count");Serial.print(count);
     }
  
}


void startscreen(){
  
  Serial.println("restart screen");
//  for(i=0 ; i<sizeof(PIN);i++){        //When you upload the code the first time keep it commented
//      EEPROM.get(i, PIN[i]);             //Upload the code and change it to store it in the EEPROM
//      Serial.print(PIN[i]); 
//      }   
    for(i=0 ; i<sizeof(PIN);i++)      
        Serial.print(PIN[i]); 
              
  lcd.clear();
  Serial.println("  # Enter Pin");
  Serial.println(" * Change Pin");
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("  # Enter Pin");
  lcd.setCursor(0,1);
  lcd.print("  * Change Pin");
  keypressed = NO_KEY;
 
}
