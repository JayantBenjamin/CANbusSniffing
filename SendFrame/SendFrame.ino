#include <Canbus.h>
#include <defaults.h>
#include <global.h>
#include <mcp2515.h>
#include <mcp2515_defs.h>
void setup() {
  Serial.begin(38400); // For debug use
  Serial.println("CAN Read - Testing receival of CAN Bus message");  
  if(Canbus.init(CANSPEED_500)){ 
 //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  }else{
    Serial.println("Can't init CAN");
  }
}
void loop(){
  tCAN message;
if (mcp2515_check_message()){
    if (mcp2515_get_message(&message)) {
        if(message.id != -1) {
              Serial.print("<");
               Serial.print(message.id);

               for(int i=0;i<message.header.length;i++) {  
                  if (i == 3){
                    Serial.print(",");
                    Serial.print((message.data[3]*100)/255);
                  } else {
                  int state = (message.data[i]);
                  Serial.print(",");
                  Serial.print(state);
                  }                 
                }
               Serial.println(">");
               delay(10);
             }
           }
          } else {
    Serial.print(“No data”);

      message.id = 0; //The ID for the frame you are sending
        message.header.rtr = 0;
        message.header.length = 8; //formatted in DEC
        message.data[0] = 0; // place your custom value for ch1 here
        message.data[1] = 0;  // place your custom value for ch2 here
        message.data[2] = 0;  // place your custom value for ch3 here
        message.data[3] = 0;  // place your custom value for ch4 here 
        message.data[4] = 0;  // place your custom value for ch5 here
        message.data[5] = 0;   // place your custom value for ch6 here
        message.data[6] = 0;  // place your custom value for ch7 here
        message.data[7] = 0;  // place your custom value for ch8 here

Serial.print( "Message sent:   "); 
Serial.println( message.id);
for(int i =0; i <=7; i++){   
Serial.println(“, “); 
Serial.println( message.data[i]);
}

mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
mcp2515_send_message(&message);

}
}

