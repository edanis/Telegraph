#include<SoftwareSerial.h>

// morse code lookup table
String morse_lookup[] = {
  ".-",    /*A*/   "-...",  /*B*/   "-.-.",  /*C*/   "-..",   /*D*/
  ".",     /*E*/   "..-.",  /*F*/   "--.",   /*G*/   "....",  /*H*/
  "..",    /*I*/   ".---",  /*J*/   "-.-",   /*K*/   ".-..",  /*L*/
  "--",    /*M*/   "-.",    /*N*/   "---",   /*O*/   ".--.",  /*P*/
  "--.-",  /*Q*/   ".-.",   /*R*/   "...",   /*S*/   "-",     /*T*/
  "..-",   /*U*/   "...-",  /*V*/   ".--",   /*W*/   "-..-",  /*X*/
  "-.--",  /*Y*/   "--..",  /*Z*/   ".----", /*1*/   "..---", /*2*/
  "...--", /*3*/   "....-", /*4*/   ".....", /*5*/   "-....", /*6*/
  "--...", /*7*/   "---..", /*8*/   "----.", /*9*/   "-----"  /*0*/
};

//Telegraph Constants
const int TELEGRAPH_PIN = 7;
const int DOT_DELAY = 75;  // milliseconds
const int DASH_DELAY = DOT_DELAY * 3;
const int ELEMENT_DELAY = DOT_DELAY;
const int CHARACTER_DELAY = DOT_DELAY * 2;
const int WORD_DELAY = DOT_DELAY * 6;


String lookupCode(char letter){
  switch (letter) {
    case 'A' : return morse_lookup[0];
    case 'B' : return morse_lookup[1]; 
    case 'C' : return morse_lookup[2];
    case 'D' : return morse_lookup[3];
    case 'E' : return morse_lookup[4];
    case 'F' : return morse_lookup[5];
    case 'G' : return morse_lookup[6];
    case 'H' : return morse_lookup[7];
    case 'I' : return morse_lookup[8];
    case 'J' : return morse_lookup[9];
    case 'K' : return morse_lookup[10];
    case 'L' : return morse_lookup[11];
    case 'M' : return morse_lookup[12];
    case 'N' : return morse_lookup[13];
    case 'O' : return morse_lookup[14];
    case 'P' : return morse_lookup[15];
    case 'Q' : return morse_lookup[16];
    case 'R' : return morse_lookup[17];
    case 'S' : return morse_lookup[18];
    case 'T' : return morse_lookup[19];
    case 'U' : return morse_lookup[20];
    case 'V' : return morse_lookup[21];
    case 'W' : return morse_lookup[22];
    case 'X' : return morse_lookup[23];
    case 'Y' : return morse_lookup[24];
    case 'Z' : return morse_lookup[25];
    case '1' : return morse_lookup[26];
    case '2' : return morse_lookup[27];
    case '3' : return morse_lookup[28];
    case '4' : return morse_lookup[29];
    case '5' : return morse_lookup[30];
    case '6' : return morse_lookup[31];
    case '7' : return morse_lookup[32];
    case '9' : return morse_lookup[33];
    case '0' : return morse_lookup[34];
    case ' ' : return " ";
    default: Serial.print("Unrecognized Character: "); Serial.println(letter); return " ";
    
  }
  
}

void sendDot(){
  digitalWrite(TELEGRAPH_PIN, LOW);
  delay(DOT_DELAY);
  digitalWrite(TELEGRAPH_PIN, HIGH);
  delay(ELEMENT_DELAY); 
}

void sendDash(){
  digitalWrite(TELEGRAPH_PIN, LOW);
  delay(DASH_DELAY);
  digitalWrite(TELEGRAPH_PIN, HIGH);
  delay(ELEMENT_DELAY);
}

void charEnd(){
  delay(CHARACTER_DELAY); 
}

void space(){
  delay(WORD_DELAY);
}

void char_send(char letter){
    String code = lookupCode(letter);
    Serial.print("Read Letter: "); Serial.print(letter);
    Serial.print(" Sending code: ");
    for (int i = 0; i < sizeof(code); i++){
      Serial.print(code[i]);
      switch(code[i]){
        case '.': sendDot(); break;
        case '-': sendDash(); break;
        case ' ': space(); Serial.println(); return;
        case '\0' : charEnd(); Serial.println(); return;
        default : Serial.print("Could not code: "); Serial.println(code[i]);
      } 
    }
    charEnd();
    
}

void setup(){
    Serial.begin(115200);  
    pinMode(TELEGRAPH_PIN, OUTPUT);
    digitalWrite(TELEGRAPH_PIN, HIGH);
}

void loop(){      
  if (Serial.available() > 0) {
      char_send(toupper(Serial.read()));
  } 
}
