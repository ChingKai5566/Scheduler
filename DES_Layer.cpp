#include "DES_Layer.h"

DES_Layer::DES_Layer() {}

void DES_Layer::add_event(Event* e) {
  int new_timestamp = e->get_timestamp();
  auto it = event_queue.begin();

  for (; it != event_queue.end(); it++) {
    Event* cur_event = *it;

    if (new_timestamp < cur_event->get_timestamp()) {
      break;
    }
  }
  event_queue.insert(it, e);
}

Event* DES_Layer::get_event() {
  Event* cur_event = event_queue.front();
  event_queue.erase(event_queue.begin());
  return cur_event;
}

int DES_Layer::get_next_event_time() {
  Event* next_event = event_queue.front();
  return next_event->get_timestamp();
}

void DES_Layer::show_event_q() {
  cout << "ShowEventQ: ";

  for (auto e : event_queue) {
    cout << e->get_process()->get_event_time() << ":"
         << e->get_process()->get_pid() << " ";
  }

  cout << endl;
}
