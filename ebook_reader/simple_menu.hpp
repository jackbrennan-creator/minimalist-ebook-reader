#pragma once

#include "screen.h"
#include "menu_manager.hpp"

class simple_menu: public menu_manager
{
  public:

    simple_menu(): menu_manager() { }
    
    void show_menu_options(int initial_selection)
    {
      if (menu_options == nullptr) return;
      display->clearDisplay();
      display->setFont();
      display->setTextSize(menu_font_size);
      for (int i = 0; i < menu_option_count; i = i + 1)
      {
        display->setCursor(options_left, spacing * i + options_top); 
        display->print(menu_options[i]);
      }
      set_selection(initial_selection);
      show_menu_selector();
      redisplay();
    }
  
};
