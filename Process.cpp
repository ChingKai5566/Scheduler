#include "Process.h"

#include <iostream>

Process::Process(int pid, int AT, int TC, int CB, int IO) { init(pid, AT, TC, CB, IO); }

void Process::init(int pid, int AT, int TC, int CB, int IO) {
  this->pid = pid;
  this->start_time = AT;
  this->total_time = TC;
  this->cb_max = CB;
  this->ib_max = IO;
  set_rem(total_time);
  set_event_time(start_time);
  set_state(CREATED);
  set_prio(1);
  set_cb(0);
  set_ib(0);
  set_finish_time(0);
  set_turnaround_time(0);
  set_io_time(0);
  set_cpu_wait_time(0);
}

int Process::get_pid() { return pid; }

void Process::set_pid(int pid) { this->pid = pid; }

int Process::get_cb_max() { return cb_max; }

void Process::set_cb_max(int cb) { this->cb_max = cb; }

int Process::get_ib_max() { return ib_max; }

void Process::set_ib_max(int ib) { this->ib_max = ib; }

int Process::get_start_time() { return start_time; }
void Process::set_start_time(int time) { this->start_time = time; }

int Process::get_total_time() { return total_time; }
void Process::set_total_time(int time) { this->total_time = time; }

int Process::get_event_time() { return this->event_time; }

void Process::set_event_time(int event_time) { this->event_time = event_time; }

void Process::set_rem(int time) { rem = time; }

int Process::get_rem() { return rem; }

void Process::set_state(process_type state) { this->state = state; }

process_type Process::get_state() { return state; }

int Process::get_prio() { return prio; }

void Process::set_prio(int num) {
  this->prio = num;   // need to change to random number
}

int Process::get_cb() { return cb; }

void Process::set_cb(int num) {
  this->cb = num;   // need to change to random number
}

int Process::get_ib() { return ib; }

void Process::set_ib(int num) {
  this->ib = num;   // need to change to random number
}

void Process::set_finish_time(int time) { this->finish_time = time; }

int Process::get_finish_time() { return this->finish_time; }

void Process::set_turnaround_time(int time) { this->turnaround_time = time; }

int Process::get_turnaround_time() { return this->turnaround_time; }

void Process::set_io_time(int time) { this->io_time = time; }

int Process::get_io_time() { return this->io_time; }

void Process::set_cpu_wait_time(int time) { this->cpu_wait_time = time; }

int Process::get_cpu_wait_time() { return this->cpu_wait_time; }

void Process::print_process() {
  cout << "Process " << pid << " time: " << event_time << " rem: " << rem << " state: " << show_state(state) << " prio: " << prio << " cb: " << cb
       << " ib: " << ib << endl;
}