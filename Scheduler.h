#ifndef _scheduler_h
#define _scheduler_h

#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "Process.h"

class Scheduler {
 public:
  virtual void add_process(Process*) = 0;
  virtual Process* get_next_process() = 0;
  virtual string get_scheduler() = 0;
  virtual void show_run_queue() = 0;
  virtual bool test_preempt() = 0;
};

class FCFS_Scheduler : public Scheduler {
 public:
  list<Process*> run_queue;
  void add_process(Process*);
  Process* get_next_process();
  string get_scheduler();
  void show_run_queue();
  bool test_preempt();
};

class LCFS_Scheduler : public Scheduler {
 public:
  list<Process*> run_queue;
  void add_process(Process*);
  Process* get_next_process();
  string get_scheduler();
  void show_run_queue();
  bool test_preempt();
};

class SRTF_Scheduler : public Scheduler {
 public:
  list<Process*> run_queue;
  void add_process(Process*);
  Process* get_next_process();
  string get_scheduler();
  void show_run_queue();
  bool test_preempt();
};

class RR_Scheduler : public Scheduler {
 public:
  int quantum;
  list<Process*> run_queue;
  RR_Scheduler(int);
  void add_process(Process*);
  Process* get_next_process();
  string get_scheduler();
  void show_run_queue();
  bool test_preempt();
};

class PRIO_Scheduler : public Scheduler {
 public:
  int quantum, max_prio;

  vector<list<Process*>>* active_queue;
  vector<list<Process*>>* expired_queue;
  // vector<list<Process*>> q1;
  // vector<list<Process*>> q2;

  PRIO_Scheduler(int, int);
  void add_process(Process*);
  Process* get_next_process();
  string get_scheduler();
  void show_run_queue();
  bool q_isEmpty(vector<list<Process*>>*);
  bool test_preempt();
};

class PREPRIO_Scheduler : public Scheduler {
 public:
  int quantum, max_prio;

  vector<list<Process*>>* active_queue;
  vector<list<Process*>>* expired_queue;
  // vector<list<Process*>> q1;
  // vector<list<Process*>> q2;

  PREPRIO_Scheduler(int, int);
  void add_process(Process*);
  Process* get_next_process();
  string get_scheduler();
  void show_run_queue();
  bool q_isEmpty(vector<list<Process*>>*);
  bool test_preempt();
};

#endif