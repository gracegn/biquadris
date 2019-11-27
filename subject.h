#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"

template <typename InfoType> class Observer;

template <typename InfoType> class Subject {
  std::vector<Observer<InfoType>*> observers;
  virtual InfoType info = 0; //made it virtual to silence errors, idk if this was the right thing to do
 protected:
  void setInfo(InfoType newInfo);
 public:
  void attach(Observer<InfoType> *o);  
  void notifyObservers();
  InfoType getInfo() const;
};

template <typename InfoType>
void Subject<InfoType>::attach(Observer<InfoType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType>
void Subject<InfoType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

template <typename InfoType>
void Subject<InfoType>::setInfo(InfoType newInfo) { info = newInfo; }

template <typename InfoType>
InfoType Subject<InfoType>::getInfo() const { return info; }
#endif
