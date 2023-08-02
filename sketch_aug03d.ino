const int gasSensorPin = A0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(gasSensorPin);
  float voltage = sensorValue * (5.0 / 1023.0); // Convert analog value to voltage
  float ppm = convertToPPM(voltage); // Convert voltage to parts per million (PPM)
  
  Serial.print("Gas Concentration (PPM): ");
  Serial.println(ppm);

  delay(1000); // Adjust the delay based on your monitoring requirements
}

// Function to convert sensor voltage to PPM value for CO2 using MQ-135 datasheet curve
float convertToPPM(float voltage) {
  // MQ-135 sensitivity characteristic (R0/RS ratio) for CO2
  float sensitivity = 6.2;

  // MQ-135 nominal resistance in clean air (in kohms)
  float R0 = 76.63;

  // Calculate resistance of the sensor (in kohms) based on voltage and sensitivity
  float RS = (5.0 - voltage) / voltage * R0;

  // Calculate PPM using the sensitivity characteristic (RS/R0 ratio)
  float ppm = pow(10, (log10(RS / R0) - 2.602) / sensitivity);

  return ppm;
}
