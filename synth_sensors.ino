/*Gets sensor inputs from flex sensors and mpu-6050 accel/gyro. 
 * Prints data to bluetooth module to be sent to Rpi. 
 * 
 * Written by Nathan Jenson
 * 6/20/2019
 */
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <MPU6050.h>
//#include <I2Cdev.h>

#define dt 0.0065
#define ADC 72
#define MPU 68
#define pinky_pin A3

// Declare variables to use
int16_t ax, ay, az;
int16_t gx, gy, gz;

int16_t acc_x = 0;
int16_t acc_y = 0;
int32_t acc_z = 0;

int32_t ax_sum;
int32_t ay_sum;
int32_t az_sum;

int16_t ang_x = 0;
int16_t ang_y = 0;
int16_t ang_z = 0;

int16_t x_angle;
int16_t y_angle;
int16_t z_angle;


int16_t thumb_flex, index_flex, middle_flex, ring_flex, pinky_flex;


Adafruit_ADS1015 ads;     // Instantiate 12-bit version of ACD - ADS1015
MPU6050 mpu;              // Instantiate the MPU-6050

void setup(void) 
{
  Serial.begin(2000000);
  ads.setGain(GAIN_ONE);
  mpu.initialize();
}

void loop(void) 
{
  get_flex_data();                                    // Get flex sensor data
  get_mpu_data();                                     // Get accel and gyroscope data
  send_data();                                        // Concatenate and send the data to the pi
}



/*Get the flex sensor data from the ADS1015 and from the Analog input pin
 */
void get_flex_data(){
  Wire.begin(ADC);                                    // Begin communication with ADS1015
  thumb_flex = ads.readADC_SingleEnded(0);            // Get flex sensor data for 4 fingers
  index_flex = ads.readADC_SingleEnded(1);
  middle_flex = ads.readADC_SingleEnded(2);
  ring_flex = ads.readADC_SingleEnded(3);
  Wire.end();                                         // End communication with ADS1015
  pinky_flex = analogRead(pinky_pin);                       // Get the reading of the last flex sensor
  }

/* Get data from the MPU-6050
 * Start by getting acceleration data, filtered using an average of 4 readings
 * Then get gyro data and use complementary filter with map function to clean up data
 */
void get_mpu_data(){
  
  Wire.begin(MPU);                                      // Begin communication with MPU-6050

  ax_sum = 0;                                           // Get the Acceleration data by averaging. Set Acc sums equal to zero before starting
  ay_sum = 0;
  az_sum = 0;
                                                      
  for (int i=0; i<4; i++){                               // Filter data by taking average of multiple readings
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);        // Get accelerations
    ax_sum += ax;                                        // Sum 4 acceleration readings
    ay_sum += ay;
    az_sum += az;
    }
  
  acc_x = ax_sum / 4;                                    // Take the average of the 4 data readings
  acc_y = ay_sum / 4;
  acc_z = az_sum / 4;


  ang_x = 0.97*(ang_x + gx*dt)+(0.03*ax);               // Now process the gyro data with complementry filter
  x_angle = map(ang_x,-15600,17200,-90,90);             // Map to -90 through 90 degrees
  
  ang_y = 0.97*(ang_y + gy*dt) + (0.03*ay);             // Same as above but for Y data
  y_angle = map(ang_y,-16600,16100,-90,90);

  ang_z = 0.97*(ang_z + gz*dt) + (0.03*az);             // Same as above but for z data
  z_angle = map(ang_z,-16600,16100,-90,90);


  Wire.end();                                           // End communication with the MPU
  }

  
/* Send data in easy to read format.
 *  Use this function instead of the send_data() function for debugging purposes
 */
  
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
 }


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
  Serial.println("$ " + String(thumb_flex) + " " + String(index_flex)+ " " + String(middle_flex) + " " + String(ring_flex)+ " " + String(pinky_flex) + " " + String(x_angle)+ " " + String(y_angle) + " " + String(z_angle)+ String(micros()) + " &");
 }
