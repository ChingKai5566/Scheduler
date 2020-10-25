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
  if (event_queue.empty()) {
    return nullptr;
  }
  Event* cur_event = event_queue.front();
  event_queue.pop_front();
  return cur_event;
}

int DES_Layer::get_next_event_time() {
  Event* next_event = event_queue.front();
  return next_event->get_timestamp();
}

void DES_Layer::remove_event(Event* e) {
  auto it = event_queue.begin();

  for (; it != event_queue.end(); it++) {
    Event* cur_event = *it;

    if (cur_event == e) {
      break;
    }
  }
  event_queue.erase(it);
}

void DES_Layer::show_event_q() {
  cout << "ShowEventQ: ";

  for (auto e : event_queue) {
    cout << e->get_process()->get_event_time() << ":" << e->get_process()->get_pid() << " ";
  }

  cout << endl;
}

void DES_Layer::show_q() {
  for (auto e : event_queue) {
    cout << e->get_timestamp() << ":" << e->get_process()->get_pid() << ":" << e->event_type << " ";
  }
}