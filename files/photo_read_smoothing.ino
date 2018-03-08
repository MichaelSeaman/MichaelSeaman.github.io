/*
 *  Analog input read
 *  Using photoresistor circuit as described:
 *  https://www.arduino.cc/en/Tutorial/AnalogInput
 *
 */
#define nCalibrationMeasurements 20
#define calibrationTime 1000
 
int sensorPin = A0;
int ledPin = 13;
int sensorValue = 0;
double meanVal = 0;
int stdVal = 1;
int threshhold = 3;
int threshholdStd = 10;
double alphaSmooth = 0.01;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  int params[2] = {0, 1};
  calibrate(params);
  meanVal = params[0];
  stdVal = params[1];
  threshhold = updateThreshold(meanVal, stdVal);

  Serial.print("Mean photo value of: ");
  Serial.println(meanVal);
  Serial.print("Photo STD: ");
  Serial.println(stdVal);
  Serial.print("Calculated Threshhold: ");
  Serial.println(threshhold);

}

void calibrate(int *cdata) {
  int readings[nCalibrationMeasurements];
  int caliDelay = calibrationTime / nCalibrationMeasurements;

  readings[0] = analogRead(sensorPin);
  for(int i = 1; i < nCalibrationMeasurements; ++i){
    delay(caliDelay);
    readings[i] = analogRead(sensorPin);
  }
  int meanVal = arrayMean(readings, nCalibrationMeasurements);
  int stdVal = arraySTD(readings, nCalibrationMeasurements);
  cdata[0] = meanVal;
  cdata[1] = stdVal;
}

int arrayMean(int *a, int size){
  int sum = 0;
  for(int i = 0; i < size; ++i) {
    sum += a[i];
  }
  return sum / size;
}

int arraySTD(int *a, int size){
  int mean = arrayMean(a, size);
  int variance = 0;
  int std = 0;
  for (int i = 0; i < size; i++) {
    variance += sq(a[i] - mean);
  }
  variance /= size;
  std = sqrt(variance);
  return std;

}

void loop() {
  // put your main code here, to run repeatedly:

  sensorValue = analogRead(sensorPin);
  if(sensorValue > threshhold){
    Serial.println();
    Serial.print("New high read: ");
    Serial.println(sensorValue);
  }
  digitalWrite(ledPin, HIGH);
  delay(sensorValue);
  digitalWrite(ledPin, LOW);
  delay(sensorValue);
  meanVal = smoothedMovingAverage(meanVal, sensorValue, alphaSmooth);
  threshhold = updateThreshold(meanVal, stdVal);
  Serial.println(threshhold);
}

double smoothedMovingAverage(double ave, double newRead, double alpha) {
  return newRead * alpha + (1 - alpha) * ave;
}

int updateThreshold(double mean, int std) {
  return mean + threshholdStd * std;
}
