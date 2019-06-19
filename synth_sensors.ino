#include <Wire.h>
#include <I2Cdev.h>
#include <MPU6050.h>

#define dt 0.005
#define thumb A0
#define index A1
#define middle A2
#define ring A3
//#define pinky A2                                                TODO: implement analog mux into arduino sketch.


// Declare variables to use
int16_t ax, ay, az;
int16_t gx, gy, gz;
//float x_acc, gyro;

int16_t ang_x = 0;
int16_t ang_y = 0;

int16_t x_angle;
int16_t y_angle;

uint16_t thumb_flex;
uint16_t index_flex;
uint16_t middle_flex;
uint16_t ring_flex;
uint16_t pinky_flex;

uint16_t finger_avg;

MPU6050 mpu;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  mpu.initialize();
}

void loop() {
  // put your main code here, to run repeatedly:

  get_gyro();                                         // Main section. Get values from each section
  index_flex = get_finger_flex(index);                // TODO: add accel data and additional flex sensors
  middle_flex = get_finger_flex(middle);              
  
  Serial.print(" st");                                // Print sensor data to serial port
  Serial.print(" ");                                  // begin by sending start bit ("st" can be changed to something else)
  Serial.print(x_angle);                              // Send to serial port
  Serial.print(" ");
  Serial.print(y_angle);
  Serial.print(" ");
  Serial.print(index_flex);
  Serial.print(" ");
  Serial.print(middle_flex);
  Serial.print(" ");
  Serial.println("sp");                               // Print stop bit

}


uint16_t get_finger_flex(int finger) {
  // Get flex data from fingers
  int sum = 0;
  for (int i=0; i<5; i++){
    sum += analogRead(finger);
    }
  finger_avg = sum / 5;
  
  return finger_avg;
}

void get_gyro() {
  // Get Gyro and accelerometer data
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);         // Get data from sensor

  ang_x = 0.97*(ang_x + gx*dt)+(0.03*ax);               // Filter data
  x_angle = map(ang_x,-15600,17200,-90,90);             // Map to -90 through 90 degrees
                                                        // The values -15600 and 17200 may need to be changed
                                                        // for variations in the gyro hardware. See comment below. 
 
  ang_y = 0.97*(ang_y + gy*dt) + (0.03*ay);             // Same as above but for Y data
  y_angle = map(ang_y,-16600,16100,-90,90);
  
  /*Serial.print("y-angle:");                             // If output angles are not calibrated from -90 to 90 degrees, 
  Serial.print("\t");                                   // comment out the serial.print lines in the section above and
  Serial.print(ang_y);                                  // uncomment the block of lines to the left. These will display
  Serial.print("x-gyro data:");                         // the range of values that need to be mapped to -90 to 90 degrees.
  Serial.print("\t");  
  Serial.println(ang_x);
  */
  return;
  
  }
