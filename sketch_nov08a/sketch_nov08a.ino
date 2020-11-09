

#define     PRSCLR   1024   
//define three inputs as volatile
volatile uint8_t buttonState = 0;
volatile uint16_t sliderState = 0;
volatile uint16_t previousSliderState = 0;
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
long randNum = 0;



//define wait time variable in millisconds
unsigned long long waitTime = 6000;
unsigned long long previousTime = 0;
unsigned long long currentTime = 0;
unsigned long long decrementAmount = 50;

//next user instruction flag
bool flag = true;
bool win = false;


//keep track of score
uint8_t score = 0;

//create tones
unsigned int correctTone[3] = { 220, 277, 300};
unsigned int wrongTone[3] = {300, 277, 220};
unsigned int winTone[12] = { 220, 277, 300, 220, 277, 300, 220, 277, 300, 220, 277, 300};
unsigned int readyTone[7] = {200, 250, 300, 250, 200, 250, 300};
                                  
//playing one note
void playfreq(unsigned int freq);

void playWinSound();
void playLoseSount();
void playStartSound();
void playRightSound();
void buttonSequence();
void sliderSequence();
void photoSequence();

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


  //set up speaker output
  //PB1 pin in OUTPUT mode
  DDRB |= ( 1 << DDB1 );

  TCCR1A = 0b0;
  //non-inverting mode of PWM
  TCCR1A |= ( 1 << COM1A1 ) | ( 1 << COM1B1 );
  //Fast mode PWM with ICR1 as TOP:
  TCCR1A |= ( 1 << WGM11 );
  TCCR1B = 0b0;
  TCCR1B |= ( 1 << WGM12 ) | ( 1 << WGM13 );
  //prescaler = 1024
  TCCR1B |= ( 1 << CS12 ) | ( 1 << CS10 );

  //play ready to play tone
  for(int i = 0; i <7; i++){
      playfreq(readyTone[i]);
      delay(100);
    }
}



void loop() {
  // put your main code here, to run repeatedly:

  //select input prompt
  
  if(flag){
    randNum = random(3);
    flag = false;
  }
  delay(3);//slow program down
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
  delay(3);//slow program down
  
  if(!win){
    //play lose 
    for(int i = 0; i <3; i++){
      playfreq(wrongTone[i]);
      delay(100);
    }
    //blink score
    //reset game
    digitalWrite(resetPin, LOW);
  
  }else{
   
    //play win
    for(int i = 0; i <3; i++){
      playfreq(wrongTone[i]);
      delay(100);
    }
   
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
  if(score == 99){
    for(int i = 0; i <12; i++){
      playfreq(winTone[i]);
      delay(80);
    }
    //reset game
    digitalWrite(resetPin, LOW);
  }
  
}

void playfreq( unsigned int freq )
{
    //claclulate TOP according to note frequency
    ICR1 = F_CPU / PRSCLR / freq - 1;
    //50% duty cycle
    OCR1A = ICR1 / 2;
}


void buttonSequence(){
  
  while(!flag){
    
    currentTime = millis();//get current time
    
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;//exits with time up option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(buttonState == HIGH){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
    
    }else{
      buttonState = digitalRead(buttonPin);//get current state
    }  
  }
}

void sliderSequence(){
  previousSliderState = analogRead(sliderPin);
  
  while(!flag){
    
    currentTime = millis();//get current time
    
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;//exits with time up option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(previousSliderState != sliderPin){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else{
      sliderState = analogRead(sliderPin);//get current state
    }  
  }
}

void photoSequence(){
  previousPhotoState = analogRead(photoPin);
 
  while(!flag){
  
    currentTime = millis();//get current time
   
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;//exits with time up option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else if(previousPhotoState != photoState){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
   
    }else{
      photoState = analogRead(photoPin);//get current state
    }  
  }
}
