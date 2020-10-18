#include "Event.h"
#include "Process.h"

Event::Event(int timestamp, Process* p, process_type state) {
  /* initialize */
  set_timestamp(timestamp);
  set_process(p);
  set_new_state(state);
}

void Event::set_timestamp(int timestamp) {
  this->timestamp = timestamp;
}

int Event::get_timestamp() {
  return this->timestamp;
}

void Event::set_process(Process* p) {
  this->process = p;
}

Process* Event::get_process() {
  return this->process;
}

process_type Event::get_old_state() {
  return this->old_state;
}

void Event::set_old_state(process_type old_state) {
  this->old_state = old_state;
}

process_type Event::get_new_state() {
  return this->new_state;
}
void Event::set_new_state(process_type new_state) {
  this->new_state = new_state;
}