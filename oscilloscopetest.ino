void setup() {
  // put your setup code here, to run once:
  
  //configure buttons with GPIO 
  //set direction registers for pin 13 where LED is

 //Turn LED ON pin 13
  GPIOC_PDDR |= (1<<5);//pin 13 is on port c pin 5 on port data direction register
  PORTC_PCR5 |= (1<<8);//enable pin as GPIO on pin control register
  PORTC_PCR5 |= (1<<1); //enable pull-bit 0 as 0 set to pull down
  GPIOC_PDOR |= (1<<5);// set port data output register bit 5 to high

  Serial.begin(9600);

//set up timer PWM 40% duty cycle pin 9
  FTM0_MOD = 61439;
//pin 9 on FTM0. FTM0_MOD is max value. FTM0_C2V is value to count upto for duty cycle.
  FTM0_C2V = 24575;//40 % duty cycle
//page 209 FTM0_CH2 is alt 4 for PCR3
  PORTC_PCR3 |= (1<<10);
  PORTC_PCR3 &= (0<<9);
  PORTC_PCR3 &= (0<<8);

  //DSE = High
  PORTC_PCR3 |= (1<<8);
  //SRE = Slow
  PORTC_PCR3 |= (1<<2);
 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(FTM0_C2V);
}
