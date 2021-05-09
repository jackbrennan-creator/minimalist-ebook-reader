#pragma once

#include "SdFat.h"

class book_file
{
  public:
    
    bool open_file(const char* path)
    {
      if (file.open(path, O_RDONLY))
      {
        init_file();
        return true;
      }
      else return false;
    }
    
    void close_file()
    {
      file.close();
    }
    
    long file_position()
    {
      return file.curPosition();
    }
    
    void set_position(long new_position)
    {
      file.seekSet(new_position); 
    }
    
    char get_ch()
    {
      if (end_of_file()) return '\n';
      char file_buffer[1];
      file.read(file_buffer, 1);
      return file_buffer[0];
    }
    
    bool end_of_file()
    {
      return file_position() >= file_length;
    }

  private:
  
    SdFile file;
    long   file_length = 0;
    
    void init_file()
    {
      file_length = file.fileSize();
    }
    
};
