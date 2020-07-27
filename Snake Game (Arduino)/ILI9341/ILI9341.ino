#include <Adafruit_GFX.h>       // include Adafruit graphics library
#include <Adafruit_ILI9341.h>   // include Adafruit ILI9341 TFT library
 
#define TFT_CS    8      // TFT CS  pin is connected to arduino pin 8
#define TFT_RST   9      // TFT RST pin is connected to arduino pin 9
#define TFT_DC    10     // TFT DC  pin is connected to arduino pin 10
// initialize ILI9341 TFT library
Adafruit_ILI9341 myGLCD = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
 
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
  //myGLCD.InitLCD();  
 // myGLCD.setFont(SmallFont); 
// myGLCD.fillScr(0,106,78);
  draw_snake();
  generate_food();
}

  
void loop() {
 //myGLCD.fillScr(0, 106, 78);
  int radius = 5;
  while(1){

  Serial.println(snake[0].x);
  Serial.print(",");
  Serial.println(snake[0].y);
    
  running_the_snake();
  taking_input();
  collition();

//value = digitalRead(8);
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
//  myGLCD.setColor(244, 42, 65);  
//  myGLCD.drawCircle(snake[i].x,snake[i].y,radius);
  }
//  myGLCD.fillScr(0, 106, 78);
  drawfood();
  }
    delay(10000);
  deactivate_and_wait();
}

void draw_snake()
{
  // snakesize =5;
  int radius = 5;
  int snakeheadx = random(30,60);
  int snakeheady = random(20,40);
  snake[0].x = snakeheadx;
  snake[0].y = snakeheady;
  for(int i = 1;i<snakesize;i++)
  {
      snake[i].x = snake[i-1].x+radius + radius;
      snake[i].y = snake[i-1].y;  
  }
  
  for(int i = 0;i<snakesize;i++)
  {
//  myGLCD.setColor(244, 42, 65);  
//  myGLCD.drawCircle(snake[i].x,snake[i].y,radius);
  }
  
}
void deactivate_and_wait(){
  // set Databus inactive to prevent latchup 
  //22 to 37  
  for (int i = 6; i<=21; i++)
       pinMode(i,INPUT_PULLUP);   
       delay(100000);
    for (int i = 6; i<=21; i++)
       pinMode(i,OUTPUT); 
       }

       
 void running_the_snake()
 {
   
   for(int i = snakesize-1;i>0;i--)
   {
        snake[i] = snake[i-1];
   } 
 }   

    
 void taking_input()
 {
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
    if(snake[snakesize-1].x == food.x && snake[snakesize-1].y == food.y)
       generate_food();
 }
 void drawfood()
 {
//  myGLCD.setColor(244, 42, 65);  
  myGLCD.fillCircle(food.x,food.y,5);
 }
 void generate_food()
 {
     food.x = random(0,319);
     food.y = random(0,239);
     drawfood();
 }}
