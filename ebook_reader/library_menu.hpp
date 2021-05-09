#pragma once

#include "screen.h"
#include "settings.hpp";
#include "ebook.hpp"
#include "menu_manager.hpp"
#include "error_manager.hpp"
#include "SdFat.h"

class library_menu: public menu_manager
{
  public:
  
    library_menu(error_manager* errors, ebook* book): menu_manager()
    {
      this->errors = errors;
      this->book   = book;
    }

    void show_menu_options(int initial_selection)
    {
      int  books = 0;
      int  yc    = 0;
      char file_name[name_length];
      File library;
    
      if (errors->get_error_state() == error_manager::no_sd_card) display->sdCardInit();
      
      display->setFont();
      display->setTextSize(menu_font_size);
      display->clearDisplay();
      if (library.open(library_folder, O_RDONLY))
      {
        display->setCursor(options_left, options_top - 50);
        display->print("LIBRARY");
          
        display->setCursor(options_left, options_top); 
        display->print("EXIT");
        
        File book_file = library.openNextFile();
        yc             = display->getCursorY();
        while (book_file && yc < display->height() - 2 * font_height(nullptr)) 
        {
          books = books + 1;
          book_file.getName(file_name, name_length);
          
          display->setCursor(options_left, options_top + spacing * books); 
          display->print(file_name);
          
          book_file.close();
          book_file = library.openNextFile();
        }
        library.close();
      }
      else errors->show_error(error_manager::no_library);
      this->set_menu_options(nullptr, books + 1);
      this->set_selection(initial_selection);
      this->show_menu_selector();
      redisplay();
    }
    
    bool do_menu_action()
    {
      int  book_index = 0;
      char file_name[name_length];
      bool found;
      File library;

      if (selection == 0) return false;
      
      display->clearDisplay();
      display->setFont();
      display->setTextSize(menu_font_size);
      display->setCursor(0, 0);
      display->clearDisplay();
      if (library.open(library_folder, O_RDONLY))
      { 
        File book_file = library.openNextFile();
        found          = false;
        while (!found && book_file) 
        {
          book_index = book_index + 1;
          book_file.getName(file_name, name_length);
          book_file.close();
          if (book_index == selection) found = true; else book_file = library.openNextFile();
        }
        library.close();
      }
      else errors->show_error(error_manager::no_library);
      if (found) 
      {
        char book_path[strlen(library_folder) + 1 + strlen(file_name) + 1];
        strcpy(book_path, library_folder);
        strcat(book_path, file_name     );
        book->new_book(book_path, true);
      }
      return found;
    }

  private:
      
    const int        name_length    = 100;
    const char*      library_folder = "/Library/";
    
    error_manager*   errors;
    ebook*           book;
};
