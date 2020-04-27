void setup() {
   size(400, 400);
   background(100);
}
void draw() {
   stroke(255);    
   line(10, 10, 300, 350);
   
   noFill();
   stroke(0, 255, 0);
   ellipse(300, 300, 100, 30);
   
   fill(random(256), random(256), random(256));
   noStroke();
   ellipse(80, 200, 50, 50);
   
   noFill();
   stroke(0, 0, 255);
   triangle(20, 10, 120, 80, 80, 350);
   
   fill(255, 0, 0, 128);
   stroke(0, 255, 0);
   rect(100, 100, 150, 30);
}
