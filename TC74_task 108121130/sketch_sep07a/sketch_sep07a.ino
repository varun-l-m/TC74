#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#define SCL_CLOCK  100000 
int tempTC74;
char *alert = "FIRE";
int main(){
  DDRB=(1<<5);
  i2c_init();
  UART_init(103);
  //Serial.begin(9600);
  while(1){
    uint8_t data = 0;
    
  i2c_start(0x9A);
  i2c_write(0x00);
  i2c_start(0x9B);
 
  data = i2c_read();
  i2c_stop();
  tempTC74 = data;
  if(tempTC74 >=50){
    UART_puts(alert);
    //Serial.print("FIRE");
    PORTB= (1<<5);
    
    
    //break;
    }
    else{

      PORTB=0;
      _delay_ms(10);
      //Serial.print("P");
      
      
      }


    

    
    
    
    }
  
  
  }
  void i2c_init(void)
{
  
  TWSR = 0;                         
  TWBR = ((F_CPU/SCL_CLOCK)-16)/2; }



unsigned char i2c_start(unsigned char address)
{
    uint8_t   twst;

  
  TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);

 
  while(!(TWCR & (1<<TWINT)));

 
  

  
  TWDR = address;
  TWCR = (1<<TWINT) | (1<<TWEN);

 
  while(!(TWCR & (1<<TWINT)));

  
  

}
void i2c_stop(void)
{
   
  TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
  
  
  while(TWCR & (1<<TWSTO));

}
unsigned char i2c_write( unsigned char data )
{ 
    uint8_t   twst;
    
  
  TWDR = data;
  TWCR = (1<<TWINT) | (1<<TWEN);

  
  while(!(TWCR & (1<<TWINT)));

  
  
}
unsigned char i2c_read(void)
{
  TWCR = (1<<TWINT) | (1<<TWEN);
  while(!(TWCR & (1<<TWINT)));
  
    return TWDR;
}

void UART_init(uint16_t ubrr)
{
    // set baudrate in UBRR
    UBRR0L = (uint8_t)(ubrr & 0xFF);
    UBRR0H = (uint8_t)(ubrr >> 8);

    // enable the transmitter and receiver
    UCSR0C = 0x06;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}
void UART_putc(unsigned char data)
{
    // wait for transmit buffer to be empty
    while(!(UCSR0A & (1 << UDRE0)));

    // load data into transmit register
    UDR0 = data;
}
void UART_puts(char* s)
{
    // transmit character until NULL is reached
    while(*s > 0) UART_putc(*s++);
}
