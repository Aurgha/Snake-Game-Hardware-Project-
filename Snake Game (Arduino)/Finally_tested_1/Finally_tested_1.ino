// UTFT_Demo_320x240 
#include <UTFT.h>
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
UTFT myGLCD(ILI9325D_16,38,39,40,41);

struct item{
  int x;
  int y;
  };

item snake[100];
item food;
int snake_position = 1;//if 0 means that going left,1 means that going right,2 means that going down,3 means that going up
int snakesize = 5;
int point = 0;



void setup() {  
  Serial.begin(9600);
  pinMode(8,INPUT);//left
  pinMode(9,INPUT);//up
  pinMode(10,INPUT);//right
  pinMode(11,INPUT);//down
  randomSeed(analogRead(0));  // Setup the LCD  
  myGLCD.InitLCD();  
  myGLCD.setFont(SmallFont); 
  myGLCD.fillScr(0,106,78);
  draw_snake();
  generate_food();
}

  
void loop() {
  int radius = 5;
  while(1){

    Serial.println(snake[0].x);
    Serial.print(",");
    Serial.println(snake[0].y);
      
    myGLCD.fillScr(0, 106, 78);
    drawfood();
    
    score_board();
    running_the_snake();
    taking_input();
  
    if(snake_position == 0)
      snake[0].x = snake[0].x - 10; 
      
    else if(snake_position == 1)
      snake[0].x = snake[0].x + 10;
      
    else if(snake_position == 2)
      snake[0].y = snake[0].y + 10; 
       
    else if(snake_position == 3)
      snake[0].y = snake[0].y - 10;  
        
    for(int i = 0;i<snakesize;i++)
    {
      myGLCD.setColor(244, 42, 65);  
      myGLCD.fillCircle(snake[i].x,snake[i].y,radius);
    }
    
  }
  delay(10000);
  deactivate_and_wait();
}

  
void draw_snake()
{
  int radius = 5;
  int snakeheadx = random(0,10);
  int snakeheady = random(50,100);
  snake[0].x = snakeheadx;
  snake[0].y = snakeheady;
  for(int i = 1;i<snakesize;i++)
  {
     snake[i].x = snake[i-1].x+radius + radius;
     snake[i].y = snake[i-1].y;  
  }
  
  for(int i = 0;i<snakesize;i++)
  {
    myGLCD.setColor(244, 42, 65);  
    myGLCD.fillCircle(snake[i].x,snake[i].y,radius);
  }
}


void deactivate_and_wait(){
  // set Databus inactive to prevent latchup 
  //22 to 37  
  for (int i = 22; i<=37; i++)
    pinMode(i,INPUT_PULLUP);
       
  delay(10000);
  
  for (int i = 22; i<=37; i++)
    pinMode(i,OUTPUT); 
}

       
void running_the_snake(){  
   for(int i = snakesize-1;i>0;i--)
      snake[i] = snake[i-1]; 

   collition();
}   

    
 void taking_input(){
  
    if(digitalRead(8) == 1 && snake_position != 1)
        snake_position = 0;
    if(digitalRead(10) == 1 && snake_position != 0)
        snake_position = 1;
    if(digitalRead(11) == 1 && snake_position != 3)
        snake_position = 2;
    if(digitalRead(9) == 1 && snake_position != 2)
        snake_position = 3;
}


 void collition()
 {
    if(snake[0].x>= food.x-10 && snake[0].x<= food.x+10 && snake[0].y>= food.y-10 && snake[0].y<= food.y+10){
       generate_food();
       point++;
    }
 }
 
 void drawfood()
 {
  myGLCD.setColor(244, 42, 65);  
  myGLCD.fillCircle(food.x,food.y,5);
 }
 
 void generate_food()
 {
     food.x = random(0,319);
     food.y = random(0,239);
     drawfood();
 }

 void score_board()
 {
     myGLCD.setColor(0, 0, 0);  
     myGLCD.fillRect(0 , 0 , 50 , 30);
     myGLCD.setColor(244, 244, 244);
     myGLCD.printNumI(point , 10 , 10);
 }
