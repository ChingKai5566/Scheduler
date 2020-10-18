#ifndef _process_h
#define _process_h

#include "Process_Type.h"

class Process {
 private:
  /* read from file */
  int pid;         // process id
  int cb_max;      // CB
  int ib_max;      // IO
  int start_time;  // AT
  int total_time;  // TC

  /* process instruction */
  int event_time;
  int rem;             // remaining time
  process_type state;  // process state
  int prio;
  int cb;
  int ib;

 public:
  /* constructor */
  Process(int, int, int, int, int);

  /* getter and setter */
  void init(int, int, int, int, int);
  void set_rem(int);
  int get_rem();
  void set_state(process_type);
  process_type get_state();
  int get_prio();
  void set_prio();

  /* method */
  void create_event(int, Process*, process_type);
  void print();
};

#endif