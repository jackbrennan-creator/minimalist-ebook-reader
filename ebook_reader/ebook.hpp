#pragma once

#include "settings.hpp"
#include "screen.h"
#include "book_file.hpp"
#include "error_manager.hpp"

class ebook
{
  public:

    static const int max_book_path_length = 256;

    ebook(ebook_settings* settings, error_manager* errors)
    {
      file          = new book_file();
      font          = nullptr;
      book_settings = settings;
      this->errors  = errors;
    }
    
    void set_font(const GFXfont* book_font)
    {
      font = (GFXfont*)book_font;
    }
    
    void new_book(const char* path, bool from_begining)
    {
      file->close_file();
      book_settings->set_current_book(path);
      display->clearDisplay();
      display->setCursor(0, 0);
      open_book(path);
      if (!from_begining) 
      {
        book_settings->get_book_details(current_page, pages, page_index);
        file->set_position(page_index[current_page - 1]); 
      }
      display_book(font);
      redisplay();
    }
    
    void display_page()
    {
      display->clearDisplay();
      display->setCursor(0, 0);
      file->set_position(page_index[current_page - 1]); 
      display_book(font);
      redisplay();
    }
    
    void first_page()
    {
      current_page = 1;
      display_page();
    }
    
    void furthest_read_page()
    {
      current_page = pages;
      display_page();
    }
    
    void next_page()
    {
      if (current_page < last_page && current_page < max_page)
      {
        display->clearDisplay();
        display->setCursor(0, 0);
        set_next_page();
        display_book(font);
        redisplay();
      }
    }
    
    void previous_page()
    {
      if (current_page > 1)
      {
        display->clearDisplay();
        display->setCursor(0, 0);
        set_previous_page();
        file->set_position(page_index[current_page - 1]); 
        display_book(font);
        redisplay();
      }
    }
    
    int get_current_page()
    {
      return current_page;
    }
    
    int get_furthest_read_page()
    {
      return pages;
    }

  private:

    static const int max_page  = 512;
  
    int              pages;
    long             page_index[max_page];
    int              current_page;
    int              last_page;
    bool             end_of_line;
    bool             end_of_paragraph;
    bool             last_word;
    GFXfont*         font;
    book_file*       file;
    ebook_settings*  book_settings;
    error_manager*   errors;
    
    static const int max_chars = 200;
    char             line[max_chars + 1];
    int              line_pt;
    int              line_length;
    int              line_width;
    int              line_height;
    
    static const int max_word_chars = max_chars;
    char             word_chars[max_word_chars + 1];
    int              word_length;
    int              word_width;
    int              space_width;
    int              page_width;
    
    static const int max_words = max_chars / 2 + 1;
    int              word_index[max_words];
    int              index_pt;
    
    void open_book(const char* path)
    {
      if (display->sdCardInit())
        if (file->open_file(path))
        {
          init_book();
          errors->set_error_state(error_manager::no_error);
        }
        else errors->set_error_state(error_manager::no_book);
      else errors->set_error_state(error_manager::no_sd_card);
    }
    
    void init_book()
    {
      pages        = 0;
      current_page = 1;
      last_page    = max_page;
    }
    
    void display_book(const GFXfont* font)
    {
      display->setTextSize(1);
      display->setFont(font);
      display->setCursor(0, 0);
      if (errors->get_error_state() == error_manager::no_error)
      {
        line_height = font_height(font);
        if (current_page > pages)
        {
          pages                 = pages + 1;
          page_index[pages - 1] = file->file_position();
        }
        display_current_page();
        book_settings->set_book_details(current_page, pages, page_index);
      }
      else errors->show_error_status();
    }
    
    void set_previous_page()
    {
      if (current_page > 1) current_page = current_page - 1;
    }
    
    void set_next_page()
    {
      if (current_page < last_page && current_page < max_page) current_page = current_page + 1;
    }
    
    void display_current_page()
    {
      set_space_width();
      int margins      = 2 * space_width + 15;
      page_width       = display->width() - margins;
      word_length      = 0;
      word_width       = 0; 
      end_of_paragraph = false;
      
      while (!file->end_of_file() && !bottom_of_page())
      {
        get_line();
        display_line(margins / 2);
        if (end_of_paragraph && word_length == 0) 
        {
          display->println();
          end_of_paragraph = false;
        }
      }
      display->setCursor(display->width() / 2, display->height() - line_height / 2); 
      display->print(current_page);
      if (file->end_of_file() && last_page == max_page) last_page = current_page;
    }

    bool bottom_of_page()
    {
      return display->getCursorY() > display->height() - 2 * line_height;
    }
    
    void display_line(int left_margin)
    {
       if (line_length == 0) 
       {
         end_of_paragraph = false;
         return; 
       }
      display->println();
      int xc = left_margin;
      int yc = display->getCursorY();
      int padding = space_width + (end_of_paragraph ? 0 : (page_width - line_width) / (index_pt - 1));
      for (int index = 0; index < index_pt; index = index + 1)
      {
        if (index > 0) xc = xc + padding;
        display->setCursor(xc, yc);
        display_word(index);
        xc = display->getCursorX();
      }
    }
    
    void display_word(int index)
    {
      int start  = word_index[index];
      int finish = (index < index_pt - 1) ? word_index[index + 1] - 1 : line_pt - 1; 
      for (int pt = start; pt <= finish; pt = pt + 1) 
        display->print(line[pt]);
    }
    
    void get_line()
    {
      line_pt     = 0;
      line_length = 0;
      line_width  = 0;
      index_pt    = 0;
      end_of_line = false;
      if (file->end_of_file()) put_line_ch(0);
      else
      {
        while (!end_of_line && !file->end_of_file() && line_pt < max_chars)
        {
          int  word_start = get_word();
          bool overflow   = (line_width + space_width + word_width > page_width);
          if (overflow) 
          {
            file->set_position(word_start);
            word_length = 0;
            end_of_line = true;
          } 
          else put_word();
        }
        put_line_ch(0);
      }
    }
    
    int get_word()
    {
      bool eow        = false;
      int  word_start = file->file_position();
      char ch         = skip_layout();
      last_word       = false;
      while (!eow && !end_of_line)
      {
        switch (ch)
        {
          case '\n'           : last_word = true; end_of_line = true;                                                     break;
          case ' ' : case '\t': eow = true;                                                                               break;
          default             : put_word_ch(ch); if (word_length >= max_word_chars) eow = true; else ch = file->get_ch(); break;
        }
        if (file->end_of_file()) break;
      }
      word_chars[word_length] = 0;
      word_width = string_width(word_chars);
      if (file->end_of_file()) last_word = true;
      return word_start;
    }
    
    char skip_layout()
    {
      char ch = file->get_ch();
      while (!file->end_of_file() && (ch == ' ' || ch == '\t')) ch = file->get_ch();
      return ch;
    }
    
    void put_word_ch(char ch)
    {
      word_chars[word_length] = ch;
      word_length             = word_length + 1;
    }
    
    void put_word()
    {
      word_index[index_pt] = line_pt;
      index_pt             = index_pt + 1;
      if (line_length > 0) 
      {
        line_length = line_length + 1;
        line_width  = line_width  + space_width;
      }
      for (int i = 0; i < word_length; i = i + 1) put_line_ch(word_chars[i]);
      line_length      = line_length + word_length;
      line_width       = line_width  + word_width;
      word_length      = 0;
      word_width       = 0;
      end_of_paragraph = last_word;
    }
    
    void put_line_ch(char ch)
    {
      line[line_pt] = ch;
      line_pt       = line_pt + 1;
    }
    
    void set_space_width()
    {
      short          x,  y; 
      unsigned short dx, dy;
      display->getTextBounds("a", 0, 0, &x, &y, &dx, &dy);
      space_width = dx;
    }

};
