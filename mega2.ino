//Dht11
#include <dht.h>
#define dht_apin A0 // Analog Pin sensor is connected to

//Ultra
#define echoPin 3 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 4 //attach pin D3 Arduino to pin Trig of HC-SR04
int res[6] = {0,0,0,0,0,0};
//dht
dht DHT;
const int buzzer = 9; //buzzer to arduino pin 9

//MQ2
int smoke = A5;

// Your threshold value
int sensorThres = 600;

//vibration 
int vib_pin=7;

//ultra
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

void setup(){
  Serial.begin(9600);
  //DHT11
  delay(500);//Delay to let system boot
    
  //buzzer
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  
  //MQ2
  pinMode(smoke, INPUT);
  
  //vibration
  pinMode(vib_pin,INPUT);
  
  //Ultra
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

}
void loop()
{
  //DHT11
  DHT.read11(dht_apin);
  
  //MQ2
  int analogSensor = analogRead(smoke);

  //UltraSonic
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

  //in house alerts
  int val;
  val=digitalRead(vib_pin);
  
  if (val==1||DHT.temperature>=34 || analogSensor > sensorThres||DHT.temperature>=34)
  {
    tone(buzzer, 1000, 200);
    delay(1000);
  }
  else
  {
    noTone(buzzer);
  }

//python
  if(distance<=10&&distance>=4)
  {
    res[2] = 1;
  }
  else if(distance>10)
  {
    res[2] = 0;
  }
  //
  if(DHT.temperature>=30 && analogSensor > sensorThres)
  {
//    Serial.print("Alert!! Fire is in the apartment!!");
    res[5] = 1;
  }
  else
  {
    res[5] = 0;
  }
  int Set_temp_DHT = 28;
  res[0]=res[1]=0;
  if(DHT.temperature<Set_temp_DHT)
  {
    res[0] = 1;
  }
  else if(DHT.temperature>Set_temp_DHT)
  {
    res[1] = 1;
  }
  res[3] = DHT.humidity;
  res[4] = DHT.temperature;
  Serial.print("q: ");
  Serial.print(res[0]);
  Serial.print(" ");
  Serial.print(res[1]);
  Serial.print(" ");
  Serial.print(res[2]);
  Serial.print(" ");
  Serial.print(res[3]);
  Serial.print(" ");
  Serial.print(res[4]);
  Serial.print(" ");
  Serial.print(res[5]);
  Serial.print("\n");
}
