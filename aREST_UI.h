/* 
  aREST UI for Arduino & the ESP8266
  See the README file for more details.
 
  Written in 2015 by Marco Schwartz under a GPL license. 
  Version 1.0.1
  Changelog:
  
  Version 1.0.1: Initial release with buttons only
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

typedef struct {
  String function_name;
  String description;
} function_button_t;

typedef enum {
  TYPE_BUTTON=0,
  TYPE_FUNCTION_BUTTON,
  TYPE_FUNCTION_WITH_INPUT_BUTTON,
  TYPE_SLIDER,
  TYPE_VARIABLE_LABEL,
  TYPE_LABEL
} ui_type_t;


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

  // Set in the ui_order_list
  ui_order_list[ui_order_index] = TYPE_BUTTON;
  ui_order_index++;
}

// Create function button
void function_button(char *function_name, char *description, int (*f)(String)){

  // Setup function
  aREST::function(function_name, f);

  // Set in function button array
  function_buttons[function_buttons_index].function_name = String(function_name);
  function_buttons[function_buttons_index].description = String(description);
  function_buttons_index++;

  // Set in the ui_order_list
  ui_order_list[ui_order_index] = TYPE_FUNCTION_BUTTON;
  ui_order_index++;
}

// Create function button
void function_with_input_button(char *function_name, char *description, int (*f)(String)){

  // Setup function
  aREST::function(function_name, f);

  // Set in function with input button array
  func_with_input_buttons[func_with_input_buttons_index].function_name = String(function_name);
  func_with_input_buttons[func_with_input_buttons_index].description = String(description);
  func_with_input_buttons_index++;

  // Set in the ui_order_list
  ui_order_list[ui_order_index] = TYPE_FUNCTION_WITH_INPUT_BUTTON;
  ui_order_index++;
}

void slider(int pin) {

  // Set pin as output
  pinMode(pin,OUTPUT);

  // Set in button array
  sliders[sliders_index] = pin;
  sliders_index++;

  // Set in the ui_order_list
  ui_order_list[ui_order_index] = TYPE_SLIDER;
  ui_order_index++;
}

void variable_label(char *variable_name, char *label_text, int *var){

  // Initialize var
  aREST::variable(variable_name, var);
  variable_label_add(variable_name, label_text);
}

// Float variables (Mega & ESP only, or without CC3000)
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ESP8266) || defined(CORE_WILDFIRE) || !defined(ADAFRUIT_CC3000_H)
void variable_label(char *variable_name, char *label_text, float *var){

  // Initialize variable
  aREST::variable(variable_name, var);
  variable_label_add(variable_name, label_text);
}
#endif

// String variables (Mega & ESP only, or without CC3000)
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(ESP8266) || defined(CORE_WILDFIRE) || !defined(ADAFRUIT_CC3000_H)
void variable_label(char *variable_name, char *label_text, String *var){

  // Initialize var
  aREST::variable(variable_name, var);
  variable_label_add(variable_name, label_text);
}
#endif

// Create variable label
void variable_label_add(char *variable_name, char *label_text){

  var_labels_names[var_labels_index] = variable_name;
  var_labels_text[var_labels_index] = label_text;
  var_labels_index++;

  // Set in the ui_order_list
  ui_order_list[ui_order_index] = TYPE_VARIABLE_LABEL;
  ui_order_index++;
}

// Create label
void label(char *label_text, bool small_text=false){

  labels_text[labels_index] = label_text;
  labels_text_should_be_small[labels_index] = small_text;
  labels_index++;

  // Set in the ui_order_list
  ui_order_list[ui_order_index] = TYPE_LABEL;
  ui_order_index++;
}

void add_next_button() {
  addToBuffer("<div class=\"row\">");
  addToBuffer("<div class=\"col-md-2\"><button class=\"btn btn-block btn-lg btn-primary\" id='btn_on");
  addToBuffer(buttons[current_buttons_index]);
  addToBuffer("'>On</button></div>");
  addToBuffer("<div class=\"col-md-2\"><button class=\"btn btn-block btn-lg btn-danger\" id='btn_off");
  addToBuffer(buttons[current_buttons_index]);
  addToBuffer("'>Off</button></div>");
  addToBuffer("</div>");
  current_buttons_index++;
}

void add_next_function_button() {
  addToBuffer("<div class=\"row\">");
  addToBuffer("<div class=\"col-md-2\"><button class=\"btn btn-block btn-lg btn-primary\" id='func_btn");
  addToBuffer(current_function_buttons_index);
  addToBuffer("'>");
  addToBuffer(function_buttons[current_function_buttons_index].description);
  addToBuffer("</button></div>");
  addToBuffer("</div>");
  current_function_buttons_index++;
}

void add_next_function_with_input_button() {
  addToBuffer("<div class=\"row\">");
  addToBuffer("<div class=\"col-md-2\"><input type='text' id='func_with_input_text");
  addToBuffer(current_func_with_input_buttons_index);
  addToBuffer("'/></div>");
  addToBuffer("<div class=\"col-md-2\"><button class=\"btn btn-block btn-lg btn-primary\" id='func_with_input_btn");
  addToBuffer(current_func_with_input_buttons_index);
  addToBuffer("'>");
  addToBuffer(func_with_input_buttons[current_func_with_input_buttons_index].description);
  addToBuffer("</button></div>");
  addToBuffer("</div>");
  current_func_with_input_buttons_index++;
}

void add_next_slider() {
  addToBuffer("<div class=\"row\">");
#if defined(ESP8266)
  addToBuffer("<div class=\"col-md-2\"><input type='range' value='0' max='1023' min='0' step='5' id='slider");
#else
  addToBuffer("<div class=\"col-md-2\"><input type='range' value='0' max='255' min='0' step='5' id='slider");
#endif
  addToBuffer(sliders[current_sliders_index]);
  addToBuffer("'></div>");
  addToBuffer("</div>");
  current_sliders_index++;
}

void add_next_variable_label() {
  addToBuffer("<div class=\"row\">");
  addToBuffer("<div class='col-md-4 indicator'>");
  addToBuffer(var_labels_text[current_var_labels_index]);
  addToBuffer(": </div>");
  addToBuffer("<div class='col-md-4 indicator' id='");
  addToBuffer(var_labels_names[current_var_labels_index]);
  addToBuffer("'></div>");
  addToBuffer("</div>");
  current_var_labels_index++;
}

void add_next_label() {
  addToBuffer("<div class=\"row\">");
  if (labels_text_should_be_small[current_labels_index])
  {
      addToBuffer("<div class='col-md-10 smalltext'>");
  }
  else
  {
      addToBuffer("<div class='col-md-10 indicator'>");
  }
  addToBuffer(labels_text[current_labels_index]);
  addToBuffer("</div>");
  addToBuffer("</div>");
  current_labels_index++;
}

void reset_current_indices() {
  current_buttons_index = 0;
  current_function_buttons_index = 0;
  current_func_with_input_buttons_index = 0;
  current_sliders_index = 0;
  current_var_labels_index = 0;
  current_labels_index = 0;
}

// Handle connection
virtual void root_answer() {
        
    // Answer
    addToBuffer("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
    addToBuffer("<html><head>");
    addToBuffer("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
    addToBuffer("<script ");
    addToBuffer("src=\"http://code.jquery.com/jquery-2.1.3.min.js\">");
    addToBuffer("</script>");
    addToBuffer("<script type='text/javascript' src='http://cdn.rawgit.com/Foliotek/AjaxQ/master/ajaxq.js'></script>");
    addToBuffer("<style>.row {margin-top: 30px;} .indicator {font-size: 30px; vertical-align: middle;} .smalltext {font-size: 15px; vertical-align: middle;}</style>");
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

    reset_current_indices();
    // Add all UI elements in order they were added
    for (int i = 0; i < ui_order_index; i++) {
      switch (ui_order_list[i]) {
	case TYPE_BUTTON:
	  add_next_button();
	  break;
	case TYPE_FUNCTION_BUTTON:
	  add_next_function_button();
	  break;
	case TYPE_FUNCTION_WITH_INPUT_BUTTON:
	  add_next_function_with_input_button();
	  break;
	case TYPE_SLIDER:
	  add_next_slider();
	  break;
	case TYPE_VARIABLE_LABEL:
	  add_next_variable_label();
	  break;
	case TYPE_LABEL:
	  add_next_label();
	  break;
      }
    }

    addToBuffer("</div>");

    addToBuffer("<script>$( document ).ready(function() {");

    // Buttons JavaScript
    for (int i = 0; i < buttons_index; i++) {
      addToBuffer("$('#btn_on");
      addToBuffer(buttons[i]);
      addToBuffer("').click(function() {$.getq('queue','/digital/");
      addToBuffer(buttons[i]);
      addToBuffer("/1');});");
      addToBuffer("$('#btn_off");
      addToBuffer(buttons[i]);
      addToBuffer("').click(function() {$.getq('queue','/digital/");
      addToBuffer(buttons[i]);
      addToBuffer("/0');});");    
    }

    // Function Buttons JavaScript
    for (int i = 0; i < function_buttons_index; i++) {
      addToBuffer("$('#func_btn");
      addToBuffer(i);
      addToBuffer("').click(function() {$.getq('queue','/");
      addToBuffer(function_buttons[i].function_name);
      addToBuffer("');});");
    }

    // Function With Input Buttons JavaScript
    for (int i = 0; i < func_with_input_buttons_index; i++) {
      addToBuffer("$('#func_with_input_btn");
      addToBuffer(i);
      addToBuffer("').click(function() {var text = document.getElementById(\"func_with_input_text");
      addToBuffer(i);
      addToBuffer("\").value; $.getq('queue','/");
      addToBuffer(func_with_input_buttons[i].function_name);
      addToBuffer("?params=' + text); });");
    }

    // Sliders JavaScript
    for (int i = 0; i < sliders_index; i++) {
      addToBuffer("$('#slider");
      addToBuffer(sliders[i]);
      addToBuffer("').mouseup(function() {var val = $('#slider");
      addToBuffer(sliders[i]);
      addToBuffer("').val(); $.getq('queue','/analog/");
      addToBuffer(sliders[i]);
      addToBuffer("/' + val); });");      
    }

    // Variable Labels JavaScript
    for (int j = 0; j < var_labels_index; j++) {
      addToBuffer("$.getq('queue','/");
      addToBuffer(var_labels_names[j]);
      addToBuffer("', function(data) { $('#");
      addToBuffer(var_labels_names[j]);
      addToBuffer("').html(data.");
      addToBuffer(var_labels_names[j]);
      addToBuffer("); });"); 
    }

    addToBuffer("});</script>");

    addToBuffer("</body></html>\r\n");

}

private:

  // UI title
  String ui_title;

  // Buttons array
  int buttons[10];
  int buttons_index;
  int current_buttons_index;

  // Function Buttons array
  function_button_t function_buttons[10];
  int function_buttons_index;
  int current_function_buttons_index;

  // Function With Input Buttons array
  function_button_t func_with_input_buttons[10];
  int func_with_input_buttons_index;
  int current_func_with_input_buttons_index;

  // Buttons array
  int sliders[10];
  int sliders_index;
  int current_sliders_index;
  
  // Variable Labels array
  uint8_t var_labels_index;
  uint8_t current_var_labels_index;
  char * var_labels_names[10];
  char * var_labels_text[10];
  
  // Labels array
  uint8_t labels_index;
  uint8_t current_labels_index;
  char * labels_text[10];
  bool labels_text_should_be_small[10];

  ui_type_t ui_order_list[30];
  int ui_order_index;
};

#endif
