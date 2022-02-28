import controlP5.*;
import processing.serial.*;

Serial port;  // Serial Port Object - to access serial port

ControlP5 cp5; // ControlP5 object - for gui 

void setup(){ 
  
  size(700, 700);  // Window size, (width, height)
  //port = new Serial(this, "/dev/cu.usbserial-DA01GXP5", 9600);  // Change this to your port
  
  cp5 = new ControlP5(this);
  
  cp5.addButton("UTurn").setColorBackground(255,0,0).setPosition(10, 10).setSize(70, 70);   
  
  cp5.addButton("Stop").setPosition(90, 10).setSize(70, 70);  
  
  cp5.addButton("FullTurn").setPosition(170, 10).setSize(70, 70);
  
  cp5.addButton("90Left").setPosition(10, 90).setSize(70, 70);
  
  cp5.addButton("90Right").setPosition(170, 90).setSize(70, 70); 
}

void draw(){ 

  background(179, 230, 255);
    
}

void UTurn(){
  //port.write('u'); 
}

void FullTurn(){
  //port.write('y');
}
