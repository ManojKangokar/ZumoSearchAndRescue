import controlP5.*;
import processing.serial.*;
import java.util.*;

// defining boundaries for maping movements 
static final int maxHeight = 500;
static final int maxWidth = 500;
static final int minHeight = 250;
static final int minWidth = 10;
static final float roomSize = 10;
static final float objectSize = 20;

String displayText;
String modeText;

float robotX;
float robotY;

//  for calibration
float robotHeading = 270;
float scale = 5;

// for printing room locations
ArrayList < Float > roomLocationsX = new ArrayList < Float > ();
ArrayList < Float > roomLocationsY = new ArrayList < Float > ();

ArrayList < Float > objectLocationsX = new ArrayList < Float > ();
ArrayList < Float > objectLocationsY = new ArrayList < Float > ();
Serial port;  // Serial Port Object - to access serial port

ControlP5 cp5; // ControlP5 object - for gui 

void setup(){ 
  
  robotX = 250;
  robotY = 740;
  
  displayText = "System Ok";
  modeText = "Manual-control";
  //DA01GXP5
  size(520, 800);  // Window size, (width, height)
  port = new Serial(this, "/dev/cu.usbserial-AL1L30CR", 9600);  // Change this to your port
  
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
  
  cp5.addButton("Auto").setColorBackground(color(153, 51, 255)).setPosition(250,90).setSize(70, 70);
  
  cp5.addButton("SearchLeft").setColorBackground(color(153, 51, 255)).setPosition(330,10).setSize(70, 70);

  cp5.addButton("SearchRight").setColorBackground(color(153, 51, 255)).setPosition(410,10).setSize(70, 70);
}

void draw(){ 

  //background(179, 230, 255);
  
  strokeWeight(2);  // creating a weight to map zumo movement 
  noFill();
  rect(minWidth, minHeight, maxWidth, maxHeight);
  
  while (port.available() > 0) {
    
    String input = port.readString();
    
    System.out.print(input);
    
    if(input.contains("u-turn")){
      robotTurn(180);
    }else if(input.contains("full-turn")){
      robotTurn(360);
    }else if(input.contains("90l")){
      robotTurn(360 - 90);
    }else if(input.contains("90r")){
      robotTurn(90);
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
            robotTurn(360 - intAngle);
            break;
        }
      }catch(NumberFormatException ex){
        
      }
    }
    
    if(input.contains("forward")){
      
      robotForward(scale);
    }
    if(input.contains("backward")){
      robotForward(scale * -1);
    }
    if(input.contains("room")){
      roomLocationsX.add(robotX);
      roomLocationsY.add(robotY);
    }
    if(input.contains("object")){
      objectLocationsX.add(robotX);
      objectLocationsY.add(robotY);
    }
    if(input.contains("corner-hit")){
      displayText = "Corner Hit";
    }
    if(input.contains("Auto-control")){
      modeText = "Auto-control";
    }
    if(input.contains("Manual-control")){
      modeText = "Manual-control";
    }
  }
  // if there is a room then put a box, if it finds an object then put a circle that is red
  if (!(roomLocationsX.isEmpty())){
    for(int i = 0; i < roomLocationsX.size(); i++){
      fill(255,255,200);
      rect(roomLocationsX.get(i),roomLocationsY.get(i),-10,-10);
    }
  }
  if (!(objectLocationsX.isEmpty())){
    for(int i = 0; i < objectLocationsX.size(); i++){
      fill(255,0,0);
      circle(objectLocationsX.get(i), objectLocationsY.get(i), objectSize);
    }
  }
  fill(0);
  rect(330,90,180,100);
  fill(255);
   textSize(28);
   text(displayText, 330, 120); 
   text(modeText, 330, 170); 
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
    case 'g':
      port.write('g');
      break;
    case 'h':
      port.write('h');
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

void Auto(){
  port.write('n');
}

void SearchLeft(){
 port.write('g'); 
}

void SearchRight(){
 port.write('h'); 
}

void robotForward(float amount){
  strokeWeight(10);
  float newX = robotX + cos(radians(robotHeading)) * amount;
  float newY = robotY + sin(radians(robotHeading)) * amount;
  
  fill(0);
  line(robotX, robotY, newX, newY);
  strokeWeight(1);
  fill(204, 102, 0);
  circle(newX, newY, 10);
  
  
  robotX = newX;
  robotY = newY;
}

void robotTurn(float degrees){
  robotHeading += degrees;
}
