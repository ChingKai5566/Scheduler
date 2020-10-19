#include "Event.h"
#include "Process.h"

Event::Event(int timestamp, Process* p, int type) {
  /* initialize */
  set_timestamp(timestamp);
  set_process(p);
  set_transition(1);
}

void Event::set_timestamp(int timestamp) {
  this->timestamp = timestamp;
}

int Event::get_timestamp() {
  return timestamp;
}

void Event::set_process(Process* p) {
  process = p;
}

Process* Event::get_process() {
  return process;
}

process_type Event::get_old_state() {
  return old_state;
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

void Event::set_transition(int number) {
  this->transition = number;

  switch (number) {
    case 1:
      set_old_state(CREATED);
      set_new_state(READY);
      break;
    case 2:
      set_old_state(READY);
      set_new_state(RUNNING);
      break;
    case 3:
      set_old_state(RUNNING);
      set_new_state(BLOCKED);
      break;
    case 4:
      set_old_state(BLOCKED);
      set_new_state(READY);
      break;
    case 5:
      set_old_state(RUNNING);
      set_new_state(READY);
      break;
    default:
      break;
  }
}

int Event::get_transition() {
  return this->transition;
}
