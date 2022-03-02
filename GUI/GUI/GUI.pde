import controlP5.*;
import processing.serial.*;

// defining boundaries for maping movements 
static final int maxHeight = 500;
static final int maxWidth = 500;
static final int minHeight = 250;
static final int minWidth = 10;

float robotX;
float robotY;

//  for calibration
float robotHeading = 270;
float scale = 10;

Serial port;  // Serial Port Object - to access serial port

ControlP5 cp5; // ControlP5 object - for gui 

void setup(){ 
  
  robotX = 260;
  robotY = 740;
  
  size(520, 800);  // Window size, (width, height)
  port = new Serial(this, "/dev/cu.usbserial-DA01GXP5", 9600);  // Change this to your port
  
  cp5 = new ControlP5(this);
  
  cp5.addButton("UTurn").setPosition(10, 10).setSize(70, 70);   
  
  cp5.addButton("Stop").setColorBackground(color(255,0,0)).setColorLabel(color(255,255,0)).setPosition(90, 10).setSize(70, 70);  
  
  cp5.addButton("FullTurn").setPosition(170, 10).setSize(70, 70);
  
  cp5.addButton("Left90").setPosition(10, 90).setSize(70, 70);
  
  cp5.addButton("Forward").setColorBackground(color(81, 206, 61)).setPosition(90, 90).setSize(70,70);
  
  cp5.addButton("Right90").setPosition(170, 90).setSize(70, 70); 
  
  cp5.addButton("Left").setColorBackground(color(81, 206, 61)).setPosition(10, 170).setSize(70, 70); 
  
  cp5.addButton("Backward").setColorBackground(color(81, 206, 61)).setPosition(90, 170).setSize(70, 70);
  
  cp5.addButton("Right").setColorBackground(color(81, 206, 61)).setPosition(170, 170).setSize(70, 70);

  cp5.addButton("Manual").setColorBackground(color(153, 51, 255)).setPosition(250,10).setSize(70, 70);
}

void draw(){ 

  //background(179, 230, 255);
  
  strokeWeight(2);  // creating a weight to map zumo movement 
  noFill();
  rect(minWidth, minHeight, maxWidth, maxHeight);
  
  while (port.available() > 0) {
    
    String input = port.readString();
    //System.out.print(input);
    if(input.equals("u-turn")){
      robotTurn(180);
    }else if(input.equals("full-turn")){
      robotTurn(360);
    }else if(input.length() >= 3){
      String strAngle = input.substring(0,2);
      char side = input.charAt(2);
    
      try{
        int intAngle = Integer.parseInt(strAngle);
        switch(side){
          case 'r':
            robotTurn(intAngle);
            break;
          case 'l':
            robotTurn(intAngle * -1);
            break;
        }
      }catch(NumberFormatException ex){
        switch(input){
          case "forward": 
            robotForward(scale);
            break;
          case "backward":
            robotForward(-scale);
            break;
        }
      }
    }
  }
   
}

void keyPressed() {
  switch(key){
    case 'u':
      port.write('u'); 
      break;
    case 'b':
      port.write('b'); 
      break;
    case 'y':
      port.write('y'); 
      break;
    case 'q':
      port.write('q'); 
      break;
    case 'w':
      port.write('w'); 
      break;
    case 'e':
      port.write('e'); 
      break;
    case 'a':
      port.write('a'); 
      break;
    case 's':
      port.write('s'); 
      break;
    case 'd':
      port.write('d'); 
      break;
    case 'm':
      port.write('m'); 
      break;
  }
}

void UTurn(){
  port.write('u'); 
}

void Stop(){
  port.write('b'); 
}

void FullTurn(){
  port.write('y');
}

void Left90(){
  port.write('q');
}

void Forward(){
  port.write('w');
}

void Right90(){
  port.write('e');
}

void Left(){
  port.write('a');
}

void Backward(){
  port.write('s');
}

void Right(){
  port.write('d');
}

void Manual(){
  port.write('m');
}

void robotForward(float amount){
  strokeWeight(10);
  float newX = robotX + cos(radians(robotHeading)) * amount;
  float newY = robotY + sin(radians(robotHeading)) * amount;

  line(robotX, robotY, newX, newY);
  fill(0);
  
  robotX = newX;
  robotY = newY;
}

void robotTurn(float degrees){
  robotHeading += degrees;
}
