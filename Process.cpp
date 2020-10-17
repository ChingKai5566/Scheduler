#include "Process.h"

Process::Process(int pid, int AT, int TC, int CB, int IO) {
  this->pid = pid;
  this->start_time = AT;
  this->total_time = TC;
  this->cb_max = CB;
  this->ib_max = IO;

  /* initialize instruction */
  this->state = CREATED;
  this->e_last_time = this->start_time;
  this->e_next_time = this->start_time;
  this->rem = this->total_time;

}