// Pin Definitions
// Rows are connected to
const int row1 = 8;

const int row2 = 7;

const int row3 = 6;

const int row4 = 5;

const int row5 = 4;

const int row6 = 3;

const int row7 = 2;


// The 74HC595 uses a serial communication
// link which has three pins
const int clock = 9;
const int latch = 10;
const int data = 11;


uint8_t keyToMidiMap[54];

boolean keyPressed[54];

int noteVelocity = 127;


// use prepared bit vectors instead of shifting bit left everytime
int bits[] = {
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111

//  B00000001,  //use in case of pull down configuration
//  B00000010,
//  B00000100,
//  B00001000,
//  B00010000,
//  B00100000,
//  B01000000,
//  B10000000
};


// 74HC595 shift to next column
void scanColumn(int value) {
digitalWrite(latch, LOW); //Pulls the chips latch low
shiftOut(data, clock, MSBFIRST, value); //Shifts out the 8 bits to the shift register
digitalWrite(latch, HIGH); //Pulls the latch high displaying the data
}

void setup() {

// Map scan matrix buttons/keys to actual Midi note number. Lowest num 41 corresponds to F MIDI note.


keyToMidiMap[0] = 55;
keyToMidiMap[1] = 48;
keyToMidiMap[2] = 49;
keyToMidiMap[3] = 50;
keyToMidiMap[4] = 51;
keyToMidiMap[5] = 52;
keyToMidiMap[6] = 53;
keyToMidiMap[7] = 54;

keyToMidiMap[8] = 63;
keyToMidiMap[1 + 8] = 56;
keyToMidiMap[2 + 8] = 57;
keyToMidiMap[3 + 8] = 58;
keyToMidiMap[4 + 8] = 59;
keyToMidiMap[5 + 8] = 60;
keyToMidiMap[6 + 8] = 61;
keyToMidiMap[7 + 8] = 62;

keyToMidiMap[16] = 71;
keyToMidiMap[1 + 16] = 64;
keyToMidiMap[2 + 16] = 65;
keyToMidiMap[3 + 16] = 66;
keyToMidiMap[4 + 16] = 67;
keyToMidiMap[5 + 16] = 68;
keyToMidiMap[6 + 16] = 69;
keyToMidiMap[7 + 16] = 70;

keyToMidiMap[24] = 79;
keyToMidiMap[1 + 24] = 72;
keyToMidiMap[2 + 24] = 73;
keyToMidiMap[3 + 24] = 74;
keyToMidiMap[4 + 24] = 75;
keyToMidiMap[5 + 24] = 76;
keyToMidiMap[6 + 24] = 77;
keyToMidiMap[7 + 24] = 78;

keyToMidiMap[32] = 87;
keyToMidiMap[1 + 32] = 80;
keyToMidiMap[2 + 32] = 81;
keyToMidiMap[3 + 32] = 82;
keyToMidiMap[4 + 32] = 83;
keyToMidiMap[5 + 32] = 84;
keyToMidiMap[6 + 32] = 85;
keyToMidiMap[7 + 32] = 86;

keyToMidiMap[40] = 95;
keyToMidiMap[1 + 40] = 88;
keyToMidiMap[2 + 40] = 89;
keyToMidiMap[3 + 40] = 90;
keyToMidiMap[4 + 40] = 91;
keyToMidiMap[5 + 40] = 92;
keyToMidiMap[6 + 40] = 93;
keyToMidiMap[7 + 40] = 94;

keyToMidiMap[48] = 103;
keyToMidiMap[1 + 48] = 96;
keyToMidiMap[2 + 48] = 97;
keyToMidiMap[3 + 48] = 98;
keyToMidiMap[4 + 48] = 99;
keyToMidiMap[5 + 48] = 100;
keyToMidiMap[6 + 48] = 101;
keyToMidiMap[7 + 48] = 102;

keyToMidiMap[56] = 111;
keyToMidiMap[1 + 56] = 104;
keyToMidiMap[2 + 56] = 105;
keyToMidiMap[3 + 56] = 106;
keyToMidiMap[4 + 56] = 107;
keyToMidiMap[5 + 56] = 108;
keyToMidiMap[6 + 56] = 109;
keyToMidiMap[7 + 56] = 110;

// setup pins output/input mode
pinMode(data, OUTPUT);
pinMode(clock, OUTPUT);
pinMode(latch, OUTPUT);

pinMode(row1, INPUT);
pinMode(row2, INPUT);
pinMode(row3, INPUT);
pinMode(row4, INPUT);
pinMode(row5, INPUT);
pinMode(row6, INPUT);
pinMode(row7, INPUT);

Serial.begin(57600);

delay(1000);
}


void loop() {

  for (int col = 0; col < 8; col++) {

    // shift scan matrix to following column
    scanColumn(bits[col]);

    // check if any keys were pressed - rows will have HIGH output in this case corresponding
    int groupValue1 = !digitalRead(row1); //remove "!" in case of pull down configuration
    int groupValue2 = !digitalRead(row2);
    int groupValue3 = !digitalRead(row3);
    int groupValue4 = !digitalRead(row4);
    int groupValue5 = !digitalRead(row5);
    int groupValue6 = !digitalRead(row6);
    int groupValue7 = !digitalRead(row7);

    // process if any combination of keys pressed
    if (groupValue1 != 0 || groupValue2 != 0 || groupValue3 != 0
        || groupValue4 != 0 || groupValue5 != 0 || groupValue6 != 0 || groupValue7 != 0){

      if (groupValue1 != 0 && !keyPressed[col]) {
        keyPressed[col] = true;
        noteOn(0x91, keyToMidiMap[col], noteVelocity);
      }

      if (groupValue2 != 0 && !keyPressed[col + 8]) {
        keyPressed[col + 8] = true;
        noteOn(0x91, keyToMidiMap[col + 8], noteVelocity);
      }

      if (groupValue3 != 0 && !keyPressed[col + 16]) {
        keyPressed[col + 16] = true;
        noteOn(0x91, keyToMidiMap[col + 16], noteVelocity);
      }

      if (groupValue4 != 0 && !keyPressed[col + 24]) {
        keyPressed[col + 24] = true;
        noteOn(0x91, keyToMidiMap[col + 24], noteVelocity);
      }  
      
      if (groupValue5 != 0 && !keyPressed[col + 32]) {
        keyPressed[col + 32] = true;
        noteOn(0x91, keyToMidiMap[col + 32], noteVelocity);
      }
      
      if (groupValue6 != 0 && !keyPressed[col + 40]) {
        keyPressed[col + 40] = true;
        noteOn(0x91, keyToMidiMap[col + 40], noteVelocity);
      } 

      if (groupValue7 != 0 && !keyPressed[col + 48]) {
        keyPressed[col + 48] = true;
        noteOn(0x91, keyToMidiMap[col + 48], noteVelocity);
      } 
   }

    //  process if any combination of keys released
    if (groupValue1 == 0 && keyPressed[col]) {
      keyPressed[col] = false;
      noteOn(0x91, keyToMidiMap[col], 0);
    }

    if (groupValue2 == 0 && keyPressed[col + 8]) {
      keyPressed[col + 8] = false;
      noteOn(0x91, keyToMidiMap[col + 8], 0);
    }

    if (groupValue3 == 0 && keyPressed[col + 16]) {
      keyPressed[col + 16] = false;
      noteOn(0x91, keyToMidiMap[col + 16], 0);
    }

    if (groupValue4 == 0 && keyPressed[col + 24]) {
      keyPressed[col + 24] = false;
      noteOn(0x91, keyToMidiMap[col + 24], 0);
    }

    if (groupValue5 == 0 && keyPressed[col + 32]) {
      keyPressed[col + 32] = false;
      noteOn(0x91, keyToMidiMap[col + 32], 0);
    }

    if (groupValue6 == 0 && keyPressed[col + 40]) {
      keyPressed[col + 40] = false;
      noteOn(0x91, keyToMidiMap[col + 40], 0);
    }
    
    if (groupValue7 == 0 && keyPressed[col + 48]) {
      keyPressed[col + 48] = false;
      noteOn(0x91, keyToMidiMap[col + 48], 0);
    }

  }

}


void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}
