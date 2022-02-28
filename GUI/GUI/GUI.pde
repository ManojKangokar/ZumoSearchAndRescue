import controlP5.*;
import processing.serial.*;

Serial port;  // Serial Port Object - to access serial port

ControlP5 cp5; // ControlP5 object - for gui 

void setup(){ 
  
  size(700, 700);  // Window size, (width, height)
  port = new Serial(this, "/dev/cu.usbserial-DA01GXP5", 9600);  // Change this to your port
  
  cp5 = new ControlP5(this);
  
  cp5.addButton("UTurn").setPosition(10, 10).setSize(70, 70);   
  
  cp5.addButton("Stop").setColorBackground(color(255,0,0)).setColorLabel(color(255,255,0)).setPosition(90, 10).setSize(70, 70);  
  
  cp5.addButton("FullTurn").setPosition(170, 10).setSize(70, 70);
  
  cp5.addButton("Left90").setPosition(10, 90).setSize(70, 70);
  
  cp5.addButton("Forward").setColorBackground(color(81, 206, 61)).setPosition(90, 90).setSize(70,70);
  
  cp5.addButton("90Right").setPosition(170, 90).setSize(70, 70); 
  
  cp5.addButton("Left").setColorBackground(color(81, 206, 61)).setPosition(10, 170).setSize(70, 70); 
  
  cp5.addButton("Backward").setColorBackground(color(81, 206, 61)).setPosition(90, 170).setSize(70, 70);
  
  cp5.addButton("Right").setColorBackground(color(81, 206, 61)).setPosition(170, 170).setSize(70, 70);

  cp5.addButton("Manual").setColorBackground(color(153, 51, 255)).setPosition(250,10).setSize(70, 70);
}

void draw(){ 

  background(179, 230, 255);
    
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
