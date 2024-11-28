/* This code is to use with ToF10120 Laser Range Sensor to measure distance in (mm) and 
 * shows it on on an OLED screen using I²c inteface and in the Serial monitor of the Arduino app 
 * Modified and adapted from https://www.electroniclinic.com/ 
 * by Martin Glass December 2024 (c)
 * https://github.com/martinglass/TOF10120-OLED-Measuring-Device
 */

#define DEBUG 0 // additional output for DEBUG != 0

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


unsigned char i2c_rx_buf[16];
unsigned char dirsend_flag=0;

unsigned short x_mm; // distance in millimeters

unsigned short mma = 0; // Moving average cumulative
unsigned short j=0; // Moving average count

// Moving Average (mma) Parameters
#define MMA_LIMIT 20 // mma size
unsigned short x_mma[MMA_LIMIT]; // array of x values within the mma

int i = 0; // loop counter
int mma_i = 0; // ongoing count pointer


// for the OLED display

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

 
int row = 0, col = 0;
int char_height = 8; // pixels, 8px is textSize 1

// Declaration for an SSD1306 display connected to I2C using Wire library
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Wire.begin(); 
  Serial.begin(115200); 
//  Serial.begin(115200,SERIAL_8N1); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, 1);
  display.clearDisplay();
  display.setTextColor(WHITE);
  
  // Initialise values to 0 in the moving average array
  for (i = 0; i < MMA_LIMIT; i++) {
    x_mma[i] = 0;
  }

  // startup screen
  row=0; col=0;
  display.setCursor(col,row); // column row
  display.setTextSize(char_height/8);
  display.print("Start distance");
  Serial.print("Start distance ");
  row += char_height;
  display.setCursor(col,row); // column row
  display.setTextSize(char_height/8);
  display.print("readings by Martin G");
  Serial.println("readings by Martin G");
  display.display(); 
  delay(1000);

  row=0; col=0;
  display.clearDisplay();
  display.setCursor(col,row); // column row
  display.setTextSize(char_height/8);
  display.print("Readings mm");
  display.display();            
  Serial.println("Readings mm");
} // setup()


void loop() {
  delay(250);
  // place text on OLED screen
  row += char_height;
  


if (row > (SCREEN_HEIGHT - 1)) // Show readings until the end of the screen
  {
    col += SCREEN_WIDTH / 2; // Two columns of readings
    if (col > (SCREEN_WIDTH - 1)) 
    {
      col = 0; 
      display.clearDisplay(); // Clear screen after it is full
      display.display(); // Update display screen (to clear)
    }

    row = 0; // Reset to the top row for new readings
  } // End of `if (row > (SCREEN_HEIGHT - 1))

  x_mm = ReadDistance();
  if (DEBUG) x_mm = 10 + ( rand() % 1991 ); // Debug (generate random data) 

  // update the Moving Average data
  if ( x_mm > 0 ) {
    x_mma[mma_i] = x_mm;

    if (DEBUG) Serial.print("(mma_i "); // Debug
    if (DEBUG) Serial.print(mma_i); // Debug
    if (DEBUG) Serial.print(" "); // Debug
    if (DEBUG) Serial.print( x_mma[mma_i] ); // Debug
    if (DEBUG) Serial.print( ") " ); // Debug

    if ( row == 0 ) {
      // calculate and display Moving Average at top of screen

       moving_average();
       display_measurement( mma );
       print_measurement( mma );

       row += char_height; // skip a row, to provide an onscreen blank line gap
       Serial.println("^^^^^^ (MMA)\n");

      }
    // show measurement on OLED & Serial Output
    display_measurement( x_mm );
    print_measurement( x_mm );
    mma_i +=  1 ; // increment ongoing count pointer
    if ( mma_i >= MMA_LIMIT ) mma_i = 0; // until end of array
  }  // end of if x_mm > 0 
} // loop()


void SensorRead(int addr,unsigned char* datbuf,int cnt) 
{
  unsigned short result=0;
  // Instruct sensor to read echoes and wait for readings
  Wire.beginTransmission(82); // transmit to device #82 (0x52)
  Wire.write(byte(addr));      // sets distance data address (addr)
  Wire.endTransmission();      // stop transmitting
  delay(1);                   // datasheet suggests at least 30uS
  
  // Request and read reading from sensor
  Wire.requestFrom(82, cnt);    // request cnt bytes from slave device #82 (0x52)
  if (cnt <= Wire.available()) { // if two bytes were received
    *datbuf++ = Wire.read();  // receive high byte (overwrites previous reading)
    *datbuf++ = Wire.read(); // receive low byte as lower 8 bits
  } else {
if (DEBUG) Serial.println("Error: Insufficient data from sensor."); //Debug
  }
}

unsigned short ReadDistance(){
    SensorRead(0x00,i2c_rx_buf,2);
    unsigned short length_val=i2c_rx_buf[0];
    length_val=length_val<<8;
    length_val|=i2c_rx_buf[1];
    delay(300); 
    return length_val;
}

void display_measurement(unsigned short x)
{
// display on OLED display
  display.setCursor(col+8,row); // column row
  display.setTextSize(char_height/8);
  display.print(x);
  display.setCursor(col+32,row);
  display.setTextSize(char_height/8);
  display.print("mm "); 
  display.display();
}

void print_measurement(unsigned short x)
{
// show measurement on Serial Monitor
  Serial.print(x);
  Serial.println(" mm");
}

void moving_average() {
// Calculated Moving Average
  mma = 0;
  j = 0;
  for (i = 0; i < MMA_LIMIT; i++) {
    if (DEBUG) Serial.print( x_mma[i] ); //Debug
    if (DEBUG) Serial.print( " " ); //Debug
    if ( x_mma[i] != 0 ) {
      mma += x_mma[i];
      j += 1;
    }
  }

//  if (DEBUG) Serial.print( mma ); //Debug
//  if (DEBUG) Serial.print( " pre | " ); //Debug
  if ( j != 0) mma /= j ;
//  if (DEBUG) Serial.print( mma ); //Debug
//  if (DEBUG) Serial.print( "|" ); //Debug
//  if (DEBUG) Serial.print( j ); //Debug
}
