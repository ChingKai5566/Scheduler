#include <stdio.h>
#include <string>

using namespace std;

typedef enum process_type_t { CREATED, READY, RUNNING, BLOCKED } process_type;

class Process {
 private:
  /* read from file */
  int pid;         // process id
  int cb_max;      // CB
  int ib_max;      // IO
  int start_time;  // AT
  int total_time;  // TC

  /* process instruction */
  int e_last_time;     // last event's time
  int e_next_time;     // next event's time
  int rem;             // remaining time
  process_type state;  // process state
  int prio;
  int cb;
  int ib;

 public:
  /* constructor */
  Process(int, int, int, int, int);

  /* method */
  void init(int, int, int, int, int);
  void set_rem(int);
  int get_rem();
  void set_state(process_type);
  process_type get_state();
  void print();
};