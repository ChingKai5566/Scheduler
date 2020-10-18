#include "DES_Layer.h"

DES_Layer::DES_Layer() {}

void DES_Layer::add_event(Event* e) {
  this->event_queue.push(e);
}

Event* DES_Layer::get_event() {
  Event* e = this->event_queue.top();
  this->event_queue.pop();
  return e;
}