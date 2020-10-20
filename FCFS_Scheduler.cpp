#include "Scheduler.h"

void FCFS_Scheduler::add_process(Process* proc) {
  run_queue.push_back(proc);
}

Process* FCFS_Scheduler::get_next_process() {
  Process* proc = run_queue.front();
  run_queue.pop_front();

  return proc;
}

string FCFS_Scheduler::get_scheduler() {
  return "FCFS";
}