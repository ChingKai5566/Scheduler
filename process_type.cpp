#ifndef _process_type_h
#define _process_type_h

#include <string>

using namespace std;

typedef enum process_type_t { CREATED, READY, RUNNING, BLOCKED, DONE } process_type;

string show_state(process_type state) {
  switch (state) {
    case CREATED:
      return "CREATED";
      break;
    case READY:
      return "READY";
      break;
    case RUNNING:
      return "RUNNING";
      break;
    case BLOCKED:
      return "BLOCKED";
      break;
    default:
      return "DONE";
      break;
  }
}

#endif