#ifndef _event_h
#define _event_h

#include "Process.h"

static string show_transition(int type) {
  switch (type) {
    case 1:
      return "CREATED -> READY";
      break;
    case 2:
      return "READY -> RUNNG";
      break;
    case 3:
      return "RUNNG -> BLOCK";
      break;
    case 4:
      return "BLOCK -> READY";
      break;
    case 5:
      return "RUNNG -> READY";
      break;
    case 6:
      return "Done";
      break;
  }
  return "";
}

class Event {
 private:
  /* instruction */
  int timestamp;
  int transition;
  Process* process;
  process_type old_state;
  process_type new_state;

 public:
  /* constructor */
  Event(int, Process*, int);

  string event_type;

  /* setter and getter */
  void set_timestamp(int);
  int get_timestamp();
  void set_process(Process*);
  Process* get_process();
  void set_old_state(process_type);
  process_type get_old_state();
  process_type get_new_state();
  void set_new_state(process_type);
  void set_transition(int);
  int get_transition();

  /* method */
  void print_event();
};

#endif