#include "Scheduler.h"

void LCFS_Scheduler::add_process(Process* proc) { run_queue.push_back(proc); }

Process* LCFS_Scheduler::get_next_process() {
  if (run_queue.empty()) {
    return nullptr;
  }
  Process* proc = run_queue.back();
  run_queue.pop_back();

  return proc;
}

string LCFS_Scheduler::get_scheduler() { return "LCFS"; }

void LCFS_Scheduler::show_run_queue() {
  cout << "SCHED(" << run_queue.size() << "):";

  for (auto p : run_queue) {
    cout << " " << p->get_pid() << ":" << p->get_event_time();
  }

  cout << endl;
}

bool LCFS_Scheduler::test_preempt() {
  return false;
}