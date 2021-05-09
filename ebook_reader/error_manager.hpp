#pragma once
    
#include "screen.h"

class error_manager
{
  public:

    enum error_state {no_error, no_sd_card, no_library, no_book};

    error_manager() 
    {
      current_error = no_error;
    }
    
    error_state get_error_state()
    {
      return current_error;
    }
    
    void set_error_state(error_state error)
    {
      current_error = error;
    }
    
    void show_error(error_state error)
    {
      set_error_state(error);
      show_error_status();
    }
    
    void show_error_status()
    { 
      display->setCursor(100, 100);
      switch (current_error)
      {
        case no_sd_card: display->print("No SD card"       ); break;
        case no_book   : display->print("No book selected" ); break;
        case no_library: display->print("Library not found"); break;
        default        : display->print("Unknown error"    ); break;
      }
      display->setCursor(100, 140);
      display->print("Tap any button to continue...");
    }

  private:
    
    error_state current_error;

};
