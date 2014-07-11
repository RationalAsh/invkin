/**
  * Inverse Kinematics
  * This sketch is for visualizing the inverse kinematics
  * algorithm that I'm implementing in python. I think I'll
  * probably use UDP or something to transmit the angles
  * from the python program to the processing sketch.
*/

//Numeric constants
final int right = 39;
final int left  = 37;
final int up    = 38;
final int down  = 40;
final int TRACE = 84;

//flags
int traceFlag = 0;

PVector l1, l2;
float link1      = 300;
float link2      = 200;
float theta1     = 45;
float theta2     = 30;
PVector effector = new PVector(link1+link2,0);
PVector angles   = new PVector(0,0);

void setup()
{
  size(1280, 720);
  strokeWeight(10);
  stroke(255, 160);
}

void draw()
{
  background(0);
  angles = invKin(effector);
  point(effector.x, effector.y);
  //angles = invKin(new PVector(mouseX, height - mouseY));
  //println(str(mouseX) + "," + str(height - mouseY));
  theta1 = angles.x;
  theta2 = angles.y;
  drawArm();  
}

void drawLink(float x_m, float y_m, 
              float segLength, float angle_deg)
{
  //pushMatrix();
  //translate(x_m, 0);
  float x = x_m;
  float y = height - y_m;
  float angle = radians(angle_deg);
  line(x, y, x + segLength*cos(angle),
        y - segLength*sin(angle));
  //translate(x,y);
  //popMatrix();
}

void drawArm()
{
  drawLink(0, 0, link1, theta1);
  drawLink(link1*cos(radians(theta1)), 
            link1*sin(radians(theta1)), 
            link2, theta1 - theta2);
}

void keyPressed()
{
  //println(keyCode);
  switch(keyCode)
  {
    case left:
    effector.x -= 1;
    break;
    
    case right:
    effector.x += 1;
    break;
    
    case up:
    effector.y += 1;
    break;
    
    case down:
    effector.y -= 1;
    break;
    
    case TRACE:
    traceFlag ^= 1;
    if(traceFlag==1) println("Path tracing on! ");
    if(traceFlag!=1) println("Path tracing off.");
    break;
  }
  print("Effector: ");
  println(effector);
  print("Angles: ");
  println(angles);
}

PVector invKin(PVector e)
{
  float r_2   = (e.x * e.x) + (e.y * e.y);
  float l_sq  = link1*link1 + link2*link2;
  float term2 = (r_2 - l_sq)/(2*link1*link2);
  float term1 = -1*sqrt(1 - (term2 * term2));
  
  float th2   = atan2(term1, term2);
  
  float k1    = link1 + link2*cos(th2);
  float k2    = link2*sin(th2);
  float r     = sqrt((k1*k1) + (k2*k2));
  float gamma = atan2(k2,k1);
  
  float th1   = atan2(e.y,e.x) - gamma;
  
  PVector th  = new PVector(abs(degrees(th1)), -1*degrees(th2)); 
  
  return th;
}

