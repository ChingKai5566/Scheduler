#include "Scheduler.h"

void SRTF_Scheduler::add_process(Process* proc) { 
    int proc_rem = proc->get_rem();
    auto it = run_queue.begin();

    for (; it!= run_queue.end(); it++) {
      Process* cur_proc = *it;

      if (proc_rem < cur_proc->get_rem()) {
        break;
      }
    }

    run_queue.insert(it, proc);
  
  }

Process* SRTF_Scheduler::get_next_process() {
  if (run_queue.empty()) {
    return nullptr;
  }
  Process* proc = run_queue.front();
  run_queue.pop_front();

  return proc;
}

string SRTF_Scheduler::get_scheduler() { return "SRTF"; }

void SRTF_Scheduler::show_run_queue() {
  cout << "SCHED(" << run_queue.size() << "):";

  for (auto p : run_queue) {
    cout << " " << p->get_pid() << ":" << p->get_event_time();
  }

  cout << endl;
}

bool SRTF_Scheduler::test_preempt() {
  return false;
}