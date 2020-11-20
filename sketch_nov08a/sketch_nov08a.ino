#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978 
//define three inputs as volatile
volatile uint16_t buttonState = 0;
volatile uint16_t sliderState = 0;
volatile uint16_t previousSliderState = 0;
volatile uint16_t photoState = 0;

//define input pin assignments
const uint8_t sliderPin = A0;
const uint8_t buttonPin = A2;
const uint8_t photoPin = A1;


//define output pin assignments
const uint8_t counterPin = 0;
const uint8_t buttonPromptPin = 3;
const uint8_t sliderPromptPin = 7;
const uint8_t photoPromptPin = 4;
const uint8_t yellowLedPin = 1;
const uint8_t speakerPin = 9;
const uint8_t voicePlayPin = 5;
const uint8_t voicePausePin = 6;
const uint8_t resetPin = 2;


//define random number variable
long randNum = 0;


uint8_t melodyNoteLength = 8;
int melody[] = {200, 500, 270, 700, 20, 340, 210, 210};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};

uint8_t lostMelodyNoteLength = 8;
int lostMelody[] = {800, 400, 600, 300, 500, 100, 200, 200};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int lostnoteDurations[] = {8, 8, 8, 8, 8, 8, 8, 1};


uint8_t wonMelodyNoteLength = 6 ;
int wonMelody[] = {  100, 200, 500, 300, 500, 700};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int wonnoteDurations[] = {4, 4, 4, 2, 4, 1};


//define wait time variable in millisconds
volatile unsigned long long waitTime = 6000;
volatile unsigned long long previousTime = 0;
volatile unsigned long long currentTime = 0;
volatile unsigned long long decrementAmount = 50;

//next user instruction flag
volatile bool flag = true;
volatile bool win = false;
volatile bool play = false;

//keep track of score
uint8_t score = 0;

                           
volatile void buttonSequence();
volatile void sliderSequence();
volatile void photoSequence();
volatile void resetSequence();
volatile void playDarude();

void setup() {
  //THIS MUST BE FIRST
  digitalWrite(resetPin, HIGH);
  delay(100);


 
  // put your setup code here, to run once:

  previousTime = millis();
  
  //set pins to output mode
  pinMode(resetPin, OUTPUT);
  delay(10);
  pinMode(counterPin, OUTPUT);
  delay(10);
  pinMode(buttonPromptPin, OUTPUT);
  delay(10);
  pinMode(sliderPromptPin, OUTPUT);
  delay(10);
  pinMode(photoPromptPin, OUTPUT);
  delay(10);
  pinMode(yellowLedPin, OUTPUT);
  delay(10);
  pinMode(speakerPin, OUTPUT);
  delay(10);
  pinMode(voicePlayPin, OUTPUT);
  delay(10);
  pinMode(voicePausePin, OUTPUT);
  delay(10);
  
  //set pins to input mode
  pinMode(sliderPin, INPUT);
  delay(10);
  pinMode(buttonPin, INPUT);
  delay(10);
  pinMode(photoPin, INPUT);
  delay(10);
 
  //display usually start at 80 when first plugged in
  //change sync variable to true to run sync
  //change difference variable to sync properly
  bool SYNC = false;
  int difference = 20;
  int i = 0;
  while(i < 20 && SYNC){
    digitalWrite(counterPin, HIGH);
    delay(10);
    digitalWrite(counterPin, LOW);
    delay(10);
    i++;
  }
  randomSeed(0);

  //play ready to play tone
  for (int thisNote = 0; thisNote < melodyNoteLength; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speakerPin);

  }
  win = false;
  flag = true;
  play = false;
}



void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(buttonPin) == HIGH){
    play = true;
  }
  //select input prompt
  if(play){  
    if(flag){
      randNum = random(3);
      flag = false;
      delay(30);
    }
    delay(30);//slow program down
    previousTime = millis();
    switch(randNum){
        case 0:
          digitalWrite(buttonPromptPin,HIGH);
          buttonSequence();
          digitalWrite(buttonPromptPin,LOW);
          break;
        case 1:
          digitalWrite(sliderPromptPin,HIGH);
          sliderSequence();
          digitalWrite(sliderPromptPin,LOW);
          break;
        case 2:
          digitalWrite(photoPromptPin, HIGH);
          photoSequence();
          digitalWrite(photoPromptPin, LOW);
          break;
    }
    delay(30);//slow program down
    
    if(!win){
      //play lose 

     
      for (int thisNote = 0; thisNote < lostMelodyNoteLength; thisNote++) {
  
        // to calculate the note duration, take one second divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc
        int lostnoteDuration = 1000 / lostnoteDurations[thisNote];
        tone(speakerPin, lostMelody[thisNote], lostnoteDuration);
    
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
    
        int lostpauseBetweenNotes = lostnoteDuration * 1.30;
        delay(lostpauseBetweenNotes);
        // stop the tone playing:
        noTone(speakerPin);
  
      }
      
      //blink score
      
      resetSequence();
    }else if(win){
     
      //play win
   
      //add to score
      score ++;
      
      digitalWrite(counterPin, HIGH);
      delay(10);
      digitalWrite(counterPin, LOW);
      delay(10);
      
      //--interval
      if(waitTime > decrementAmount){
        waitTime -= decrementAmount;
      }
      win = false;
    }
    
    //delay(3);//slow program down
    
    //play win tone
    if(score == 99){
      playDarude();
      playDarude();
      playDarude();
      //reset game
      resetSequence();
    }
  }
}


volatile void buttonSequence(){
  
  while(!flag){
    
    currentTime = millis();//get current time
    buttonState = digitalRead(buttonPin);//get current state
    if(currentTime - previousTime >= waitTime){// check time for operation
     win = false;//exits with time up option
     flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(buttonState == HIGH){//check if button was press
      tone(speakerPin,NOTE_E4);
      delay(100);
      noTone(speakerPin);
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
    }  
  }
}

volatile void sliderSequence(){
 
  previousSliderState = digitalRead(sliderPin);
  while(!flag){
    
    currentTime = millis();//get current time
    sliderState = digitalRead(sliderPin);//get current state
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;//exits with time up option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(sliderState != previousSliderState){//check if button was press
       tone(speakerPin,NOTE_D4);
      delay(100);
      noTone(speakerPin);
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
    }
    
  }
}

volatile void photoSequence(){
  //delay(30);
  while(!flag){
  
    currentTime = millis();//get current time
    photoState = analogRead(photoPin);//get current state
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;//exits with time up option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(10 == photoState){//check if button was press
       tone(speakerPin,NOTE_C4);
      delay(100);
      noTone(speakerPin);
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }  
  }
}

volatile void resetSequence(){
    delay(1000);

    while(score < 100){
      digitalWrite(counterPin, HIGH);
      delay(10);
      digitalWrite(counterPin, LOW);
      delay(10);
      score ++;
    }
    play = false;
    score = 0;
    //reset game
    delay(1000);
    digitalWrite(resetPin, LOW);

}

volatile void playDarude(){
 int shortTone = 80; //Length of Short Note
 int longTone = 200; //Length of Long Note
 int standardDelay = 40; //Delay
 int delayBetweenBars = 50; //Delay

  
  for(int k = 0; k <4; k++){
    tone(speakerPin,  NOTE_B3, shortTone);
    delay(shortTone); 
    noTone(speakerPin); 
    delay(standardDelay);
  }
  tone(speakerPin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(speakerPin);

  
  delay(delayBetweenBars);
  
  for(int k = 0; k<6; k++){
    tone(speakerPin,  NOTE_B3, shortTone);
    delay(shortTone);
    noTone(speakerPin);
    delay(standardDelay); 
  }
  
  tone(speakerPin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);
  
  for(int k = 0; k < 6; k++){
    tone(speakerPin,  NOTE_E4, shortTone);
    delay(shortTone);
    noTone(speakerPin);
    delay(standardDelay); 
    
  }
  
  tone(speakerPin,  NOTE_E4, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);
 
  for(int k = 0; k < 6; k++){
    tone(speakerPin,  NOTE_D4, shortTone); //Play tone, PinspeakerPin, note, length of note
    delay(shortTone); //Length of delay
    noTone(speakerPin); //Stop tone
    delay(standardDelay); 
    
  }
  tone(speakerPin,  NOTE_D4, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);

  tone(speakerPin, NOTE_A3, longTone);
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);

  
  for(int k = 0; k <4; k++){
    tone(speakerPin,  NOTE_B3, shortTone);
    delay(shortTone); 
    noTone(speakerPin); 
    delay(standardDelay);
  }

  tone(speakerPin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(delayBetweenBars);
 
  for(int k = 0; k<6; k++){
    tone(speakerPin,  NOTE_B3, shortTone);
    delay(shortTone);
    noTone(speakerPin);
    delay(standardDelay); 
  }

  
  tone(speakerPin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);
 
  tone(speakerPin, NOTE_E4, longTone);
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);

  for(int k = 0; k <4; k++){
    tone(speakerPin,  NOTE_B3, shortTone);
    delay(shortTone); 
    noTone(speakerPin); 
    delay(standardDelay);
  }

  
  tone(speakerPin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(delayBetweenBars);
 
  for(int k = 0; k<6; k++){
    tone(speakerPin,  NOTE_B3, shortTone);
    delay(shortTone);
    noTone(speakerPin);
    delay(standardDelay); 
  }

  
  tone(speakerPin,  NOTE_B3, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);

  tone(speakerPin, NOTE_E4, longTone); 
  delay(longTone);
  noTone(speakerPin);
  delay(standardDelay);  
  
}
