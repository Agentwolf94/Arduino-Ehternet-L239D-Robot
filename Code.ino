/*
  Web Server
A simple web server
Circuit:
* Ethernet shield attached to pins 10, 11, 12, 13
*/
//-------------------------------------------------------------------------------------------------------
#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x48, 0xD3 };

// The IP address will be dependent on your local network:
// assign an IP address for the controller:

IPAddress ip(192,168,1,20);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255, 255, 255, 0);

// Initialize the Ethernet server library with the port you want to use.
EthernetServer server(8081);
String readString;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------
// Any extra codes for Declaration :

// Declare Pin 8 as an LED because thats what we will be connecting the LED to.You could use any other pin and would then have to change the pin number.

 int LeftMotorForward = 10; // Pin 10 has Left Motor connected on Arduino boards.
 int LeftMotorReverse = 9; // Pin 9 has Left Motor connected on Arduino boards.

 int RightMotorForward = 12; // Pin 12 has Right Motor connected on Arduino boards.
 int RightMotorReverse = 13; // Pin 13 has Right Motor connected on Arduino boards.

//-------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void setup()
{
//-------------------------------------------------

// Extra Set up code:
  pinMode(LeftMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorForward, OUTPUT);  // initialize the  pin as an output.
  pinMode(LeftMotorReverse, OUTPUT);  // initialize the  pin as an output.
  pinMode(RightMotorReverse, OUTPUT);  // initialize the  pin as an output.

//-------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//enable serial data print
  Serial.begin(9600);

  //start Ethernet
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("LED Controller Test 1.0");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

void loop()
{
// listen for incoming clients
  EthernetClient client = server.available();
  if (client)

  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())

      {
        char c = client.read();

        //read char by char HTTP request
        if (readString.length() < 100)

        {

          //store characters to string
          readString += c;
          //Serial.print(c);


          Serial.write(c);
          // if you've gotten to the end of the line (received a newline
          // character) and the line is blank, the http request has ended,
          // so you can send a reply
          //if HTTP request has ended
          if (c == '\n') {
            Serial.println(readString); //print to serial monitor for debuging
//--------------------------------------------------------------------------------------------------------
// Needed to Display Site:
client.println("HTTP/1.1 200 OK"); //send new page
            client.println("Content-Type: text/html");
            client.println();
            client.println("<HTML>");
            client.println("<HEAD>");

//--------------------------------------------------------------------------------------------------------
//-------------------------------------------------
// what is being Displayed :     
        
            client.println("<TITLE>Home Automation</TITLE>");
            client.println("<center>");
            client.println("</HEAD>");
            client.println("<BODY>");
            client.println("<H1>Home Automation</H1>");
            client.println("<hr />");
            client.println("<center>");

            client.println("<a href=\"/?forward\"\">Move Forward</a>");
            client.println("<br />");
            client.println("<br />");
            
            client.println("<a href=\"/?stop\"\">All Stop</a><br />");  
            client.println("<br />");
            client.println("<br />");
  
            
            client.println("<a href=\"/?reverse\"\">Reverse</a><br />");     
            client.println("<br />");
            client.println("<br />");
            
            client.println("<a href=\"/?right\"\">Move Right</a><br />");  
            client.println("<br />");
            client.println("<br />");
            
            client.println("<a href=\"/?left\"\">Move Left</a><br />");  

            client.println("</BODY>");
            client.println("</HTML>");

            delay(1);
            //stopping client
            client.stop();

//--------------------------------------------------------------------------------------------------------
// Code which needs to be Implemented:
            if(readString.indexOf("?forward") >0)//checks for Forward ON
            {
              digitalWrite(RightMotorForward, HIGH);   // turn the Right Motor ON
              digitalWrite(LeftMotorForward, HIGH);   // turn the Left Motor ON
              delay(10000);               // wait for  10 seconds
              Serial.println("THE ROBOT WILL MOVE FORWARD");
            }
            
            else 
            
            {
              
              if(readString.indexOf("?stop") >0)//checks for Stop Button ON
              {
                digitalWrite(RightMotorReverse, LOW);   // turn the Right Motor ON
                digitalWrite(LeftMotorReverse, LOW);   // turn the Left Motor ON
   
                digitalWrite(RightMotorForward,LOW);   // turn the Right Motor OFF
                digitalWrite(LeftMotorForward, LOW);   // turn the Left Motor OFF
                Serial.println("THE ROBOT WILL BE STOP");;
              }
              
              if(readString.indexOf("?reverse") >0)//checks for Reverse Button ON
              {
               digitalWrite(RightMotorReverse, HIGH);   // turn the Right Motor ON
               digitalWrite(LeftMotorReverse, HIGH);   // turn the Left Motor ON
               delay(10000);               // wait for  10 seconds
               Serial.println("THE ROBOT WILL MOVE REVERSE");
              }
              
            }
              
//-------------------------------------------------            
            //clearing string for next read
            readString="";

            // give the web browser time to receive the data
            delay(1);
            // close the connection:
            client.stop();
            Serial.println("client disonnected");

          }
        }
      }
    }
  }
}
