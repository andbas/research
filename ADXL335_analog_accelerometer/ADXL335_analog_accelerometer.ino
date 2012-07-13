#define ADC_ref 5.0
#define analog_resolution 1024.0

#define zero_x 1.60156
#define zero_y 1.60156
#define zero_z 1.64551

#define sensitivity_x 0.33
#define sensitivity_y 0.33
#define sensitivity_z 0.31
 
unsigned int value_x;
unsigned int value_y;
unsigned int value_z;
 
float xv;
float yv;
float zv;
 
float angle_x;
float angle_y;
float angle_z;
 
void setup()   {
  Serial.begin(9600);
}
 
void loop() {
  value_x = analogRead(0);
  value_y = analogRead(1);
  value_z = analogRead(2);
  
  xv = (value_x/analog_resolution*ADC_ref-zero_x)/sensitivity_x;
  yv = (value_y/analog_resolution*ADC_ref-zero_y)/sensitivity_y;
  zv = (value_z/analog_resolution*ADC_ref-zero_z)/sensitivity_z;
  
  Serial.print("x = ");
  Serial.print(xv);
  Serial.print("g   y = ");
  Serial.print(yv);
  Serial.print("g   z = ");
  Serial.print(zv);
  Serial.println("g");

  angle_x =atan2(-yv,-zv)*RAD_TO_DEG;
  angle_y =atan2(-xv,-zv)*RAD_TO_DEG;
  angle_z =atan2(-yv,-xv)*RAD_TO_DEG;
  
  Serial.print(angle_x);
  Serial.print(" deg ");
  Serial.print(angle_y);
  Serial.print(" deg ");
  Serial.print(angle_z);
  Serial.println(" deg");

  delay(1500);
}
