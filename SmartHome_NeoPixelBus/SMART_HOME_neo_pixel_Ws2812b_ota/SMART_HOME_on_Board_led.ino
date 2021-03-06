// including libraries
#include <WiFi.h>
#include <PubSubClient.h>



//Defining Pin for whic led is connected
#define LED 2  



//Defining MQTT Adafruit Keys
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "ankitkothari29"   // Change your key
#define AIO_KEY         "eaf8dc2d131e48b7b1d967b5f364fe15" // Change your key
#define AIO_FEED        "ankitkothari29/feeds/led"   // Change your key




//Defining WIFI Credentials
const char* ssid     = "ANKIT-Dlink_Network";
const char* password = "Compaq@8826";

WiFiClient espClient;
PubSubClient client(espClient);



void setup()  //Under Void setup code will be run only once.
{
  Serial.begin(115200); //To print the output in console 115200 is buad rate
  Serial.print("Welcome to Smart Home demo");


  pinMode(LED, OUTPUT);// Wheather the device is input / output

  Serial.print("Connecting to ");
  Serial.println(ssid);

  
  WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {   //untill WIFI not connected try agin with delay of 0.5 sec
    delay(500);
    Serial.print(".");   //print on the console
  }


  digitalWrite(LED, LOW); //By default turninng off
  
   
  Serial.print("Connected");
  client.setServer(AIO_SERVER, 1883);
  client.setCallback(callback); // Call function
 
}






void loop()    // Loop run Continously
{
  if (!client.connected()) { //! used for not - if mqtt client not connected try again (Call connection function)
    reconnect();
  }
  client.loop();  //if connected sync with server
}








void callback(char* topic, byte* payload, unsigned int length) { // Subscribe to the channel (Device name for which message is recieved)
  Serial.print("Message arrived [");
  Serial.print(topic);   //Print for which device msg is recieved
  Serial.print("] ");
  for (int i = 0; i < length; i++) { // read the whole message charcter by charcter
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);

//LED ON
    
    if (receivedChar == '1') {   //if state send is 0 then turn on led
      digitalWrite(LED, HIGH); 
      Serial.print("led on");
   
  }
//LED OFF
      
  
    if (receivedChar == '0') {
     digitalWrite(LED, LOW); 
      Serial.print("led off");
     
    }






  }
  Serial.println(); // print new line 
}










void reconnect() {  // function to reconnect with mqtt
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32", AIO_USERNAME, AIO_KEY)) {
      Serial.println("connected");
      client.subscribe(AIO_FEED);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}
