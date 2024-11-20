#ifndef color_h
#define color_h

typedef struct {
	float r, g, b;
} Color;

void glColor(Color c);
Color randomColor();


#define NewColor(r, g, b) (Color) { (float)r/255, (float)g/255, (float)g/255 }

// Colors stolen from raylib
// https://github.com/raysan5/raylib/blob/master/src/raylib.h#L173
#define LIGHTGRAY  NewColor(200, 200, 200) 
#define GRAY       NewColor(130, 130, 130) 
#define DARKGRAY   NewColor(80 , 80 , 80 ) 
#define YELLOW     NewColor(253, 249, 0  ) 
#define GOLD       NewColor(255, 203, 0  ) 
#define ORANGE     NewColor(255, 161, 0  ) 
#define PINK       NewColor(255, 109, 194) 
#define RED        NewColor(230, 41 , 55 ) 
#define MAROON     NewColor(190, 33 , 55 ) 
#define GREEN      NewColor(0  , 228, 48 ) 
#define LIME       NewColor(0  , 158, 47 ) 
#define DARKGREEN  NewColor(0  , 117, 44 ) 
#define SKYBLUE    NewColor(102, 191, 255) 
#define BLUE       NewColor(0  , 121, 241) 
#define DARKBLUE   NewColor(0  , 82 , 172) 
#define PURPLE     NewColor(200, 122, 255) 
#define VIOLET     NewColor(135, 60 , 190) 
#define DARKPURPLE NewColor(112, 31 , 126) 
#define BEIGE      NewColor(211, 176, 131) 
#define BROWN      NewColor(127, 106, 79 ) 
#define DARKBROWN  NewColor(76 , 63 , 47 ) 

#define WHITE      NewColor(255, 255, 255)
#define BLACK      NewColor(0  , 0  , 0  )
#define MAGENTA    NewColor(255, 0  , 255)
#define MYWHITE    NewColor(255, 255, 255)

#define glify(c) c.r, c.g, c.b, 1

#ifdef color_impl
#include <GL/gl.h>
#define rng_impl
#include "rng.h"

void glColor(Color c) {
	glColor3f(c.r, c.g, c.b);
}

Color randomColor() {
	return NewColor(randi(0, 256), randi(0, 256), randi(0, 256));
}


#endif // color_impl
#endif // color_h
