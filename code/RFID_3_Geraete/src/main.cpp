#include "config.h"
#include "setup.h"

void setup() {

    
    setup_lcd();
    setup_serial();
    setup_reader(); 
    
    //setup_led();   
  }

void loop() {

    reader_loop();
}


