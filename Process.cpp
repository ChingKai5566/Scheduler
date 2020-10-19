#include "Process.h"
#include <iostream>
#include "Event.h"

Process::Process(int pid, int AT, int TC, int CB, int IO) {
  init(pid, AT, TC, CB, IO);

  /* initialize instruction */
  set_rem(total_time);
  set_event_time(start_time);
  set_state(CREATED);
  set_prio(1);
}

void Process::init(int pid, int AT, int TC, int CB, int IO) {
  this->pid = pid;
  this->start_time = AT;
  this->total_time = TC;
  this->cb_max = CB;
  this->ib_max = IO;
}

int Process::get_pid() {
  return pid;
}

void Process::set_pid(int pid) {
  this->pid = pid;
}

void Process::set_rem(int time) {
  rem = time;
}

int Process::get_rem() {
  return rem;
}

void Process::set_state(process_type state) {
  this->state = state;
}

process_type Process::get_state() {
  return state;
}

int Process::get_prio() {
  return prio;
}

void Process::set_prio(int num) {
  this->prio = num;  // need to change to random number
}

int Process::get_event_time() {
  return this->event_time;
}

void Process::set_event_time(int event_time) {
  this->event_time = event_time;
}
