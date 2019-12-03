#ifndef OBSERVER_H
#define OBSERVER_H
#include "subject.h"

template <typename InfoType> class Subject;

template <typename InfoType> class Observer {
 public:
  virtual void notify(Subject<InfoType> &whoFrom, Action type = Action::BlockChange) = 0; // pass the Subject that called the notify method
  virtual ~Observer() = default;
};
#endif
