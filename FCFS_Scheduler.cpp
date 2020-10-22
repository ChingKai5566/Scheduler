#include "Scheduler.h"

void FCFS_Scheduler::add_process(Process* proc) { run_queue.push_back(proc); }

Process* FCFS_Scheduler::get_next_process() {
  if (run_queue.empty()) {
    return nullptr;
  }
  Process* proc = run_queue.front();
  run_queue.pop_front();

  return proc;
}

string FCFS_Scheduler::get_scheduler() { return "FCFS"; }

void FCFS_Scheduler::show_run_queue() {
  cout << "SCHED(" << run_queue.size() << "):";

  for (auto p : run_queue) {
    cout << " " << p->get_pid() << ":" << p->get_event_time();
  }

  cout << endl;
}
