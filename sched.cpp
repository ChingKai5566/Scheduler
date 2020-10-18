#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <vector>

#include "Event.cpp"
#include "Process.cpp"

using namespace std;

/* global variable */
int v_flag = 0;
char* s_value = NULL;
vector<Process*> process_list;

/* function */
void check_flag(int argc, char** argv);
void get_process(char* filename);

int main(int argc, char* argv[]) {
  // invocation
  check_flag(argc, argv);

  // readfile and create process
  get_process(argv[argc - 2]);
}

void get_process(char* filename) {
  ifstream infile(filename);

  int num = 0;
  int AT, TC, CB, IO;

  while (infile >> AT >> TC >> CB >> IO) {
    Process* p = new Process(num, AT, TC, CB, IO);
    process_list.push_back(p);
    num++;
  }
}

void check_flag(int argc, char* argv[]) {
  // check flag
  int index;
  int c;
  opterr = 0;

  while ((c = getopt(argc, argv, "vs:")) != -1)
    switch (c) {
      case 'v':
        v_flag = 1;
        break;
      case 's':
        s_value = optarg;
        break;
      default:
        abort();
    }
}