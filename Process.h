#ifndef _process_h
#define _process_h

#include <string>
using namespace std;
typedef enum process_type_t { CREATED, READY, RUNNING, BLOCKED, DONE } process_type;

static string show_state(process_type state) {
  switch (state) {
    case CREATED:
      return "CREATED";
      break;
    case READY:
      return "READY";
      break;
    case RUNNING:
      return "RUNNG";
      break;
    case BLOCKED:
      return "BLOCKED";
      break;
    default:
      return "DONE";
      break;
  }
}

class Process {
 private:
  /* read from file */
  int pid;          // process id
  int cb_max;       // CB
  int ib_max;       // IO
  int start_time;   // AT
  int total_time;   // TC

  /* process instruction */
  int event_time;
  int rem;              // remaining time
  process_type state;   // process state
  int prio;
  int cb;
  int ib;

  /* result */
  int finish_time;
  int turnaround_time;
  int io_time;
  int cpu_wait_time;

 public:
  /* constructor */
  Process(int, int, int, int, int);

  /* getter and setter */
  void init(int, int, int, int, int);
  int get_pid();
  void set_pid(int pid);
  int get_cb_max();
  void set_cb_max(int cb);
  int get_ib_max();
  void set_ib_max(int ib);
  int get_start_time();
  void set_start_time(int time);
  int get_total_time();
  void set_total_time(int time);
  int get_event_time();
  void set_event_time(int event_time);
  void set_rem(int);
  int get_rem();
  void set_state(process_type);
  process_type get_state();
  int get_prio();
  void set_prio(int);
  void set_cb(int);
  int get_cb();
  void set_ib(int);
  int get_ib();
  void set_finish_time(int);
  int get_finish_time();
  void set_turnaround_time(int);
  int get_turnaround_time();
  void set_io_time(int);
  int get_io_time();
  void set_cpu_wait_time(int);
  int get_cpu_wait_time();

  /* method */
  void print_process();
};

#endif