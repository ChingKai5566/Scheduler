
typedef enum process_type_t
{
  CREATED,
  READY,
  RUNNING,
  BLOCKED
} process_type;

class Process
{
public:
  /* constructor */
  Process(int pid, int AT, int TC, int CB, int IO);

  /* read from file */
  int pid;        // process id
  int cb_max;     // CB
  int ib_max;     // IO
  int start_time; // AT
  int total_time; // TC

  /* process instruction */
  int e_last_time;    // last event's time
  int e_next_time;    // next event's time
  int rem;            // remaining time
  process_type state; // process state
  const int prio = 4;
};