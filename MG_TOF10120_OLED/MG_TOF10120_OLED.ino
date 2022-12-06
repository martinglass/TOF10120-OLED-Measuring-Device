/* This code is to use with ToF10120 Laser Range Sensor to measure distance in (mm) and 
 * shows it on on an OLED screen using I²c inteface and in the Serial monitor of the Arduino app 
 * Modified and adapted from https://www.electroniclinic.com/ 
 * by Martin Glass December 2022 (c)
 * https://github.com/martinglass/TOF10120-OLED-Measuring-Device
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

unsigned short length_val = 0;
unsigned char i2c_rx_buf[16];
unsigned char dirsend_flag=0;

int x_mm; // distance in millimeters

// for the OLED display

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
 
// Declaration for an SSD1306 display connected to I2C using Wire library
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int row = 0, col = 0;
int char_height = 8; // pixels, 8px is textSize 1

void setup() {
  Wire.begin(); 
  Serial.begin(9600,SERIAL_8N1); 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, 1);
  display.clearDisplay();
  display.setTextColor(WHITE);

  // startup screen
  row=0; col=0;
  display.setCursor(col,row); // column row
  display.setTextSize(char_height/8);
  display.print("Start distance");
  row += char_height;
  display.setCursor(col,row); // column row
  display.setTextSize(char_height/8);
  display.print("readings by Martin G");
  display.display(); 
  delay(1000);

  row=0; col=0;
  display.clearDisplay();
  display.setCursor(col,row); // column row
  display.setTextSize(char_height/8);
  display.print("Readings mm");
  display.display();            
} // setup()


void loop() {
  delay(250);
  // place text on OLED screen
  row += char_height;
  if (row > (SCREEN_HEIGHT-1)) // show readings until end of screen
  {
    col += SCREEN_WIDTH / 2; // two columns of readings
    if (col > (SCREEN_WIDTH-1)) 
    {
      col = 0; 
      display.clearDisplay(); // clear screen after screen is full
      display.display();
    }

  row=0;
  }
   x_mm = ReadDistance();
// show measurement on OLED   
   display_measurement();

// show measurement on Serial Monitor
   Serial.print(x_mm);
   Serial.println(" mm");
   
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
  }
}

int ReadDistance(){
    SensorRead(0x00,i2c_rx_buf,2);
    length_val=i2c_rx_buf[0];
    length_val=length_val<<8;
    length_val|=i2c_rx_buf[1];
    delay(300); 
    return length_val;
}

void display_measurement()
{
// display on OLED display
  display.setCursor(col+8,row); // column row
  display.setTextSize(char_height/8);
  display.print(x_mm);
  display.setCursor(col+32,row);
  display.setTextSize(char_height/8);
  display.print("mm "); 
  display.display();
}
