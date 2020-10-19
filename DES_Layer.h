#include <iostream>
#include <list>
#include "Event.h"

using namespace std;

class DES_Layer {
 private:
  /* event queue */
  list<Event*> event_queue;

 public:
  /* constructor */
  DES_Layer();

  /* method */
  void add_event(Event*);
  Event* get_event();
  void show_event_q();
};