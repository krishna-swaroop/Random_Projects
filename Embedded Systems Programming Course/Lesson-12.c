// Lesson-12
// discusses structures and its applications
// introduces the CMSIS core and corresponding header file that describes all required structures to address
// registers.
#include <stdint.h>

#include "lm4f120h5qr.h"
#include "delay.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

typedef _packed struct {
  uint8_t y;
  uint16_t x; 
} Point;

Point p1,p2;

typedef struct {
  Point top_left;
  Point bottom_right;
} Window;

typedef struct {
  Point corners[3];
} Triangle;

Window w;
Triangle t;

int main() {
  Point *pp;
  Window *wp;
  
  p1.x = sizeof(Point);
  p1.y = 0xAAU;
  
  w.top_left.x = 1U;
  w.bottom_right.y = 2U;
  
  p2 = p1; // direct assignment works. This just copies contents of p1 into p2.
  // This can occupy a lot of memory if not careful. So we use pointers to structures.
  w2 = w1;
  
  pp = &p1;
  wp = &w2;
  
  (*pp).x = 1U;
  (*wp).top_left = *pp;
  
  pp->x = 1U;
  wp->top_left = *pp;
    
  
  t.corners[0].s = 1U;
  
}
