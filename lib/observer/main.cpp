#include <iostream>
#include <list>
using namespace std;

class IObserver {
public:
  virtual ~IObserver(){};
  virtual void Update(const string &message_from_subject) = 0;
};

class ISubject {
public:
  virtual ~ISubject(){};
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};

class Subject : public ISubject {
public:
  virtual ~Subject() { cout << "Goodbye, I was the Subject!" << endl; }
  void Attach(IObserver *observer) override {
    list_observer_.push_back(observer);
  }
  void Detach(IObserver *observer) override { list_observer_.remove(observer); }
  void Notify() override {
    std::list<IObserver *>::iterator iterator = list_observer_.begin();
    HowManyObserver();
    while (iterator != list_observer_.end()) {
      (*iterator)->Update(message_);
      ++iterator;
    }
  }
  void CreateMessage(string message = "Empty") {
    this->message_ = message;
    Notify();
  }
  void HowManyObserver() {
    cout << "There are " << list_observer_.size() << " observers" << endl;
  }
  void SomeBusinessLogic() {
    this->message_ = "change message message";
    Notify();
    cout << "doing" << endl;
  }

private:
  list<IObserver *> list_observer_;
  string message_;
};

class Observer : public IObserver {
public:
  Observer(Subject &subject) : subject_(subject) {
    this->subject_.Attach(this);
    cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\"."
         << endl;
    this->number_ = Observer::static_number_;
  }
  virtual ~Observer() {
    cout << "Goodbye, I'm the Observer \"" << this->number_ << "\"." << endl;
  }
  void Update(const string &message_from_subject) override {
    message_from_subject_ = message_from_subject;
    PrintInfo();
  }
  void RemoveMeFromTheList() {
    subject_.Detach(this);
    cout << "Observer " << number_ << " removed" << endl;
  }
  void PrintInfo() {
    cout << "Observer " << this->number_
         << " message: " << this->message_from_subject_ << endl;
  }

private:
  string message_from_subject_;
  Subject &subject_;
  static int static_number_;
  int number_;
};

int Observer::static_number_ = 0;

void ClientCode() {
  Subject *subject = new Subject;
  Observer *observer1 = new Observer(*subject);
  Observer *observer2 = new Observer(*subject);
  Observer *observer3 = new Observer(*subject);
  Observer *observer4;
  Observer *observer5;

  subject->CreateMessage("Hello");
  observer3->RemoveMeFromTheList();

  subject->CreateMessage("HHH");
  observer4 = new Observer(*subject);

  subject->CreateMessage("AAA");
}

int main() { ClientCode(); }