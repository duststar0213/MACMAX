import processing.serial.*; // import the serial library
import cc.arduino.*;

String val;
Serial port;
String instruction = "";
PImage castle;
int count = 0;

// import image and port and size
void setup() {
  castle = loadImage("CastleBackgrounds.jpg");
  port = new Serial(this, "/dev/cu.usbmodem1421", 9600);
  size(1450, 1200);
  //frameRate(2);
  startBackground();
}

// display results
void draw() {
  
  //frameRate(0.5);
  textSize(15);
  fill(0);
  while (port.available() > 0) {
    delay(100);
    val = port.readString();
    
    if (count >= 5) {
      println("New Game");
      count = 0;
      startBackground();
    }
    text(val, 100, 300 + count * 25);
    
    count++;
    print(count);
    print(" ");
    println(val);
    
  
  }
}

// display image and instructions

void startBackground() {
  
  // draw castle background
  image(castle, 0, 0);
  castle.resize(1450,1200);
  image(castle, 0, 0);
  // draw instructions
  textSize(30);
  fill(0);
  String ins0 = "Game Rules";
  text(ins0,20,60);
  textSize(15);
  fill(0);
  String ins1 = "Green represents player 1, and red represents player 2.";
  text(ins1,40,100);
  String ins2 = "Both sides have 5 chess pieces.";
  text(ins2,40,120);
  String ins3 = "The button(s) under each piece represent(s) your 'power'.";
  text(ins3,40,140);
  String ins4 = "For each round, you can pick any piece to fight against your oponent.";
  text(ins4,40,160);
  String ins5 = "Every piece can only be used once in this five-round game.";
  text(ins5,40,180);
  String ins6 = "You will not know what 'power' the opponent chooses.";
  text(ins6,40,200);
  String ins7 = "At the end of the fifth round, the player with the more score wins.";
  text(ins7,40,220);
}