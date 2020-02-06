//피에조 스피커 노래

#include "pitches.h"

int melody[] = {NOTE_G4, NOTE_G4, NOTE_A5, NOTE_A5, NOTE_G4, NOTE_G4, NOTE_E4,
                NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, 0,
                NOTE_G4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4,
                NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_C4
               };
int noteDurations[] = {  1, 1, 1, 1, 1, 1, 2,
                        1, 1, 1, 1, 3,
                        1, 1, 1, 1, 1, 1, 2,
                        1, 1, 1, 3, 1
                     };

void setup() {  
  for (int i = 0; i < sizeof(melody)/sizeof(int); i++) {
    int noteDuration = 250 * noteDurations[i];
    tone(8, melody[i], noteDuration);
    int pause = noteDuration * 1.30;
    delay(pause); // 스피커에서 소리가 나도록 기다려주는 것이다.
    noTone(8); //스피커 소리를 하나씩 끊어서 출력 시키게 하는 것
  }
}

void loop() {
  

}
