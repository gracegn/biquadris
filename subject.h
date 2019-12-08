#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <iostream>

enum class Action { BlockChange, BlockDrop, ClearRow, Blind, RemoveBlind };

template <typename InfoType> class Observer;

template <typename InfoType> class Subject {
  std::vector<Observer<InfoType>*> observers;
 protected:
 public:
  void attach(Observer<InfoType> *o);  
  void notifyObservers(Action type = Action::BlockChange);
  virtual InfoType getInfo() const = 0;
  virtual ~Subject() = default;
};

template <typename InfoType>
void Subject<InfoType>::attach(Observer<InfoType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType>
void Subject<InfoType>::notifyObservers(Action type) {
  for (auto &ob : observers) ob->notify(*this, type);
}

#endif
