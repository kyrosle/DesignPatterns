#include <cstddef>
#include <iostream>
using namespace std;
class Context;

class State {
protected:
  Context *context_;

public:
  virtual ~State() {}
  void set_context(Context *context) { this->context_ = context; }
  virtual void Handler1() = 0;
  virtual void Handler2() = 0;
};

class Context {
private:
  State *state_;

public:
  Context(State *state) : state_(nullptr) { this->TransitionTo(state); }
  ~Context() { delete state_; }
  void TransitionTo(State *state) {
    cout << "Context: Transition to " << typeid(*state).name() << endl;
    if (this->state_ != nullptr)
      delete this->state_;
    this->state_ = state;
    this->state_->set_context(this);
  }

  void Request1() { this->state_->Handler1(); }
  void Request2() { this->state_->Handler2(); }
};

class ConcreteStateA : public State {
public:
  void Handler1() override;
  void Handler2() override {
    cout << "ConcreteStateA: handles request2." << endl;
  }
};

class ConcreteStateB : public State {
public:
  void Handler1() override {
    cout << "ConcreteStateB: handles request1." << endl;
  }
  void Handler2() override {
    cout << "ConcreteStateB: handles request2." << endl;
    cout << "ConcreteStateB wants to change the state of the context." << endl;
    this->context_->TransitionTo(new ConcreteStateA);
  }
};

void ConcreteStateA::Handler1() {
  cout << "ConcreteStateA handles request1." << endl;
  cout << "ConcreteStateA wants to change the state of the context." << endl;
  this->context_->TransitionTo(new ConcreteStateB);
}

void ClientCode() {
  Context *context = new Context(new ConcreteStateA);
  context->Request1();
  context->Request2();
  delete context;
}

int main() { ClientCode(); }