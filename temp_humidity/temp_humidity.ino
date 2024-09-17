const int analogIn = A0; 
int humiditysensorOutput = 0; 
int RawValue= 0; 
double Voltage = 0; 
double tempC = 0; 
double tempF = 0; 
void setup(){ 
Serial.begin(9600); 
pinMode(A1, INPUT); 
} 
void loop(){ 
RawValue = analogRead(analogIn); 
Voltage = (RawValue / 1023.0) * 5000; 
tempC = (Voltage-500) * 0.1; 
tempF = (tempC * 1.8) + 32; 
Serial.print("Raw Value = " ); 
Serial.print(RawValue); 
Serial.print("\t milli volts = "); 
Serial.print(Voltage,0); // 
Serial.print("\t Temperature in C = "); 
Serial.print(tempC,1); 
Serial.print("\t Temperature in F = "); 
Serial.println(tempF,1);
humiditysensorOutput = Serial.print("Humidity: "); 
Serial.print(map(humiditysensorOutput, 0, 1023, 10, 70)); 
Serial.println("%"); 
analogRead(A1); 
delay(5000); 
}