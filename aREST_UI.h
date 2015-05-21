/* 
  aREST UI for Arduino & the ESP8266
  See the README file for more details.
 
  Written in 2015 by Marco Schwartz under a GPL license. 
  Version 1.0.0
  Changelog:
  
  Version 1.0.0: Initial release with buttons only
*/

#ifndef aRest_ui_h
#define aRest_ui_h

// Include Arduino header
#include "Arduino.h"

// Using ESP8266 ?
#if defined(ESP8266)
#include "stdlib_noniso.h"
#endif

class aREST_UI: public aREST {

public:

aREST_UI() {

}

// Get title
void title(String the_title) {
  ui_title = the_title;
}

// Create button
void button(int pin){

  // Set pin as output
  pinMode(pin,OUTPUT);

  // Set in button array
  buttons[buttons_index] = pin;
  buttons_index++;

}

// void slider(int pin) {

//   // Set pin as output
//   pinMode(pin,OUTPUT);

//   // Set in button array
//   sliders[sliders_index] = pin;
//   sliders_index++;

// }

// Create indicator
// void indicator(char * variable){

//   indicators[0] = variable;

// }

// Handle connection
virtual void root_answer() {
        
    // Answer
    addToBuffer("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    addToBuffer("<html><head>");
    addToBuffer("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    addToBuffer("<script ");
    addToBuffer("src=\"http://code.jquery.com/jquery-2.1.3.min.js\">");
    addToBuffer("</script>");
    //addToBuffer("<script type='text/javascript' src='http://cdn.rawgit.com/Foliotek/AjaxQ/master/ajaxq.js'></script>");
    addToBuffer("<style>.row {margin-top: 30px;} .indicator {font-size: 30px; vertical-align: middle;}</style>");
    addToBuffer("<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">");
    addToBuffer("</head><body>");
    addToBuffer("<div class=\"container\">");

    // Title
    if (ui_title.length() != 0) {
      addToBuffer("<h1>");
      addToBuffer(ui_title);
      addToBuffer("</h1>");
    }
    else {
      addToBuffer("<h1>Interface</h1>");
    }

    // Buttons UI
    for (int i = 0; i < buttons_index; i++) {
      addToBuffer("<div class=\"row\">");
      addToBuffer("<div class=\"col-md-2\"><button class=\"btn btn-block btn-lg btn-primary\" id='btn_on");
      addToBuffer(buttons[i]);
      addToBuffer("'>On</button></div>");
      addToBuffer("<div class=\"col-md-2\"><button class=\"btn btn-block btn-lg btn-danger\" id='btn_off");
      addToBuffer(buttons[i]);
      addToBuffer("'>Off</button></div>");
      addToBuffer("</div>");
    }

    // // Sliders UI
    // for (int i = 0; i < sliders_index; i++) {
    //   addToBuffer("<div class=\"row\">");
    //   addToBuffer("<div class=\"col-md-2\"><input type='range' value='0' max='255' min='0' step='5' id='slider");
    //   addToBuffer(sliders[i]);
    //   addToBuffer("'></div>");
    //   addToBuffer("</div>");
    // }
    
    // addToBuffer("<div class=\"row\">");
    // addToBuffer("<div class='col-md-4 indicator' id='temperature'></div>");
    // addToBuffer("</div>");

    addToBuffer("</div>");

    addToBuffer("<script>$( document ).ready(function() {");

    // Buttons JavaScript
    for (int i = 0; i < buttons_index; i++) {
      addToBuffer("$('#btn_on");
      addToBuffer(buttons[i]);
      addToBuffer("').click(function() {$.get('/digital/");
      addToBuffer(buttons[i]);
      addToBuffer("/1');});");
      addToBuffer("$('#btn_off");
      addToBuffer(buttons[i]);
      addToBuffer("').click(function() {$.get('/digital/");
      addToBuffer(buttons[i]);
      addToBuffer("/0');});");    
    }

    // Sliders JavaScript
    // for (int i = 0; i < sliders_index; i++) {
    //   addToBuffer("$('#slider");
    //   addToBuffer(sliders[i]);
    //   addToBuffer("').mouseup(function() {var val = $('#slider");
    //   addToBuffer(sliders[i]);
    //   addToBuffer("').val(); $.get('/analog/");
    //   addToBuffer(sliders[i]);
    //   addToBuffer("/' + val); });");      
    // }

    // addToBuffer("$.get('/temperature', function(data) { $('#temperature').html('Temperature: ' + data.temperature); });");
    addToBuffer("});</script>");

    addToBuffer("</body></html>\r\n");

}

private:

  // UI title
  String ui_title;

  // Buttons array
  int buttons[10];
  int buttons_index;

  // Buttons array
  int sliders[10];
  int sliders_index;
  
  // Indicators array
  char * indicators[10];

};

#endif