



//define three inputs as volatile
volatile uint8_t buttonState = 0;
volatile uint16_t sliderState = 0;
volatile uint16_t previousSliderState = 0;
volatile uint16_t photoState = 0;
volatile uint16_t previousPhotoState = 0;


//define input pin assignments
const uint8_t sliderPin = 1;
const uint8_t buttonPin = 1;
const uint8_t photoPin = 1;


//define output pin assignments
const uint8_t counterPin = 1;
const uint8_t buttonPromptPin = 1;
const uint8_t sliderPromptPin = 1;
const uint8_t photoPromptPin = 1;
const uint8_t yellowLedPin = 1;
const uint8_t speakerPin = 1;
const uint8_t voicePlayPin = 1;
const uint8_t voicePausePin = 1;
const uint8_t voiceNextPin = 1;



//define random number variable
long randNum = 0;



//define wait time variable in millisconds
unsigned long long waitTime = 3000;
unsigned long long previousTime = 0;
unsigned long long currentTime = 0;


//next user instruction flag
bool flag = true;
bool win = false;


//keep track of score
uint8_t score = 0;


void playWinSound();
void playLoseSount();
void playStartSound();
void playRightSound();
void buttonSequence();
void sliderSequence();
void photoSequence();

void setup() {
  // put your setup code here, to run once:

  previousTime = millis();
  
  //set pins to output mode
  pinMode(counterPin, OUTPUT);
  pinMode(buttonPromptPin, OUTPUT);
  pinMode(sliderPromptPin, OUTPUT);
  pinMode(photoPromptPin, OUTPUT);
  pinMode(yellowLedPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(voicePlayPin, OUTPUT);
  pinMode(voicePausePin, OUTPUT);
  pinMode(voiceNextPin, OUTPUT);
  
  //set pins to input mode
  pinMode(sliderPin, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(photoPin, INPUT);
 
  randomSeed(analogRead(0));
  
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
      // photoSequence();
        break;
  }
  delay(3);//slow program down
  if(!win){
    //play lose 
    //blink score
    //reset game
  }else{
    score ++;
    //play win
    //add to score
    //--interval
  }
  delay(3);//slow program down
  if(score == 99){
    //end game sequence
  }
  
}


void buttonSequence(){
  while(!flag){
    currentTime = millis();
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;
      flag = true;
    }else if(buttonState == HIGH){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
    }else{
      buttonState = digitalRead(buttonPin);
    }  
  }
}

void sliderSequence(){
  previousSliderState = analogRead(sliderPin);
  while(!flag){
    currentTime = millis();
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;
      flag = true;
    }else if(previousSliderState != sliderPin){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
    }else{
      sliderState = analogRead(sliderPin);
    }  
  }
}

void photoSequence(){
  previousPhotoState = analogRead(photoPin);
  while(!flag){
    currentTime = millis();
    if(currentTime - previousTime >= waitTime){// check time for operation
      win = false;
      flag = true;
    }else if(previousPhotoState != photoState){//check if button was press
      win = true;//exits with right option
      flag = true;//true ends this loop and assigns new number for sequence
    }else{
      photoState = analogRead(photoPin);
    }  
  }
}
