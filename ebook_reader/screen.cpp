#include "screen.h"

Inkplate* display;

const int max_partial_updates = 10;

int       updates;
int       menu_pad;
int       next_pad;
int       previous_pad;

void init_screen()
{
  display = new Inkplate(INKPLATE_1BIT);
  display->begin();
  set_orientation(portrait);
  display->clearDisplay();
  display->setTextWrap(false);
  display->setTextColor(BLACK, WHITE);
  updates = 0;
}

void set_orientation(orientation new_orientation)
{
  display->setRotation(new_orientation);
  switch (new_orientation)
  {
    case portrait:
    case inverted_landscape:
      menu_pad     = PAD3;
      previous_pad = PAD2;
      next_pad     = PAD1;
      break;
    case landscape:
    case inverted_portrait:
      menu_pad     = PAD1;
      previous_pad = PAD2;
      next_pad     = PAD3;
      break;
  }
}

int font_height(const GFXfont* font)
{
  if (font == nullptr) return 10; else return (int)pgm_read_byte(&font->yAdvance);
}

int string_width(const char* s)
{
  short          x,  y; 
  unsigned short dx, dy;
  display->getTextBounds(s, 0, 0, &x, &y, &dx, &dy);
  return dx;
}

void redisplay()
{
  if (updates >= max_partial_updates) 
    { display->display();       updates = 0;           }
  else 
    { display->partialUpdate(); updates = updates + 1; }
}

button get_button()
{
  if      (display->readTouchpad(next_pad    )) { while (display->readTouchpad(menu_pad    )); return next_button;     }
  else if (display->readTouchpad(previous_pad)) { while (display->readTouchpad(previous_pad)); return previous_button; }
  else if (display->readTouchpad(menu_pad    )) { while (display->readTouchpad(next_pad    )); return menu_button    ; }
  else return no_button;
}

void wait_for_any_button()
{
  button b;
  do 
  {
    reduce_power(1 * seconds);
    b = get_button();
  }
  while (b == no_button);
}

void reduce_power(long interval)
{
  display->einkOff();
    esp_sleep_enable_timer_wakeup(interval);
    esp_light_sleep_start();
  display->einkOn();
}
