#include "screen.h"
#include "settings.hpp"
#include "error_manager.hpp"
#include "library_menu.hpp"
#include "ebook.hpp"
#include "menu_manager.hpp"
#include "simple_menu.hpp"
#include "FreeSerifBold12pt7b.h"
#include "FreeMonoBold12pt7b.h"

enum display_state {reading_state, main_menu_state, library_state, system_info_state};

display_state   current_state;
ebook_settings* settings;
error_manager*  errors;
menu_manager*   main_menu;
library_menu*   library;
ebook*          book;
char            current_book_path[ebook::max_book_path_length];

void setup()
{
  init_screen();
  settings  = new ebook_settings();
  errors    = new error_manager ();
  main_menu = new simple_menu   ();
  book      = new ebook(settings, errors);
  library   = new library_menu(errors, book);
  show_startup_screen();
  delay(2 * seconds);
  settings->get_current_book(current_book_path, ebook::max_book_path_length);
  current_state = reading_state;
  book->set_font(&FreeSerifBold12pt7b);
  book->new_book(current_book_path, false);
}

void loop()
{
  button b = get_button();
  if (b != no_button) handle_button(b);
  reduce_power(100 * milliseconds);
}

void handle_button(button b)
{
  switch (current_state)
  {
    case reading_state    : handle_reading_button  (b); break;
    case main_menu_state  : handle_main_menu_button(b); break;
    case library_state    : handle_library_button  (b); break;
    case system_info_state: restore_main_menu      ( ); break;
  }
}

void handle_reading_button(button b)
{
  switch (b)
  {
    case menu_button    : show_main_menu     ( );                                break;
    case previous_button: book->previous_page( ); current_state = reading_state; break;
    case next_button    : book->next_page    ( ); current_state = reading_state; break;
  }
}

void handle_main_menu_button(button b)
{
  switch (b)
  {
    case menu_button    : main_menu->do_menu_action        (); break;
    case previous_button: main_menu->select_previous_option(); break;
    case next_button    : main_menu->select_next_option    (); break;
  }
}

void handle_library_button(button b)
{
  switch (b)
  {
    case menu_button    : if (library->do_menu_action()) current_state = reading_state; else restore_main_menu(); break;
    case previous_button: library->select_previous_option();                                                      break;
    case next_button    : library->select_next_option    ();                                                      break;
  }
}

void show_startup_screen()
{
  display->setFont(&FreeSerifBold12pt7b);
  display->setTextSize(2);
  display->setCursor(30, 300); display->print("Minimalist eBook Reader");
  display->setTextSize(1);
  display->setCursor(30, 340); display->print("Initialising...");
  redisplay();
}

void show_main_menu()
{
  show_main_menu(0);
}

void show_main_menu(int selected_option)
{
  char*  options                         [] = {"Exit",    "First Page",      "Furthest Read",        "Library",    "System Information"};
  static simple_menu::menu_action actions[] = {exit_menu, display_first_page, display_furthest_page, show_library, show_system_info    };
  int    action_count                       = sizeof(actions) / sizeof(simple_menu::menu_action);

  main_menu->set_menu_options(options, action_count);
  main_menu->set_menu_actions(actions, action_count);
  
  current_state = main_menu_state;
  main_menu->show_menu_options(selected_option);
}

void restore_main_menu()
{
  show_main_menu(main_menu->get_selection());
}

void exit_menu()
{
  current_state = reading_state;
  book->display_page();
}

void display_first_page()
{
  current_state = reading_state;
  book->first_page();
}

void display_furthest_page()
{
  current_state = reading_state;
  book->furthest_read_page();
}

void show_library()
{
  current_state = library_state;
  library->show_menu_options(0);
}

void show_system_info()
{
  settings->get_current_book(current_book_path, ebook::max_book_path_length);
  char* book_name = strchr(current_book_path + 1, '/');
  if (book_name == nullptr) book_name = "<No Book>"; else book_name = book_name + 1;
  
  const int font_size = 1;
  display->clearDisplay();
  display->setFont(&FreeMonoBold12pt7b);
  display->setTextSize(font_size);
  display->setCursor(0, 0);
  display->println();
  display->println(" System Information");
  display->println(" ------------------");
  display->println();
  display->print(" Current Book: "); display->print(book_name                     ); display->println();
  display->print(" Current Page: "); display->print(book->get_current_page      ()); display->println();
  display->print(" Pages Read  : "); display->print(book->get_furthest_read_page()); display->println();
  display->print(" Battery     : "); display->print(display->readBattery        ()); display->println(" volts");
  display->print(" Temperature : "); display->print(display->readTemperature    ()); display->println("C");
  redisplay();
  current_state = system_info_state;
}
