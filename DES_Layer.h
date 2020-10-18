#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include "Event.h"

using namespace std;

class DES_Layer {
 private:
  /* event queue */

 
 public:
  /* constructor */
  DES_Layer();

  /* method */
  void add_event(Event*);
  Event* get_event();
};