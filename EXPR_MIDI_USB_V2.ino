
// this constant won't change:
const int  buttonPin1 = 2;    // the pin that the pushbutton is attached to
const int  buttonPin2 = 3;

// Variables will change:
int buttonPushCounter = 1;   // counter for the number of button presses

int buttonState1 = 0;         // current state of the button
int buttonState2 = 0;

int lastButtonState1 = 0;     // previous state of the button
int lastButtonState2 = 0;     // previous state of the button

int CCnumber = 1;

/////**********////////// importo info 
#include <MIDI.h> //importo la libreria MIDI

//Variables

int analogValue=0;
int lastAnalogValue=128; //Valor de inicio, se usa para comparar con el valor anterior

MIDI_CREATE_DEFAULT_INSTANCE ();  //creo la instancia 
//////////////////////////////////////////////////////////

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin1, INPUT);
  // initialize the LED as an output:
  pinMode(buttonPin2, INPUT);
  // initialize serial communication:
  ///Serial.begin(9600);
  MIDI.begin(1);  //comienza MIDI por el canal 1 en este caso
  Serial.begin (31250); //puerto serial a 31250 baudios
}


void loop() {
  // read the pushbutton input pin:
  buttonState1 = digitalRead(buttonPin1);

  // compare the buttonState to its previous state
  if (buttonState1 != lastButtonState1) {
    // if the state has changed, increment the counter
    if (buttonState1 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      
          } 
          else {
      
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState1 = buttonState1;

//////////////////////////////////////////////////////////
 // read the pushbutton input pin:
  buttonState2 = digitalRead(buttonPin2);

  // compare the buttonState to its previous state
  if (buttonState2 != lastButtonState2) {
    // if the state has changed, increment the counter
    if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter--;

    } 
    else {
    
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState2 = buttonState2;
  
  //////////////LIMITO EL CCnro = 0
  
  if (buttonPushCounter < 0) { 
      buttonPushCounter = 0; 
      }
  
  /////////MIDI POTENTIOMETER/////////////////////////////////////////////////////////////
int CCnumber= buttonPushCounter;
  
int analogValue= (abs(analogRead (0)/8)); //escaleo el rango 0-1023
 
 //si la diferencia entre lastAnalogValue y el Valor entrante (analogValue) es  > 1 o < -1
 //entonces mando valor. Si no hay cambio, no mando nada.
 if ((analogValue - lastAnalogValue) > 1 || (analogValue-lastAnalogValue) < -1) {
  
  MIDI.sendControlChange( CCnumber, analogValue, 1);
  
  lastAnalogValue = analogValue; // queda el ultimo valor del pote.
  
   }
}

