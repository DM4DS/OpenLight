// OpenLight (GPL v3) + no commercial use without permission! Free to modify but you have to name me in your project.
// share alike / this is also for the 3D Printed parts, not only the arduino code. Thanks and enjoy it!
//
// I am sure this will be updated from time to time, so come back for the updates.

// The/a free programmable UniLight (Copyright by https://www.unilight.at/) and modifyable for your needs! Open Source. 
// to realise Light schemes to your vehicle - plane - truck - crawler - boot - etc.
// it is based on Arduino (https://www.arduino.cc/) - in my case I use a Arduino Micro 5V
// to power it straight from the 5V Servo port of my Receiver. Just plug it in and the arduino
// is doing its job.
//
//
// How does it work:
// On the "PWMInput1" Pin (in my case D9) the PWM from the receiver is read
// with a following IF the position of your source / switch is detected and translated in
// a specific blink scheme / perma light if you want (but look for the heat if you are using high power LED).
//
// In the example:
// full low < 1200 uS = no light at all
// mid range >1200 <1600 = slow blinking
// high range >1600 = fast blinking
// /feel free to express yourself in building your own blink schemes by adjusting the timings.
//
// while the LED´s generating a lot of heat if the are turned on for long time, I only switch them on
// for 10 mS! That is enough to get the needed flash and stay cool, but feel free to modify it for your needs!
// In the example only LED1 Pin 3 is connected as output to a MosFET Board, but I already defined 4 / 5 also if you need them
// copy & paste the code and change the LED1 to LED2 / LED3.
// 
// As I said, I use a 5V Arduino Micro, so I can connect it straight to a free RX channel for the PWM Signal + 5V to power
// the Arduino. Win win :)
// no special lybraries are needed, so it should be fine to use "almost" any Arduino you have laying around. Try it.
// 
// watch in the serial monitor/plotter your RX input. If there is nothing detected, it can´t work.
// I had the case that with a cheap SERVO TESTER it was not working, but with a actuall RX it is always 100% working!
// So I looked with the oscilloscope on the PWM of the Servo tester and omg, that was distorted and no wonder it was not working.
// Keep that in mind, if you maybe test on the bench.
//
// now - let´s blink :)
// DM4DS - Sandor
//

//WS2812 Part:
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 6 // which PIN the DIN from the WS2812 is connected
#define NUMPIXELS 40 // attached numbers of WS2812 LEDs (max you wanna use)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int ws2812time=100; // pause between each WS2812 LED

//Parts for all applications
int LED1 = 3;       			// that´s the one output I´m using and is configured to blink as above described
// int LED2 = 4;				// alternative outputs if you wanna usw it for more unique lighting / uncomment - 
// int LED3 = 5;				// copy & paste the IF /digitalwrite line + insert LED2/3 instead of LED1
int PWMInput1 = 9;				// PWM Input from the Receiver


void setup() {
  pinMode(LED1, OUTPUT);		// define LED1 Pin as output
//  pinMode(LED2, OUTPUT);		// uncomment if needed
//  pinMode(LED3, OUTPUT);		//        "
  pinMode(PWMInput1, INPUT);	// PWMINput1 defined as input from the RX - if you need more inputs, feel free to define more
  Serial.begin(115200);			// Serial Monitor / Plotter setting
 
// WS2812 initialize  
  pixels.begin(); // Initialise WS2812
}

void loop() {							// here the magic happens
 
int pwm1 = pulseIn(PWMInput1, HIGH);
  Serial.println(pwm1);					// Serial Monitor / Plotter Output
  if(pwm1 < 1199)						// If the stick / switch is under 1200 (low) do "no blinking"
  {
    Serial.print(PWMInput1);

  digitalWrite(LED1, LOW);   
  delay(250);             

  digitalWrite(LED1, LOW);   
  delay(500);             

  }
  else
  {
    Serial.print(PWMInput1);
  }

  if(pwm1 > 1801)						// if the stick / switch is over 1800 (full up/on) fast blinking on PIN LED1
  {
    Serial.print(PWMInput1);

  digitalWrite(LED1, HIGH);       // PIN1/LED1 on for 15ms
  delay(15);              
  digitalWrite(LED1, LOW);   			// PIN1/LED1 low means Output off / no lights for 250ms
  delay(250);             
  
  digitalWrite(LED1, HIGH);       // PIN1/LED1 on again for 15ms
  delay(15);              
  digitalWrite(LED1, LOW);   			// PIN1/LED1 off again, this time for 750ms
  delay(750);             

 digitalWrite(LED1, HIGH);        // PIN1/LED1 on again for 25ms
  delay(25);              
  digitalWrite(LED1, LOW);         // PIN1/LED1 off again for 1250ms
  delay(1250);             

  }
  else
  {
    Serial.print(PWMInput1);
  }
  if((pwm1 < 1800)&&(pwm1 > 1200))		// if the stick / switch is in the middle (>1200<1800) blink slower
  {
    Serial.print(PWMInput1);
// this time we are "running" 10 WS2812 LEDs in green color full brightness one after another
    
pixels.setPixelColor(1, pixels.Color(0,255,0)); // WS2812 LED 1 green full power 255
pixels.show(); // send the "command" to the WS2812 LEDs
delay (ws2812time); // Pause we defind earlier between each LED to light up
pixels.setPixelColor(2, pixels.Color(0,250,0)); // WS2812 LED 2 green full power 255
pixels.show();
delay (ws2812time);
pixels.setPixelColor(3, pixels.Color(0,255,0)); // WS2812 LED 3 green full power 255
pixels.show(); 
delay (ws2812time); 
pixels.setPixelColor(4, pixels.Color(0,255,0)); 
pixels.show();
delay (ws2812time);
pixels.setPixelColor(5, pixels.Color(0,255,0));
pixels.show();
delay (ws2812time);
pixels.setPixelColor(6, pixels.Color(0,255,0));
pixels.show();
delay (ws2812time);
pixels.setPixelColor(7, pixels.Color(0,255,0));
pixels.show();
delay (ws2812time);
pixels.setPixelColor(8, pixels.Color(0,255,0));
pixels.show();
delay (ws2812time);
pixels.setPixelColor(9, pixels.Color(0,255,0));
pixels.show();
delay (ws2812time);
pixels.setPixelColor(10, pixels.Color(0,255,0));
pixels.show();
delay (ws2812time);

// reset all WS2812 LEDs to "0" / OFF
pixels.setPixelColor(1, pixels.Color(0,0,0)); 
pixels.setPixelColor(2, pixels.Color(0,0,0)); 
pixels.setPixelColor(3, pixels.Color(0,0,0)); 
pixels.setPixelColor(4, pixels.Color(0,0,0)); 
pixels.setPixelColor(5, pixels.Color(0,0,0)); 
pixels.setPixelColor(6, pixels.Color(0,0,0)); 
pixels.setPixelColor(7, pixels.Color(0,0,0)); 
pixels.setPixelColor(8, pixels.Color(0,0,0)); 
pixels.setPixelColor(9, pixels.Color(0,0,0)); 
pixels.setPixelColor(10, pixels.Color(0,0,0)); 

pixels.show(); // send the "0" "command" to the WS2812 LEDs
delay (ws2812time);
  }
  else
  {
    Serial.print(PWMInput1);
  }

}

// Feel free to modify it and share it with us.
// There will be over time different hardware stuff and
// 3D printed case linked / uploaded while I building several OpenLight for my Clubmates.
// Thanks for sharing and commenting if you need somehting and not able to do it on your own.
// List how you can support me:

// Patreon: https://www.patreon.com/dm4ds
// Paypal donation: https://www.paypal.com/paypalme/dm4ds
// BMAcoffee: https://buymeacoff.ee/dm4ds
// Bitcoin: bc1qf426e46h6kdtmws4cjnu6wa3wtzy8qvctq9j9u
// Etherium: 0x3447f956194706eCDab747314CFB92Bf55428F28

// List how / where you find me:

// Youtube: https://www.youtube.com/c/DM4DS
// Printables: https://www.printables.com/de/social/461183-dm4ds/about
// Twitter: https://twitter.com/HAM_DM4DS
// Instagram: https://www.instagram.com/dm4ds/
// Thingiverse: https://www.thingiverse.com/dm4ds/
// Thangs: https://thangs.com/DM4DS
// QRZ.com: https://www.qrz.com/lookup/DM4DS
// Twitch: https://www.twitch.tv/dm4ds
// Discord Server: https://discord.gg/xSzfBCyXCZ

// List of affiliate Shops / companies:

// Amazon Affiliate Link: https://amzn.to/31TI1FC
// CopterUni: https://kurs.copteruni.de/?ref=3a0ca5

// E-post adress:
// Email: info@dm4ds.de / dm4ds@gmx.de
