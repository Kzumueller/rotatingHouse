# rotatingHouse
a rotating house with keyboard controls, made with blood, sweat and OpenGL

## Dependencies
Any version of GLUT might work, the easiest way to run it on Debian/Ubuntu is to use freeglut3:
```bash
sudo apt-get install freeglut3-dev
```

## Compiling
Run this:
```bash
gcc -std=c11 -o rotatingHouse.out rotatingHouse.c -lglut -lGL -lGLU
```

## Keyboard controls

- WASD for manual rotation
- C to reset orientation
- F to switch between wireframe and filled faces
- T to turn on auto-rotation
