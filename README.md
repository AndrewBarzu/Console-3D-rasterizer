# Console-3D-rasterizer

This project was created to practice geometry and check whether the formulas from my geometry class were actually working.
Surprise: They do work :)

## Core concept:

The application (or so called engine) runs on the console, printing characters in order to display 3D objects. It's not high definition by any means, as the characters are 
pretty large, but even so, for me it looks beautiful.

The object to be printed is stored as a collection of triangles, and then each triange is drawn by it's composing lines. First, the points of the object are translated into view, 
and then scaled and projected. The program also uses a rotation matrix to rotate the object in place around once per second (not sure because the printing takes a lot of time)
