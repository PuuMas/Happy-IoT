  #include <SimpleDHT.h> // DHT library
  #define POWER_PIN  7
  #define SIGNAL_PIN A5

const int pinDHT11 = 2; //DHT sensorin pin
const int LDR = A0; // LDR vastus pin
int red_light_pin= 11; // Red Light
int green_light_pin = 10; // Green Light
int blue_light_pin = 9; // Blue Light
int LDR_input_val = 0; //LDR arvo

SimpleDHT11 dht11; // DHT11 objecti
float temperature = 0.0; // Lämpötila
float humidity = 0.0; // Kosteus
byte data[40] = {0};

int i = 0; // Otetaan numerot ettei tule spämmiä konsoliin


int value = 0; // variable to store the water sensor value



void setup() {

  Serial.begin(9600); // Serial comm begin at 9600bps

  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);

  
if(dht11.read2(pinDHT11, &temperature, &humidity, data)){
  RGB_color(255,0,0); //If error show red led
  Serial.print("Virhe lukiessa dataa");
}

}

void loop() {
if(i <= 1){
  RGB_color(0,255,0); // Set the color of the RGB to Green
  
  LDR_input_val = analogRead(LDR);
  
  digitalWrite(POWER_PIN, HIGH);  // turn the water sensor ON
  delay(10);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from  water sensor
  digitalWrite(POWER_PIN, LOW);   // turn the  water sensor OFF
  
        //Look for the LDR values
      if(LDR_input_val < 150){
        Serial.print("HIGH");
        }
        else if(LDR_input_val > 600){
          Serial.print("LOW");
        }
        else{
          Serial.print("MEDIUM");
        }
      Serial.print("x");
      //Look for the water sensor values
       if(value < 300){
        Serial.print("LOW");
        }
        else if(value > 870){
          Serial.print("HIGH");
        }
        else{
          Serial.print("MEDIUM");
        }
        
      Serial.print("x");
      Serial.print(temperature); // Print the tempature value
      Serial.print("x");
      Serial.print(humidity); // Print the humidity value
      Serial.println("x");
      delay(5000); // five sec delay
      i++;
  }
  else{
    RGB_color(255,0,0); //show red led when no data is read 
    exit; // Exit the continues loop
  }
}


void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
