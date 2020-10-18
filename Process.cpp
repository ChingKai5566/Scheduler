#include "Process.h"
#include <iostream>
#include "Event.h"

Process::Process(int pid, int AT, int TC, int CB, int IO) {
  init(pid, AT, TC, CB, IO);

  /* initialize instruction */
  set_rem(this->total_time);
  set_state(CREATED);
  set_prio();

  /* add event*/
  create_event(this->start_time, this, CREATED);
}

void Process::init(int pid, int AT, int TC, int CB, int IO) {
  this->pid = pid;
  this->start_time = AT;
  this->total_time = TC;
  this->cb_max = CB;
  this->ib_max = IO;
}

void Process::set_rem(int time) {
  this->rem = time;
}

int Process::get_rem() {
  return this->rem;
}

void Process::set_state(process_type state) {
  this->state = state;
}

process_type Process::get_state() {
  return this->state;
}

int Process::get_prio() {
  return this->prio;
}

void Process::set_prio() {
  this->prio = 1;  // need to change to random number
}

void Process::create_event(int time, Process* p, process_type state) {
  Event* e = new Event(time, this, this->state);
  e->get_process()->print();
}

void Process::print() {
  cout << this->pid << " " << this->start_time << " " << show_state(this->get_state()) << endl;
}