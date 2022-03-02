import controlP5.*;
import processing.serial.*;

// defining boundaries for maping movements 
static final int maxHeight = 500;
static final int maxWidth = 500;
static final int minHeight = 250;
static final int minWidth = 10;

int startx = 260;
int starty = 720;
int endx = 260;
int endy = 720;

Serial port;  // Serial Port Object - to access serial port

ControlP5 cp5; // ControlP5 object - for gui 

void setup(){ 
  
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

  background(179, 230, 255);
  
  strokeWeight(2);  // creating a box to map zumo movement 
  noFill();
  rect(minWidth, minHeight, maxWidth, maxHeight);
  
  while (port.available() > 0) {
    String input = port.readString();
    switch(input){
      case "forward": 
        endy += 1;
        print("forward");
        break;
      case "stop":
        line(260, 700, 260, 500);
        line(startx, starty, endx, endy);
        print("stop");
        startx = endx;
        starty = endy;
        break;
      case "backward":
        endy -= 1;
        break;
    }
  }
  //line(x, y, x, y);
   
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
