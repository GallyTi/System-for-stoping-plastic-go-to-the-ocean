#include "HX711.h"

// ################################################################################
// ||                                                                            ||
// ||                            Hardware definition                             ||
// ||     (This may need to be adjusted after connecting the real hardware)      ||
// ||                                                                            ||
// ################################################################################

// Pressure sensor definition
HX711 pressure_sensor;
// Pressure sensor pins definition
#define pressure_dataPin 5
#define pressure_clockPin 4

// Actuator definition
enum class Actuator { ACTUATOR_1,
                      ACTUATOR_2 };
// Actuator pin definition (May need to be changed in the future)
#define actuator_1_up 6
#define actuator_1_down 7
#define actuator_2_up 8
#define actuator_2_down 9

// Motor pin definition (May need to be changed in the future)
#define motor_forward_led 3
#define motor_backward_led 2

// Water sensor pin definition
#define water_analog_pin A0
// Maximum and minimum possible voltage at water sensor (May need to be changed in the future)
const double water_height_max = 5;
const double water_height_min = 0;


// ################################################################################
// ||                                                                            ||
// ||                               Arduino setup                                ||
// ||                                                                            ||
// ################################################################################
void setup() {

  // START OF !DO NOT EDIT!
  Serial.begin(115200);
  setup_motor();
  setup_actuators();
  setup_pressure_sensor();
  // END OF !DO NOT EDIT!
  // put your setup code here, to run once:
}

// ################################################################################
// ||                                                                            ||
// ||                                Arduino loop                                ||
// ||                                                                            ||
// ################################################################################
void loop() {
  // put your main code here, to run repeatedly:

}

// ################################################################################
// ||                                                                            ||
// ||                         Pressure sensor functions                          ||
// ||      (This may need to be adjusted after connecting the real sensor)       ||
// ||                                                                            ||
// ################################################################################


// Initialize pressure sensor for sensing pressure onthe net
void setup_pressure_sensor() {
  pressure_sensor.begin(pressure_dataPin, pressure_clockPin);
  // Maybe do some scaling of the sensor
}

// Get a raw value from the pressure (+-10kg == -8388609~8388608)
double get_pressure_value() {
  pressure_sensor.wait_ready();
  return pressure_sensor.read();
}

// ################################################################################
// ||                                                                            ||
// ||                           Net actuator functions                           ||
// ||     (This may need to be adjusted after connecting the real actuator)      ||
// ||                                                                            ||
// ################################################################################

// Initialize actuators for moving the net
void setup_actuators() {
  pinMode(actuator_1_up, OUTPUT);
  pinMode(actuator_1_down, OUTPUT);
  pinMode(actuator_2_up, OUTPUT);
  pinMode(actuator_2_down, OUTPUT);
  digitalWrite(actuator_1_up, LOW);
  digitalWrite(actuator_1_down, LOW);
  digitalWrite(actuator_2_up, LOW);
  digitalWrite(actuator_2_down, LOW);
}

// Stop choosen actuator defined by actuator_num
void actuator_stop(Actuator actuator_num) {
  if (actuator_num == Actuator::ACTUATOR_1) {
    digitalWrite(actuator_1_up, LOW);
    digitalWrite(actuator_1_down, LOW);
  }
  if (actuator_num == Actuator::ACTUATOR_2) {
    digitalWrite(actuator_2_up, LOW);
    digitalWrite(actuator_2_down, LOW);
  }
}

// Move up choosen actuator defined by actuator_num
void actuator_up(Actuator actuator_num) {
  if (actuator_num == Actuator::ACTUATOR_1) {
    actuator_stop(Actuator::ACTUATOR_1);
    digitalWrite(actuator_1_up, HIGH);
    digitalWrite(actuator_1_down, LOW);
  }
  if (actuator_num == Actuator::ACTUATOR_2) {
    actuator_stop(Actuator::ACTUATOR_2);
    digitalWrite(actuator_2_up, HIGH);
    digitalWrite(actuator_2_down, LOW);
  }
}

// Move down choosen actuator defined by actuator_num
void actuator_down(Actuator actuator_num) {
  if (actuator_num == Actuator::ACTUATOR_1) {
    actuator_stop(Actuator::ACTUATOR_1);
    digitalWrite(actuator_1_up, LOW);
    digitalWrite(actuator_1_down, HIGH);
  }
  if (actuator_num == Actuator::ACTUATOR_2) {
    actuator_stop(Actuator::ACTUATOR_2);
    digitalWrite(actuator_2_up, LOW);
    digitalWrite(actuator_2_down, HIGH);
  }
}

// Stop both actuators
void actuators_stop() {
  actuator_stop(Actuator::ACTUATOR_1);
  actuator_stop(Actuator::ACTUATOR_2);
}

// Move up both actuators
void actuators_up() {
  actuator_up(Actuator::ACTUATOR_1);
  actuator_up(Actuator::ACTUATOR_2);
}

// Move down both actuators
void actuators_down() {
  actuator_down(Actuator::ACTUATOR_1);
  actuator_down(Actuator::ACTUATOR_2);
}

// ################################################################################
// ||                                                                            ||
// ||                           Water sensor functions                           ||
// ||      (This may need to be adjusted after connecting the real sensor)       ||
// ||                                                                            ||
// ################################################################################

// Get a water heigh in percentage
double get_water_height() {
  // Convert analog level to voltage
  double level = analogRead(water_analog_pin) * (5.0 / 1023.0);
  // Calculate percentage and return it
  level = level - water_height_min;
  level = 100 * level / (water_height_max - water_height_min);
  return level;
}

// ################################################################################
// ||                                                                            ||
// ||                              Motor functions                               ||
// ||        (This needs to be adjusted after connecting the real motor)         ||
// ||                                                                            ||
// ################################################################################

// Initialize motor for retracting the net
void setup_motor() {
  pinMode(motor_forward_led, OUTPUT);
  pinMode(motor_forward_led, OUTPUT);
  digitalWrite(motor_forward_led, LOW);
  digitalWrite(motor_forward_led, LOW);
}

// Stops the motor
void motor_stop() {
  digitalWrite(motor_forward_led, LOW);
  digitalWrite(motor_backward_led, LOW);
}

// Starts motor in forward direction (Returning the net)
void motor_forward() {
  motor_stop();
  digitalWrite(motor_forward_led, HIGH);
}

// Starts motor in backward direction (Retracting the net)
void motor_backward() {
  motor_stop();
  digitalWrite(motor_backward_led, HIGH);
}