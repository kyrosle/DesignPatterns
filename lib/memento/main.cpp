#include <bits/types/time_t.h>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

deque<int> deq;

class Memento {
public:
  virtual ~Memento() {}
  virtual string GetName() const = 0;
  virtual string data() const = 0;
  virtual string state() const = 0;
};

class ConcreteMemento : public Memento {
private:
  string state_;
  string data_;

public:
  ConcreteMemento(string state) : state_(state) {
    this->state_ = state;
    time_t now = time(0);
    this->data_ = ctime(&now);
  }
  string state() const override { return this->state_; }
  string GetName() const override {
    return this->data_ + "/ (" + this->state_.substr(0, 9) + "...)";
  }
  string data() const override { return this->data_; }
};

class Originator {
private:
  string state_;
  string GenerateRandomString(int length = 10) {
    const char alphanum[] = "0123456789"
                            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                            "abcdefghijklmnopqrstuvwxyz";
    int stringLength = sizeof(alphanum) - 1;

    string random_string;
    for (int i = 0; i < length; i++) {
      random_string += alphanum[std::rand() % stringLength];
    }
    return random_string;
  }

public:
  Originator(string state) : state_(state) {
    cout << "Originator: My initial state is: " << this->state_ << endl;
  }
  void DoSomething() {
    cout << "Originator: I'm doing something important." << endl;
    this->state_ = this->GenerateRandomString(30);
    cout << "Originator: and my state has changed to: " << this->state_ << endl;
  }
  Memento *Save() { return new ConcreteMemento(this->state_); }
  void Restore(Memento *memento) {
    this->state_ = memento->state();
    cout << "Originator: My state has changed to: " << this->state_ << endl;
  }
};

class Caretaker {
private:
  vector<Memento *> mementos_;
  Originator *originator_;

public:
  Caretaker(Originator *originator) : originator_(originator) {}
  void Backup() {
    cout << "Caretaker: Saving Originator's state...\n";
    this->mementos_.push_back(this->originator_->Save());
  }
  void Undo() {
    if (!this->mementos_.size()) {
      return;
    }
    Memento *memento = this->mementos_.back();
    this->mementos_.pop_back();
    cout << "Caretaker: Restoring state to: " << memento->GetName() << endl;
    try {
      this->originator_->Restore(memento);
    } catch (...) {
      this->Undo();
    }
  }
  void ShowHistory() const {
    cout << "Caretaker: Here's the list of mementos:" << endl;
    for (Memento *memento : this->mementos_) {
      cout << memento->GetName() << endl;
    }
  }
};

void ClientCode() {
  Originator *originator = new Originator("Super-duper-super-puper-super");
  Caretaker *caretaker = new Caretaker(originator);
  caretaker->Backup();
  originator->DoSomething();
  caretaker->Backup();
  originator->DoSomething();
  caretaker->Backup();
  originator->DoSomething();
  cout << endl;
  caretaker->ShowHistory();
  cout << endl;
  caretaker->Undo();
  cout << endl;
  caretaker->Undo();

  delete originator;
  delete caretaker;
}

int main() {
  std::srand(static_cast<unsigned int>(std::time(NULL)));
  ClientCode();
}