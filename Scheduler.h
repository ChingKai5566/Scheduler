#ifndef _scheduler_h
#define _scheduler_h

#include <iostream>
#include <list>
#include <string>

#include "Process.h"

class Scheduler {
 public:
  list<Process*> run_queue;
  virtual void add_process(Process*) = 0;
  virtual Process* get_next_process() = 0;
  virtual string get_scheduler() = 0;
  virtual void show_run_queue() = 0;
};

class FCFS_Scheduler : public Scheduler {
 public:
  list<Process*> run_queue;
  void add_process(Process*);
  Process* get_next_process();
  string get_scheduler();
  void show_run_queue();
};

#endif