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
  
    if (key == 'A') {
    leftButton_click1(leftButton.GEvent.click);
    
   } else if (key == 'D') {
     rightButton_click1(rightButton.GEvent.click);
    
   } else if (key == 'W') {
     fwButton_click1(fwButton.GEvent.click);
    
   } else if (key == 'S') {
     bwButton_click1(bwButton.GEvent.click);
   }
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
 
 
}
