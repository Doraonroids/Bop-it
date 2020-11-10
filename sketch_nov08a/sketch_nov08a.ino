

#define     PRSCLR   1024   
//define three inputs as volatile
volatile uint8_t buttonState = 0;
volatile uint16_t sliderState = HIGH;
volatile uint16_t previousSliderState = HIGH;
volatile uint16_t photoState = 0;
volatile uint16_t previousPhotoState = 0;


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
volatile long randNum = 0;



int melody[] = {200, 500, 270, 700, 20, 340, 210, 210};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {4, 8, 8, 4, 4, 4, 4, 4};


int lostMelody[] = {800, 400, 600, 300, 500, 100, 200, 200};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int lostnoteDurations[] = {8, 8, 8, 8, 8, 8, 8, 1};


int wonMelody[] = {  100, 200, 500, 300, 500, 700};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int wonnoteDurations[] = {4, 4, 4, 2, 4, 1, 1};


//define wait time variable in millisconds
volatile unsigned long long waitTime = 6000;
volatile unsigned long long previousTime = 0;
volatile unsigned long long currentTime = 0;
volatile unsigned long long decrementAmount = 50;

//next user instruction flag
volatile bool flag = true;
volatile bool win = false;


//keep track of score
uint8_t score = 0;

                           
volatile void buttonSequence();
volatile void sliderSequence();
volatile void photoSequence();

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
 
  randomSeed(analogRead(0));

 
  //play ready to play tone
  for (int thisNote = 0; thisNote < 8; thisNote++) {

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
    
}



void loop() {
  // put your main code here, to run repeatedly:
  
  //select input prompt
  
  if(flag){
    randNum = random(3);
    //randNum = 1;
    delay(30);
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
  delay(3000);//slow program down
  
  if(!win){
    //play lose 
    for (int thisNote = 0; thisNote < 8; thisNote++) {

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
    //reset game
    delay(1000);
    digitalWrite(resetPin, LOW);
  
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
  
  delay(3);//slow program down
  
  //play win tone
  if(score == 10){
    for (int thisNote = 0; thisNote < 8; thisNote++) {

      // to calculate the note duration, take one second divided by the note type.
  
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc
      int wonnoteDuration = 1000 / wonnoteDurations[thisNote];
      tone(speakerPin, wonMelody[thisNote], wonnoteDuration);
  
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
  
      int wonpauseBetweenNotes = wonnoteDuration * 1.30;
      delay(wonpauseBetweenNotes);
      // stop the tone playing:
      noTone(speakerPin);

    }
    //reset game
    delay(1000);
    digitalWrite(resetPin, LOW);
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
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
    }  
  }
}

volatile void sliderSequence(){
  delay(500);
 
  while(!flag){
    
    currentTime = millis();//get current time
    sliderState = digitalRead(sliderPin);//get current state
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;//exits with time up option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(sliderState != previousSliderState){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
      delay(200);
      previousSliderState = sliderState;
    }
  }
}

volatile void photoSequence(){
  delay(500);
  previousPhotoState = analogRead(photoPin) - 275 ;
 
  while(!flag){
  
    currentTime = millis();//get current time
   
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;//exits with time up option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(previousPhotoState > photoState){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }
    photoState = analogRead(photoPin);//get current state
      
  }
}
