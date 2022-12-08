

#include <pebble.h>
  
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_verse_layer;
static int s_current_verse;
static int count;

static void update_time() {

  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp;);
  static char buffer[] = "00:00";

  if(clock_is_24h_style() == true) {

    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);

  } 

  else {

    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }


  text_layer_set_text(s_time_layer, buffer);
  count += 1;
  
  if (count >= 5) {
  
  count = 0;
  s_current_verse = rand() %12;
  
  if (s_current_verse == 0) {
    
    text_layer_set_text(s_verse_layer, "John 14:6 I am the way and the truth and the life. No one comes to the father except through me.");
  }
  
  if (s_current_verse == 1) {
    
    text_layer_set_text(s_verse_layer, "Ephesians 2:8 For it is by grace you have been saved.");
  }
  
  if (s_current_verse == 2) {
    
    text_layer_set_text(s_verse_layer, "Psalm 27:1 The Lord is my light and my salvation—whom shall I fear?");
  }
  
  if (s_current_verse == 3) {
    
    text_layer_set_text(s_verse_layer, "2 Corinthians 12:9 My grace is sufficient for you, for my power is made perfect in weakness.");
  }
  
  if (s_current_verse == 4) {
    
    text_layer_set_text(s_verse_layer, "Philippians 4:13 I can do all things through Christ who strengthens me.");
  }
  
  if (s_current_verse == 5) {
    
    text_layer_set_text(s_verse_layer, "Micah 6:8 And what does the Lord require of you? To act justly and to love mercy and to walk humbly with your God.");
  }
  
  if (s_current_verse == 6) {
    
    text_layer_set_text(s_verse_layer, "Proverbs 3:5 Trust in the Lord with all your heart and lean not on your own understanding.");
  }
  
  if (s_current_verse == 7) {
    
    text_layer_set_text(s_verse_layer, "2 Corinthians 5:17 Therefore, if anyone is in Christ he is a new creation; the old has gone, the new has come!");
  }
  
  if (s_current_verse == 8) {
    
    text_layer_set_text(s_verse_layer, "Matthew 11:28-30 Come to me, all you who are weary and burdened, and I will give you rest.");
  }
  
  if (s_current_verse == 9) {
    
    text_layer_set_text(s_verse_layer, "James 4:7 Submit yourselves, then, to God. Resist the devil, and he will flee from you.");
  }
  
  if (s_current_verse == 10) {
    
    text_layer_set_text(s_verse_layer, "1 John 4:7 Dear friends, let us love one another, for love comes from God.");
  }
  
  if (s_current_verse == 11) {
    
    text_layer_set_text(s_verse_layer, "Isaiah 4:26 I the LORD have called thee in righteousness, and will hold thine hand.");
  }
 }
}


static void main_window_load(Window *window) {
   
  s_time_layer = text_layer_create(GRect(0, 25, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");

  s_verse_layer = text_layer_create(GRect(0, 100, 150, 150));
  text_layer_set_background_color(s_verse_layer, GColorClear);
  text_layer_set_text_color(s_verse_layer, GColorBlack);
  text_layer_set_text(s_verse_layer, "John 14:6 I am the way and the truth and the life. No one comes to the father except through me.");
  
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentLeft);
  text_layer_set_text_alignment(s_verse_layer, GTextAlignmentLeft);
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_verse_layer));
                  
  update_time();
}

static void main_window_unload(Window *window) {
  
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_verse_layer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  
  update_time();
}
  
static void init() {
  
  s_main_window = window_create();

  window_set_window_handlers(s_main_window, (WindowHandlers) {
  
    .load = main_window_load,
    .unload = main_window_unload
  });

  window_stack_push(s_main_window, true);
  
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  count = 0;
}

static void deinit() {
  
  window_destroy(s_main_window);
}

int main(void) {

  init();
  app_event_loop();
  deinit();
}

                                
