import processing.serial.*;
import g4p_controls.*;
// You can remove the PeasyCam import if you are not using
// the GViewPeasyCam control or the PeasyCam library.
import peasy.*;


Serial myPort;  // Create object from Serial class
int val;        // Data received from the serial port

public void setup(){
  size(480, 320, JAVA2D);
  
  createGUI();
  customGUI();

  String portName = "COM3";
  myPort = new Serial(this, portName, 9600);
  
}

public void draw(){
  background(230);
  
    if (key == 'a') {
    leftButton_click1(leftButton, GEvent.CLICKED);
    
   } else if (key == 'd') {
     rightButton_click1(rightButton, GEvent.CLICKED);
    
   } else if (key == 'w') {
     fwButton_click1(fwButton, GEvent.CLICKED);
    
   } else if (key == 's') {
     bwButton_click1(bwButton, GEvent.CLICKED);
   }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
 
 
}
