#include "Process.h"

class Event {
 private:
  /* instruction */
  int timestamp;
  Process* process;
  process_type old_state;
  process_type new_state;

 public:
  /* constructor */
  Event(int, Process*, process_type);

  /* method */
  void set_timestamp(int);
  int get_timestamp();
  void set_process(Process*);
  Process* get_process();
  void set_old_state(process_type);
  process_type get_old_state();
  process_type get_new_state();
  void set_new_state(process_type);
};