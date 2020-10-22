#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "DES_Layer.h"
#include "Scheduler.h"

using namespace std;

int v_flag = 0;
int e_flag = 0;
int t_flag = 0;

/* function */
void check_flag(int argc, char** argv, string& s_value);
void get_process(char* filename, int& max_prio, int& ofs, vector<int>& randvals, list<Process*>& process_list, DES_Layer* des_layer);
vector<int> get_randvals(char* filename);
int get_random(int& max, int& ofs, vector<int>& randvals);
void simulation(Scheduler* scheduler, DES_Layer* des_layer, int& ofs, vector<int>& randvals, int& current_time, int& cpu_time, int& io_time);
Scheduler* getScheduler(string& s_value);
void add_event(Event* new_event, DES_Layer* des_layer);

/* program starts from here */
int main(int argc, char* argv[]) {
  string s_value = " ";
  vector<int> randvals;
  DES_Layer* des_layer;
  Scheduler* scheduler;
  int quantum = INT_MAX;
  int ofs = -1;
  int max_prio = 4;
  list<Process*> process_list;

  // invocation
  check_flag(argc, argv, s_value);

  // random number file
  randvals = get_randvals(argv[argc - 1]);

  // initialize
  des_layer = new DES_Layer();
  scheduler = getScheduler(s_value);

  // readfile and create process
  get_process(argv[argc - 2], max_prio, ofs, randvals, process_list, des_layer);

  if (e_flag == 1) {
    des_layer->show_event_q();
  }

  int current_time, cpu_time, io_time;
  // start simulation
  simulation(scheduler, des_layer, ofs, randvals, current_time, cpu_time, io_time);

  double cpu_util = 0;
  double io_util = 0;
  double avg_turnaround = 0;
  double avg_waittime = 0;
  double throughput = 0;

  // print result
  cout << scheduler->get_scheduler() << endl;

  for (auto p : process_list) {
    p->print_process();
    avg_turnaround += p->get_turnaround_time();
    avg_waittime += p->get_cpu_wait_time();
  }
  avg_turnaround /= process_list.size();
  avg_waittime /= process_list.size();
  cpu_util = (cpu_time * 100 / (double)current_time);
  io_util = (io_time * 100 / (double)current_time);
  throughput = (process_list.size() * 100 / (double)current_time);

  printf("SUM: %d %.2lf %.2lf %.2lf %.2lf %.3lf\n", current_time, cpu_util, io_util, avg_turnaround, avg_waittime, throughput);
}

void simulation(Scheduler* scheduler, DES_Layer* des_layer, int& ofs, vector<int>& randvals, int& current_time, int& cpu_time, int& io_time) {
  current_time = 0;
  cpu_time = 0;
  io_time = 0;
  int io_count = 0, io_start = 0;
  int interval_time = 0;
  bool call_scheduler;
  Process* current_proc = nullptr;
  Event* evt;
  while (!des_layer->event_queue.empty()) {
    evt = des_layer->get_event();

    // event to which process
    Process* proc = evt->get_process();

    // update current time
    current_time = evt->get_timestamp();

    // time interval of this process
    interval_time = current_time - proc->get_event_time();

    // update process event time
    proc->set_event_time(current_time);

    switch (evt->get_transition()) {
      case 1:
        // created -> ready
        if (v_flag) {
          cout << current_time << " " << proc->get_pid() << " " << interval_time << ": " << show_transition(evt->get_transition()) << endl;
        }
        proc->set_state(READY);
        scheduler->add_process(proc);
        call_scheduler = true;
        break;

      case 2:
        // ready -> running

        // count cpu wait time
        {
          int current_cpu_wait_time = proc->get_cpu_wait_time();
          proc->set_cpu_wait_time(current_cpu_wait_time + interval_time);
        }

        // count cb time
        {
          int proc_cb_max = proc->get_cb_max();
          int cb = get_random(proc_cb_max, ofs, randvals);

          // done state
          bool done = false;
          if (cb >= proc->get_rem()) {
            cb = proc->get_rem();
            done = true;
          }

          if (v_flag) {
            cout << current_time << " " << proc->get_pid() << " " << interval_time << ": " << show_transition(evt->get_transition()) << " cb=" << cb
                 << " rem=" << proc->get_rem() << " prio=" << proc->get_d_prio() << endl;
          }

          proc->set_state(RUNNG);

          int next_event_time = current_time + cb;

          if (done) {
            Event* new_event = new Event(next_event_time, proc, 6);
            add_event(new_event, des_layer);
            continue;
          }

          Event* new_event = new Event(next_event_time, proc, 3);
          add_event(new_event, des_layer);
        }
        break;
      case 3:
        // running -> blocked

        // io count
        io_count++;
        if (io_count == 1) {
          io_start = current_time;
        }

        // count rem time: rem - interval_time
        proc->set_rem(proc->get_rem() - interval_time);

        // add cpu use time
        cpu_time += interval_time;

        {
          // count io time
          int proc_ib_max = proc->get_ib_max();
          int ib = get_random(proc_ib_max, ofs, randvals);

          if (v_flag) {
            cout << current_time << " " << proc->get_pid() << " " << interval_time << ": " << show_transition(evt->get_transition()) << " ib=" << ib
                 << " rem=" << proc->get_rem() << endl;
          }

          proc->set_state(BLOCK);

          int next_event_time = current_time + ib;
          Event* new_event = new Event(next_event_time, proc, 4);
          add_event(new_event, des_layer);
        }

        // current process to nullptr
        current_proc = nullptr;
        call_scheduler = true;
        break;
      case 4:
        // blocked -> ready

        // count io
        io_count--;
        if (io_count == 0) {
          io_time += current_time - io_start;
        }

        // reset dynamic prio
        proc->set_d_prio(proc->get_prio() - 1);

        // calculate io time
        proc->set_io_time(proc->get_io_time() + interval_time);

        if (v_flag) {
          cout << current_time << " " << proc->get_pid() << " " << interval_time << ": " << show_transition(evt->get_transition()) << endl;
        }
        proc->set_state(READY);
        scheduler->add_process(proc);
        call_scheduler = true;
        break;
      case 5:
        // running -> ready
        proc->set_state(READY);
        call_scheduler = true;
        break;
      case 6:
        // running -> done

        // add cpu use time
        cpu_time += interval_time;

        if (v_flag) {
          cout << current_time << " " << proc->get_pid() << " " << interval_time << ": " << show_transition(evt->get_transition()) << endl;
        }
        proc->set_state(DONE);
        current_proc = nullptr;
        call_scheduler = true;
        break;
      default:
        break;
    }

    delete evt;

    if (call_scheduler) {
      if (!des_layer->event_queue.empty() && des_layer->get_next_event_time() == current_time) {
        continue;
      }
      call_scheduler = false;

      if (current_proc == nullptr) {
        if (t_flag) {
          scheduler->show_run_queue();
        }
        current_proc = scheduler->get_next_process();
        if (current_proc == nullptr) {
          continue;
        }
        // create event
        Event* new_event = new Event(current_time, current_proc, 2);
        add_event(new_event, des_layer);
      }
    }
  }
}

void add_event(Event* new_event, DES_Layer* des_layer) {
  if (e_flag) {
    cout << " AddEvent(" << new_event->get_timestamp() << ":" << new_event->get_process()->get_pid() << ":" << show_state(new_event->get_new_state())
         << "): ";
    des_layer->show_q();
  }

  // add event into des_layer
  des_layer->add_event(new_event);

  if (e_flag) {
    cout << "==> ";
    des_layer->show_q();
    cout << endl;
  }
}

Scheduler* getScheduler(string& s_value) {
  if (s_value == "F") {
    return new FCFS_Scheduler();
  }

  if (s_value == "L") {
    return new LCFS_Scheduler();
  }

  if (s_value == "S") {
    return new SRTF_Scheduler();
  }

  return nullptr;
}

void get_process(char* filename, int& max_prio, int& ofs, vector<int>& randvals, list<Process*>& process_list, DES_Layer* des_layer) {
  ifstream infile(filename);

  int num = 0;
  int AT, TC, CB, IO;

  while (infile >> AT >> TC >> CB >> IO) {
    /* create process */
    Process* p = new Process(num, AT, TC, CB, IO);
    int cur_prio = get_random(max_prio, ofs, randvals);
    p->set_prio(cur_prio);
    p->set_d_prio(cur_prio - 1);

    process_list.push_back(p);

    /* create event */
    Event* e = new Event(p->get_event_time(), p, 1);

    /* add to DES_Layer */
    des_layer->add_event(e);
    num++;
  }
}

int get_random(int& max, int& ofs, vector<int>& randvals) {
  ofs++;

  if (ofs >= randvals.size()) {
    ofs = 0;
  }

  return 1 + (randvals[ofs] % max);
}

vector<int> get_randvals(char* filename) {
  ifstream infile(filename);
  int num;

  infile >> num;
  vector<int> randvals;

  while (infile >> num) {
    randvals.push_back(num);
  }

  return randvals;
}

void check_flag(int argc, char* argv[], string& s_value) {
  // check flag
  int index;
  int c;
  opterr = 0;

  while ((c = getopt(argc, argv, "vets:")) != -1) switch (c) {
      case 'v':
        v_flag = 1;
        break;
      case 'e':
        e_flag = 1;
        break;
      case 't':
        t_flag = 1;
        break;
      case 's':
        s_value = string(optarg);
        break;
      default:
        abort();
    }
}