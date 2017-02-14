#include <SoftwareSerial.h>

SoftwareSerial BT(0,1);

int speakerPin = 9;
int tempo = 300;
char inbyte;

//Canciones
char twinkle[] = "ccggaagffeeddc ";
char happyb[] = "ggagCb ggagCb ggCbfed ggecdc ";
char jinglebell[] = "eeeeeeegcde fffffeeeeddedg ";

int twinklebeats[] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 4 };
int happybbeats[] = {1, 1, 3, 3, 3, 5, 1, 1, 1, 3, 3,3, 5, 1, 1,1,3,3,3,3,5, 1,1,1,3,3,3,5,4 };
int jinglebellbeats[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 4 };

void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(tone);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = { 'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
  int tones[] = { 1915, 1700, 1519, 1432, 1275, 1136, 1014, 956 };

  // play the tone corresponding to the note name
  for (int i = 0; i < 8; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}

void setup() {
  BT.begin(9600);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  if (BT.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
 
    //store the first character in var inbyte
    inbyte = BT.read();
    if (inbyte == 'c' || inbyte == 'd' || inbyte == 'e' || inbyte == 'f' || inbyte == 'g' || inbyte == 'a' || inbyte == 'b' || inbyte == 'C') {
      playNote(inbyte, tempo);
    }
    else if(inbyte=='1'){playSong(twinkle,twinklebeats);}
    else if(inbyte=='2'){playSong(happyb,happybbeats);}
    else if(inbyte=='3'){playSong(jinglebell,jinglebellbeats);}

    // pause between notes
    delay(tempo / 2); 
  }
}

void playSong(char song[],int beats[]){
    for (int i = 0; i < strlen(song); i++) {
      if (song[i] == ' ') {
        delay(beats[i] * tempo); // rest
      } else {
        playNote(song[i], beats[i] * tempo);
      }
  
      // pause between notes
      delay(tempo / 2); 
  }
}
