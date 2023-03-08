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
  
}

// Use this method to add additional statements
// to customise the GUI controls
public void customGUI(){
  
  void keyPressed()
{
  if ( key == CODED ) {
    if ( keyCode == A ) {
      leftButton_click1(leftButton.GEvent.click)
      
    } else if ( keyCode == D ) {
      rightButton_click1(rightButton.GEvent.click)
     
    } else if ( keyCode == W ) {
      fwButton_click1(fwButton.GEvent.click)
     
    } else if ( keyCode == S ) {
     bwButton_click1(bwButton.GEvent.click)
    }
  }  
}

void keyReleased()
{
  switch ( key ) {
    case 'r':
      c = color( 255, 0, 0 );
      break;
    case 'g':
      c = color( 0, 255, 0 );
      break;
    case 'b':
      c = color( 0, 0, 255 );
      break;
    case 'c':
      c = color( 0, 255, 255 );
      break;
    case 'm':
      c = color( 255, 0, 255 );
      break;
    case 'y':
      c = color( 255, 255, 0 );
      break;
    default:
      break;
  }
}

}
