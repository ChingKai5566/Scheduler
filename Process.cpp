#include "Process.h"

Process::Process(int pid, int AT, int TC, int CB, int IO) {
  init(pid, AT, TC, CB, IO);

  /* initialize instruction */
  set_rem(this->total_time);
  set_state(CREATED);
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

void Process::print() {
  printf("Process %d: start time: %d, total_time: %d, cb_max: %d, ib_max: %d\n", pid, start_time, total_time, cb_max, ib_max);
}