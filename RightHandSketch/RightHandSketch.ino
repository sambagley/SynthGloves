/*Gets sensor inputs from flex sensors and mpu-6050 accel/gyro.
 * Prints data to bluetooth module to be sent to Rpi.
 *
 * Written by Nathan Jenson
 * 6/20/2019
 */

#include <Adafruit_ADS1015.h>
//#include <MPU6050.h>
#include <I2Cdev.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#define dt 0.008764
#define ADC 72
#define MPU 68
#define pinky_pin A0

// Declare variables to use
int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t acc_x = 0;
int16_t acc_y = 0;
int16_t acc_z = 0;




int16_t ang_x = 0;
int16_t ang_y = 0;
int16_t ang_z = 0;

int16_t x_angle;
int16_t y_angle;
int16_t z_angle;

int16_t temp;


int16_t thumb_flex, index_flex, middle_flex, ring_flex, pinky_flex;

uint16_t index = 0;
Adafruit_ADS1015 ads;     // Instantiate 12-bit version of ACD - ADS1015
//MPU6050 mpu;              // Instantiate the MPU-6050
MPU6050 mpu6050(Wire);
unsigned long el;

int buttonState1;
int buttonState2;
int buttonState3;
int lastButtonState1 = HIGH;
int lastButtonState2 = HIGH;
int lastButtonState3 = HIGH;

unsigned long lastDebounceTime1 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime2 = 0;  // the last time the output pin was toggled
unsigned long lastDebounceTime3 = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 10;    // the debounce time; increase if the output flickers


const int buttonPin1 = 6;    // the number of the pushbutton pin
const int buttonPin2 = 5;    // the number of the pushbutton pin
const int buttonPin3 = 4;    // the number of the pushbutton pin

float aX, aY, aZ;
float accX, accY, accZ;
void setup(void)
{
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
      // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif



  Serial.begin(57600);
  ads.setGain(GAIN_ONE);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  //mpu6050.end();
  //mpu.initialize();

}

void loop(void)
{

  get_flex_data();

  get_mpu_data();

  getButtons();
  
  send_data();

  Serial.println(micros());

}



/*Get the flex sensor data from the ADS1015 and from the Analog input pin
 */
void get_flex_data(){

  Wire.begin(ADC);
  pinky_flex = ads.readADC_SingleEnded(3);
  index_flex = ads.readADC_SingleEnded(0);
  middle_flex = ads.readADC_SingleEnded(1);
  ring_flex = ads.readADC_SingleEnded(2);
  Wire.end();
  thumb_flex = analogRead(pinky_pin);
  }

void getButtons(){
   int reading1 = digitalRead(buttonPin1);
   int reading2 = digitalRead(buttonPin2);
   int reading3 = digitalRead(buttonPin3);
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading1 != lastButtonState1) {
    // reset the debouncing timer
    lastDebounceTime1 = millis();
  }
  if (reading2 != lastButtonState2) {
    // reset the debouncing timer
    lastDebounceTime2 = millis();
  }
  if (reading3 != lastButtonState3) {
    // reset the debouncing timer
    lastDebounceTime3 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading1 != buttonState1) {
      buttonState1 = reading1;

    
    }
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading2 != buttonState2) {
      buttonState2 = reading2;

    
    }
  }if ((millis() - lastDebounceTime3) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading3 != buttonState3) {
      buttonState3 = reading3;

    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState1 = reading1;
  lastButtonState2 = reading2;
  lastButtonState3 = reading3;
}




/* Get data from the MPU-6050
 * Start by getting acceleration data, filtered using an average of 4 readings
 * Then get gyro data and use complementary filter with map function to clean up data
 */
void get_mpu_data(){
  //mpu6050.begin();
  mpu6050.update();
  aX = mpu6050.getAngleX();
  aY = mpu6050.getAngleY();
  aZ = mpu6050.getAngleZ();
  accX = mpu6050.getAccX();
  accY = mpu6050.getAccY();
  accZ = mpu6050.getAccZ();
  //mpu6050.end();

/*
acc_x = mpu6050.getRawAccX();
acc_y = mpu6050.getRawAccY();
acc_z = mpu6050.getRawAccZ();
temp = mpu6050.getRawTemp();
ang_x = mpu6050.getRawGyroX();
ang_y = mpu6050.getRawGyroY();
ang_z = mpu6050.getRawGyroZ();
*/
  }


/* Send data in easy to read format.
 *  Use this function instead of the send_data() function for debugging purposes
 */
/*
void print_readable_data(){
  Serial.print("Thumb: "); Serial.println(thumb_flex);
  Serial.print("Index: "); Serial.println(index_flex);
  Serial.print("Middle: "); Serial.println(middle_flex);
  Serial.print("Ring: "); Serial.println(ring_flex);
  Serial.print("Pinky: "); Serial.println(pinky_flex);
  Serial.println(" ");

  Serial.print("X Accel: "); Serial.println(acc_x);
  Serial.print("Y Accel: "); Serial.println(acc_y);
  Serial.print("Z Accel: "); Serial.println(acc_z);
  Serial.println(" ");

  Serial.print("X Angle: "); Serial.println(x_angle);
  Serial.print("Y Angle: "); Serial.println(y_angle);
  Serial.print("Z Angle: "); Serial.println(z_angle);
  Serial.print("Time: "); Serial.println(micros());
  Serial.println(" ");
  Serial.println(" ");
  Serial.println(" ");
 }*/


/*Sends data ready to be parsed by Pi.
 * New data set begins with "$" and ends with "&"
 * Data is sent as follows:
 * -----------------------
 * Thumb Flex
 * Index Flex
 * Middle Flex
 * Ring Flex
 * Pinky Flex
 * X gyro angle
 * Y gyro angle
 * Z gyro angle
 *
 * Velocity data will be added soon...
 */
 void send_data(){
   Serial.print("$" + String(thumb_flex) + " " + String(index_flex)+ " " + String(middle_flex) + " " + String(ring_flex)+ " " + String(pinky_flex) + " " );
   Serial.print(String(aX)+ " " + String(aY) + " " + String(aZ) + " ");
   Serial.print(String(aX)+ " " + String(aY) + " " + String(aZ) + " ");
   //Serial.print(String(ang_x)+ " " + String(ang_y) + " " + String(ang_z) + " ");
   //Serial.print(String(acc_x)+ " " + String(acc_y) + " " + String(acc_z) + " " + String(temp) + " ");
   Serial.println(String(buttonState1)+ " " + String(buttonState2) + " " + String(buttonState3) + " ");
 // Serial.println("$" + String(thumb_flex) + " " + String(index_flex)+ " " + String(middle_flex) + " " + String(ring_flex)+ " " + String(pinky_flex) + " " + String(x_angle)+ " " + String(y_angle) + " " + String(z_angle) + " "+ String(acc_x)+ " " + String(acc_y) + " " + String(acc_z) + " ");
 }





 /*void send_data_bytes(){
  Serial.write(
    );
 }*/
