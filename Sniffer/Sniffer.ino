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
          } 
          else {
Serial.println("no data");
}

}
