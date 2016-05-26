Real-Time Rendering & 3D Games Programming Assignment 3

student group:
Ke Yi Ren s3405167
William Field s3434180

Assignment1 file: main cpp, Point2f.cpp, Ball.cpp, Readme, Collisions.cpp, Peg.cpp Arena.cpp
What file include collision function: Peg.cpp and Collisions.cpp(C style way)

Makefile folder location - Assignment1/Source/
Run/execution program 's folder  -Assignment1/Bin/

commandline example:
go to Assignment3/Source folder
then
type "make"
open 2nd terminal
go to Assignment1/Bin folder
type ./Assignment3

implementation feature:
-Implement a rectangular arena where the ball collides elastically with walls pegs. 
-The pegs should light up when hit. Note it will not light up during visual debug Mode
-The ball should fall with a constant force towards the bottom, out of the bottom of the arena
Note: no ball catcher
-The trajectory the ball is predicted to follow should be visualised, including collisions. For gameplay this should be limited two deep. 
note: it is not fully polish, and it already killed our time to debug :(
-Use simple plain colours for rendering, including the visualisation. 
-Use brute force collision detection whereby all pegs are checked. 

-Polygonal pegs: rectangles, triangles, pentagons and hexagons. 
Note: no rectangles implement due run out of my time, Althought our code still has rectangle collision function code.......
-Rotation of the pegs
-In the visualisation include highlighting of the edge of the polygonal peg the ball bounces off 
Note: that what visual debug mode cover this
-Handle collisions with corners (vertices) by assuming circular shapes. 
Note: OH GOD! THAT TOOKED US A DAY TO COMPLETE and it is most interest thing we have learn!!


No HD feature implementation :( we wish we have more time and we can implementation!
But we still felt regret for no implementatin HD feature :(

Assignment 3 hotkey for program
c - printconsole with fps only;
d - enable/disband Visual Debug Mode;
v - fire BALLLLLLLLL
left arrow - turning aim to left
right arrow - turning aim to right
esc - exit program


