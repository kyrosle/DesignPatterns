#include <iostream>

using namespace std;

class BaseComponent;

class Mediator {
public:
  virtual void Notify(BaseComponent *sender, string event) const = 0;
};

class BaseComponent {
protected:
  Mediator *mediator_;

public:
  BaseComponent(Mediator *mediator = nullptr) : mediator_(mediator) {}
  void set_mediator(Mediator *mediator) { this->mediator_ = mediator; }
};

class Component1 : public BaseComponent {
public:
  void DoA() {
    cout << "Component 1 does A." << endl;
    this->mediator_->Notify(this, "A");
  }
  void DoB() {
    cout << "Component 1 does B." << endl;
    this->mediator_->Notify(this, "B");
  }
};

class Component2 : public BaseComponent {
public:
  void DoC() {
    cout << "Component 2 does C." << endl;
    this->mediator_->Notify(this, "C");
  }
  void DoD() {
    cout << "Component 2 does D." << endl;
    this->mediator_->Notify(this, "D");
  }
};

class ConcreteMediator : public Mediator {
private:
  Component1 *component1_;
  Component2 *component2_;

public:
  ConcreteMediator(Component1 *component1, Component2 *component2)
      : component1_(component1), component2_(component2) {
    this->component1_->set_mediator(this);
    this->component2_->set_mediator(this);
  }
  void Notify(BaseComponent *sender, string event) const override {
    if (event == "A") {
      std::cout << "Mediator reacts on A and triggers following operations:\n";
      this->component2_->DoC();
    }
    if (event == "D") {
      std::cout << "Mediator reacts on D and triggers following operations:\n";
      this->component1_->DoB();
      this->component2_->DoC();
    }
  }
};

void ClientCode() {
  Component1 *c1 = new Component1;
  Component2 *c2 = new Component2;
  ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
  cout << "Client triggers operation A." << endl;
  c1->DoA();
  cout << endl;
  cout << "Client triggers operation D." << endl;
  c2->DoD();

  delete c1;
  delete c2;
  delete mediator;
}

int main() { ClientCode(); }