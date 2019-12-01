#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

template <typename InfoType> class Observer;

template <typename InfoType> class Subject {
  std::vector<Observer<InfoType>*> observers;
  //InfoType info = 0;
 protected:
  //virtual void setInfo(InfoType newInfo) = 0;
 public:
  void attach(Observer<InfoType> *o);  
  void notifyObservers();
  virtual InfoType getInfo() const = 0;
};

template <typename InfoType>
void Subject<InfoType>::attach(Observer<InfoType> *o) {
  observers.emplace_back(o);
}

template <typename InfoType>
void Subject<InfoType>::notifyObservers() {
  for (auto &ob : observers) ob->notify(*this);
}

// template <typename InfoType>
// void Subject<InfoType>::setInfo(InfoType newInfo) { info = newInfo; }

// template <typename InfoType>
// InfoType Subject<InfoType>::getInfo() const { return info; }

#endif
