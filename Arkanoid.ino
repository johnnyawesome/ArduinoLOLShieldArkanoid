/*-- Cosmetics to do:

    - Ships don't move when Ball is not coming
    - Increasing Speed
    - Kometenschweif auf Ball
*/

#include <Charliplexing.h>
#include <Figure.h>
#include <Font.h>

int8_t ballx = random(0,7);
int8_t bally = random(0,8);
int8_t dx = 1;
int8_t dy = 1;
int8_t sp1y = 0;

int8_t bottombounce = 0;
int8_t nohitcount = 0;
int8_t repetition = 0;

int8_t row1[] ={1,1,1,1,1,1,1,1,1};
int8_t row2[] ={1,1,1,1,1,1,1,1,1};  
int8_t row3[] ={1,1,1,1,1,1,1,1,1};
int8_t row4[] ={1,1,1,1,1,1,1,1,1}; 
int8_t row5[] ={1,1,1,1,1,1,1,1,1};

int8_t lastballx; //To save last Ball X position
int8_t lastbally; //To save last Ball Y position


// bally = random(9);

void setup(){
  
   LedSign::Init(); //Initialize LOLShield 
  
   LedSign::SetBrightness(20); 
 
   randomSeed(analogRead(0)); //Initialize Random Number
 
}

void loop(){

  repetition++;
    
  ballx = constrain(ballx,0,13);
  bally = constrain(bally,0,8);
  
  
  //##################### BALL MOVEMENT ######################
  
   //Saves last Ball X Position
   lastballx = ballx;
   lastbally = bally;
   
   // Calculates new X and Y Ball Values
   ballx = ballx + dx;
   bally = bally + dy;
 
   //Bounce off Wall top X
   if( ballx == 13){
     dx = - 1;
   }
   //Bounce off Wall bottom X
   if(ballx == 1 ){
      dx = + 1;
      
      //Randomisation of ball movement
      bottombounce++;
        if(bottombounce >= 5 && bally < 8){
          bally = bally + 1;
          bottombounce == 0; 
        }    
   }
  
   //Bounce off Wall top Y
   if( bally == 8){
      dy = - 1;
   }
   //Bounce off Wall bottom Y
   if(bally == 0 ){
      dy = + 1;
   }  
   

   

   //######################################
   
   
   
   
   //################# ROW BLASTING BEGIN #####################

    nohitcount++;
    
   //Kill Rows
   if( ballx == 10 && row4[bally] == 1){
     row4[bally] = 0;
     dx = - 1;
     nohitcount = 0;
   }

   if( ballx == 11 && row3[bally] == 1){
     row3[bally] = 0;
     dx = - 1;
     nohitcount = 0;
   } 

   if( ballx == 12 && row2[bally] == 1){
     row2[bally] = 0;
     dx = - 1;
     nohitcount = 0;
   }

     if( ballx == 13 && row1[bally] == 1){
     row1[bally] = 0;
     dx = - 1;
     nohitcount = 0;
   }

  //######################################
   
   

   //##################### SHIP MOVEMENT ######################

    //Cosmetic: Makes ship stop if the ball just bounced off of it.
    if(lastballx >= ballx){
  
      // ### Ship Movement ###
      if(bally >= sp1y){
       sp1y= sp1y + 1;
      }
      else{
       sp1y = sp1y -1;
      }
      if(sp1y == 8){
        sp1y = sp1y -1;
      }
      if(sp1y == 0){
        sp1y = sp1y +1;
      }
      
    }
     
  //######################################

  
  // RESET GAME IF ENDLESS LOOP 
   if ((nohitcount >= 10) && (ballx == 13) && (repetition >= 50)){
     resetgame(); 
   } 
 
  //Paint Objects

  delay(130);
  LedSign::Clear();
  
  paintships();
  paintrows();
  paintball();

}  
  
void paintball(){
//  LedSign::Set(lastballx,lastbally,7);  //Values: First Number: X Axis Position, Second Number: Y Axis Position, third Nubmer: LED ON/OFF
  LedSign::Set(ballx,bally,1);  //Values: First Number: X Axis Position, Second Number: Y Axis Position, third Nubmer: LED ON/OFF 

}

void paintships(){
  LedSign::Set(0,sp1y,1);  //Values: First Number: X Axis Position, Second Number: Y Axis Position, third Nubmer: LED ON/OFF  
  LedSign::Set(0,sp1y+1,1);  //Values: First Number: X Axis Position, Second Number: Y Axis Position, third Nubmer: LED ON/OFF
  LedSign::Set(0,sp1y-1,1);  //Values: First Number: X Axis Position, Second Number: Y Axis Position, third Nubmer: LED ON/OFF
}


void paintrows(){
 
  //Paint TopRow (13)
  for (int i = 0; i <= 8; i++){
    LedSign::Set(13,i,row1[i]);
    LedSign::Set(12,i,row2[i]);
    LedSign::Set(11,i,row3[i]);
    LedSign::Set(10,i,row4[i]);
  }
 
}

void resetgame(){

     nohitcount = 0; 
     
     ballx = random(2,8);
     bally = random(2,8);
     
    for(int i = 0; i <= 8; i++){
       row1[i] = 1;
       row2[i] = 1;
       row3[i] = 1;
       row4[i] = 1;
       
     }

     LedSign::Clear(1);
     delay (400);
     LedSign::Clear(0);
     delay (300);
     LedSign::Clear(1);
     delay (300);
     LedSign::Clear(0);
     delay (300); 
     LedSign::Clear(0);
     delay (300); 
  
}


