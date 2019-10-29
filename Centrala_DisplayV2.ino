#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 256 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET LED_BUILTIN  //4
Adafruit_SSD1306 display(OLED_RESET);
 
const char* ssid = "WIFI";
const char* password = "PASS";
 
void setup() {
  delay(1000);
  Serial.begin(115200);

  SPI.begin();           // Init SPI bus dispolay
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");
 
  Serial.print("Connecting");
  
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Conectare..");
  display.println("La WIFI");
  display.display();
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Asteapta..");
    display.display();
    Serial.print(".");
    delay(500);
  }
 
  
  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

 

  // Clear the buffer.
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Pornesc...");
  delay(4000);
  display.display();
}

void loop() {
 
////////////SURSA 1 Start

if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
 
http.begin("http://adrian-pi.go.ro/remote/ambient.php");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
String payload = http.getString();   //Get the request response payload

Serial.println ("Dormitor..."); //Print the response payload
Serial.println ("Setata  ..."); //Print the response payload
Serial.println (payload); //Print the response payload


/// iau in ram
  
  display.clearDisplay();
  display.setTextSize(2.1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(payload);
  display.display();
  delay(8000);


  /// ce urmeaza sa arat din ram
    
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("Afara ...");
  display.println("Adrian ...");
  display.display();
  delay(8000);

}
 
http.end();   //Close connection
}
delay(1000);

//////////// Sursa 1 END


////////////SURSA 2 Start

if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
HTTPClient http;  //Declare an object of class HTTPClient
 
http.begin("http://adrian-pi.go.ro/remote/ambient2.php");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
 
if (httpCode > 0) { //Check the returning code
 
String payload = http.getString();   //Get the request response payload

Serial.println ("Afara  ..."); //Print the response payload
Serial.println ("Adrian ..."); //Print the response payload
Serial.println (payload); //Print the response payload

 /// iau in ram
  
  display.clearDisplay();
  display.setTextSize(2.1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(payload);
  display.display();
  delay(8000);


  /// ce urmeaza sa arat din ram
    
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("Dormitor..");
  display.println("Setata ...");
  display.display();
  delay(8000);
}
 
http.end();   //Close connection
 
}

////////////SURSA 2 END
}
  
