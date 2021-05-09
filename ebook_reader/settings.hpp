#pragma once

#include "screen.h"
#include <Preferences.h>

class ebook_settings
{
  public:

    ebook_settings() { initialise(); };
    
    void get_current_book(char* current_book, int max_length)
    {
      preferences.begin("eBook", false);
        preferences.getBytes("current_book", current_book, max_length - 1);
      preferences.end();
    }
    
    void set_current_book(const char* current_book)
    {
      preferences.begin("eBook", false);
        preferences.putBytes("current_book", current_book, strlen(current_book) + 1);
      preferences.end();
    }
    
    void get_book_details(int& current_page, int& pages, long page_index[])
    {
      preferences.begin("eBook", false);
        current_page = preferences.getInt("current_page", 1);
        pages        = preferences.getInt("pages",        0);
        preferences.getBytes("index", page_index, pages * sizeof(long));
      preferences.end();
    }
    
    void set_book_details(int current_page, int pages, long page_index[])
    {
      preferences.begin("eBook", false);
        preferences.putInt("current_page", current_page);
        preferences.putInt("pages",        pages       );
        preferences.putBytes("index", page_index, pages * sizeof(long));
      preferences.end();
    }
    
    int  free_settings_bytes()
    {
      return preferences.freeEntries();
    }

  private:

    const bool allow_clear_settings = true;

    Preferences preferences;
    
    void initialise()
    {
      preferences.begin("eBook", false);
        if (allow_clear_settings && get_button() != no_button)
        {
          preferences.clear();
          display->print("Settings Cleared!");
          redisplay();
          delay(2 * seconds);
        }
      preferences.end();
    }

};
