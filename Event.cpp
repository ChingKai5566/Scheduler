#include "Event.h"

#include <iostream>

Event::Event(int timestamp, Process* p, int type) {
  /* initialize */
  set_timestamp(timestamp);
  set_process(p);
  set_transition(type);
}

void Event::set_timestamp(int timestamp) { this->timestamp = timestamp; }

int Event::get_timestamp() { return timestamp; }

void Event::set_process(Process* p) { process = p; }

Process* Event::get_process() { return process; }

process_type Event::get_old_state() { return old_state; }

void Event::set_old_state(process_type old_state) { this->old_state = old_state; }

process_type Event::get_new_state() { return this->new_state; }

void Event::set_new_state(process_type new_state) { this->new_state = new_state; }

void Event::set_transition(int number) {
  this->transition = number;

  switch (number) {
    case 1:
      set_old_state(CREATED);
      set_new_state(READY);
      event_type = "READY";
      break;
    case 2:
      set_old_state(READY);
      set_new_state(RUNNG);
      event_type = "RUNNG";
      break;
    case 3:
      set_old_state(RUNNG);
      set_new_state(BLOCK);
      event_type = "BLOCK";
      break;
    case 4:
      set_old_state(BLOCK);
      set_new_state(READY);
      event_type = "READY";
      break;
    case 5:
      set_old_state(RUNNG);
      set_new_state(READY);
      event_type = "PREEMPT";
      break;
    case 6:
      set_old_state(RUNNG);
      set_new_state(BLOCK);
      event_type = "Done";
    default:
      break;
  }
}

int Event::get_transition() { return this->transition; }

void Event::print_event() {
  cout << "Event: ProcessID is " << process->get_pid() << " time: " << timestamp << " transition type: " << transition
       << " state: " << show_state(old_state) << " => " << show_state(new_state) << endl;
}
