#ifndef _event_h
#define _event_h

#include "Process.h"

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
  
};

#endif