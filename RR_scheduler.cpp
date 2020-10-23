#include "Scheduler.h"

RR_Scheduler::RR_Scheduler(int q) {
  this->quantum = q;
}

void RR_Scheduler::add_process(Process* proc) { run_queue.push_back(proc); }

Process* RR_Scheduler::get_next_process() {
  if (run_queue.empty()) {
    return nullptr;
  }
  Process* proc = run_queue.front();
  run_queue.pop_front();

  return proc;
}

string RR_Scheduler::get_scheduler() { return "RR " + to_string(this->quantum); }

void RR_Scheduler::show_run_queue() {
  cout << "SCHED(" << run_queue.size() << "):";

  for (auto p : run_queue) {
    cout << " " << p->get_pid() << ":" << p->get_event_time();
  }

  cout << endl;
}