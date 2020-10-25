#include "Scheduler.h"

PREPRIO_Scheduler::PREPRIO_Scheduler(int q, int m_prio) {
  this->quantum = q;
  this->max_prio = m_prio;
  active_queue = new vector<list<Process*>>(m_prio);
  expired_queue = new vector<list<Process*>>(m_prio);
}

void PREPRIO_Scheduler::add_process(Process* proc) {
  if (proc->get_d_prio() <= 0 && !(proc->get_state() == CREATED || proc->get_state() == BLOCK)) {
    proc->set_d_prio(proc->get_prio() - 1);
    int pos = max_prio - 1 - proc->get_d_prio();
    (*expired_queue)[pos].push_back(proc);
  } else {
    if (!(proc->get_state() == CREATED || proc->get_state() == BLOCK)) {
      proc->set_d_prio(proc->get_d_prio() - 1);
    }
    int pos = max_prio - 1 - proc->get_d_prio();
    (*active_queue)[pos].push_back(proc);
  }
}

Process* PREPRIO_Scheduler::get_next_process() {
  if (!q_isEmpty(active_queue)) {
    for (int i = 0; i < active_queue->size(); i++) {
      if (!(*active_queue)[i].empty()) {
        Process* next_proc = (*active_queue)[i].front();
        (*active_queue)[i].pop_front();
        return next_proc;
      }
    }
  }

  // active_queue is empty, check expired queue
  if (q_isEmpty(expired_queue)) {
    return nullptr;
  }

  // swap
  vector<list<Process*>>* tmp = expired_queue;
  expired_queue = active_queue;
  active_queue = tmp;

  return get_next_process();
}

bool PREPRIO_Scheduler::q_isEmpty(vector<list<Process*>>* q) {
  for (int i = 0; i < q->size(); i++) {
    if (!(*q)[i].empty()) {
      return false;
    }
  }
  return true;
}

string PREPRIO_Scheduler::get_scheduler() { return "PREPRIO " + to_string(this->quantum); }

void PREPRIO_Scheduler::show_run_queue() {
  cout << "{ ";

  vector<list<Process*>>& tmp1 = *active_queue;
  vector<list<Process*>>& tmp2 = *expired_queue;

  for (auto q : tmp1) {
    cout << "[";

    for (auto it = q.begin(); it != q.end(); ++it) {
      if (it != q.begin()) {
        cout << ",";
      }
      Process* proc = *it;
      cout << proc->get_pid();
    }

    cout << "]";
  }

  cout << "} : { ";

  for (auto q : tmp2) {
    cout << "[";

    for (auto it = q.begin(); it != q.end(); ++it) {
      if (it != q.begin()) {
        cout << ",";
      }
      Process* proc = *it;
      cout << proc->get_pid();
    }

    cout << "]";
  }

  cout << "}" << endl;

  if (q_isEmpty(active_queue)) {
    cout << "switched queues" << endl;
  }
}