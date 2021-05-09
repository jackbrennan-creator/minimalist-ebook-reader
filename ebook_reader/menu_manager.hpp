#pragma once

#include "screen.h"

class menu_manager
{
  public:

    typedef void(*menu_action)();

    menu_manager() 
    {
      initialise();
    }
    
    void set_menu_options(char* options[], int option_count)
    {
      menu_options      = options;
      menu_option_count = option_count;
    }
    
    void set_menu_actions(menu_action actions[], int action_count)
    {
      menu_actions      = actions;
      menu_action_count = action_count;
    }
    
    void virtual show_menu_options(int initial_selection)
    {
    }
    
    bool virtual do_menu_action()
    {
      if (menu_actions == nullptr) return false;
      if      (selection < menu_action_count) menu_actions[selection](); 
      else if (menu_action_count > 0        ) menu_actions[menu_action_count - 1]();
      return true;
    }
    
    void select_previous_option()
    {
      selection = (selection + menu_option_count - 1) % menu_option_count; 
      show_menu_selector();
    }
    
    void select_next_option()
    {
      selection = (selection + 1) % menu_option_count;
      show_menu_selector();
    }
    
    int  get_selection()
    {
      return selection;
    }

  protected:
    
    const int    menu_font_size  =   3;
    const int    options_top     =  90;
    const int    options_left    = 100;
    const int    spacing         =  30;
    const int    selector_radius =  10;
    const int    selector_top    =  90 + 2 * selector_radius;
    const int    selector_left   =  75;
  
    int          menu_option_count;
    char**       menu_options;
    int          menu_action_count;
    menu_action* menu_actions;
    int          selection;

    void initialise()
    {
      menu_options      = nullptr;
      menu_option_count = 0;
      menu_actions      = nullptr;
      menu_action_count = 0;
      selection         = 0;
    }
    
    void set_selection(int new_selection)
    {
      selection = new_selection;
    }
    
    void show_menu_selector()
    {
      display->setFont();
      display->setTextSize(menu_font_size);
      for (int i = 0; i < menu_option_count; i = i + 1)
      {
        display->fillCircle(selector_left - selector_radius, spacing * i + selector_top - selector_radius, selector_radius, (i == selection) ? BLACK : WHITE);
        display->drawCircle(selector_left - selector_radius, spacing * i + selector_top - selector_radius, selector_radius, BLACK                           ); 
      }
      display->partialUpdate();
    }
  
};
