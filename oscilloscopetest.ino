int buf[7] = {255,238,191,127,64,17,0}; //This is for sine wave duty cycle values for the demo
int del = 100; //just a variable for delay arg in loop 

void setup() {
  // put your setup code here, to run once:
  
  //configure buttons with GPIO 
  //set direction registers for pin 13 where LED is

 //Turn LED ON pin 13
  GPIOC_PDDR |= (1<<5);//pin 13 is on port c pin 5 on port data direction register
  PORTC_PCR5 |= (1<<8);//enable pin as GPIO on pin control register
  PORTC_PCR5 |= (1<<1); //enable pull-bit 0 as 0 set to pull down
  GPIOC_PDOR |= (1<<5);// set port data output register bit 5 to high

  //pin 6
  //page 209 PTD4-> FTM0_CH4 is ALT 4
  PORTD_PCR4 |= (1 << 10);
  PORTD_PCR4 &= ~(0 << 9);
  PORTD_PCR4 &= ~(0 << 8);

  //timer status control-use system clock
  FTM0_SC |= (1 << 3);
  FTM0_SC &= ~(0 << 4);

  //disable write protection
  FTM0_MODE |= (1 << 2);
  
  FTM0_MODE |= _BV(1); // Enables FTM, this must come after the line above since this bit is write protected.

  //set a pre-scalar of 8 (8bit resolution)
  FTM0_SC &= ~(0 << 2);
  FTM0_SC |= (1 << 1);
  FTM0_SC |= (1 << 0);

  // This sets edge aligned PWM mode
  FTM0_C4SC |= (1 << 5);//MSB
  FTM0_C4SC &= ~(0 << 2);//ELSA
  FTM0_C4SC |= (1 << 3);//ELSB

  //Requirements for edge aligned up counter pwm is done, MSnB 1 (Channel mode select B) ,QUADEN 0 (Quadrature Decoder), DECAPEN 0 (Dual edge capture) , COMBINE 0 (Pair dual channel)
//CPWMS 0 (center aligned disabled and set as upcounting mode)

  FTM0_CNTIN = 0; //Initial value is 0 for PWM counter, also edge align mode MUST use CNTIN by design
  FTM0_C4V = 128; // count up to C4V and clear output, C4V/MOD duty cycle %
  FTM0_MOD = 255;//counts up to MOD then counts back up from 0, this is the period of cycle
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //This is for making a sine wave, hook up to oscilloscope to see it or just delete this part of the code to test what you want. 
for(int i = 0; i <= 6; i++ ){
  FTM0_C4V = buf[i];
  delay(del);
  }

for(int j = 5; j >= 0; j-- ){
  FTM0_C4V = buf[j];
  delay(del);
  }
}
