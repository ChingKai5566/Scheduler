#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>

#include "DES_Layer.cpp"
#include "Event.cpp"
#include "Process.cpp"

using namespace std;

/* global variable */
int v_flag = 0;
int e_flag = 0;
char* s_value = nullptr;
int ofs = -1;
int max_prio = 4;
DES_Layer* des_layer;
vector<int> randvals;
vector<Process*> process_list;

/* function */
void check_flag(int argc, char** argv);
void get_process(char* filename);
vector<int> get_randvals(char* filename);
int get_random(int max);

/* program starts from here */
int main(int argc, char* argv[]) {
  // invocation
  check_flag(argc, argv);

    // random number file
  randvals = get_randvals(argv[argc - 1]);

  // initialize
  des_layer = new DES_Layer();

  // readfile and create process
  get_process(argv[argc - 2]);

  if (e_flag == 1) {
    des_layer->show_event_q();
  }
}

void get_process(char* filename) {
  ifstream infile(filename);

  int num = 0;
  int AT, TC, CB, IO;

  while (infile >> AT >> TC >> CB >> IO) {
    /* create process */
    Process* p = new Process(num, AT, TC, CB, IO);
    p->set_prio(get_random(max_prio));

    cout << p->get_pid() << " " << p->get_prio() << " " << endl;
    process_list.push_back(p);

    /* create event */
    Event* e = new Event(p->get_event_time(), p, 1);

    /* add to DES_Layer */
    des_layer->add_event(e);
    num++;
  }
}

int get_random(int max) {
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

void check_flag(int argc, char* argv[]) {
  // check flag
  int index;
  int c;
  opterr = 0;

  while ((c = getopt(argc, argv, "ves:")) != -1)
    switch (c) {
      case 'v':
        v_flag = 1;
        break;
      case 'e':
        e_flag = 1;
        break;
      case 's':
        s_value = optarg;
        break;
      default:
        abort();
    }
}