#include <iostream>
#include <list>
#include "Event.h"

using namespace std;

class DES_Layer {
 public:
  /* constructor */
  DES_Layer();

  /* event queue */
  list<Event*> event_queue;

  /* method */
  void add_event(Event*);
  Event* get_event();
  int get_next_event_time();
  void show_event_q();
  void show_q();
};