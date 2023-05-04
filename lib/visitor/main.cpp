#include <array>
#include <iostream>
using namespace std;
class ConcreteComponentA;
class ConcreteComponentB;

class Visitor {
public:
  virtual void
  VisitConcreteComponentA(const ConcreteComponentA *element) const = 0;
  virtual void
  VisitConcreteComponentB(const ConcreteComponentB *element) const = 0;
};

class Component {
public:
  virtual ~Component() {}
  virtual void Accept(Visitor *visitor) const = 0;
};

class ConcreteComponentA : public Component {
public:
  void Accept(Visitor *visitor) const override {
    visitor->VisitConcreteComponentA(this);
  }
  string ExclusiveMethodOfConcreteComponentA() const { return "A"; }
};

class ConcreteComponentB : public Component {
public:
  void Accept(Visitor *visitor) const override {
    visitor->VisitConcreteComponentB(this);
  }
  string ExclusiveMethodOfConcreteComponentB() const { return "B"; }
};

class ConcreteVisitor1 : public Visitor {
public:
  void
  VisitConcreteComponentA(const ConcreteComponentA *element) const override {
    cout << element->ExclusiveMethodOfConcreteComponentA()
         << " + ConcreteVisitor1" << endl;
  }

  void
  VisitConcreteComponentB(const ConcreteComponentB *element) const override {
    cout << element->ExclusiveMethodOfConcreteComponentB()
         << " + ConcreteVisitor1" << endl;
  }
};

class ConcreteVisitor2 : public Visitor {
public:
  void
  VisitConcreteComponentA(const ConcreteComponentA *element) const override {
    cout << element->ExclusiveMethodOfConcreteComponentA()
         << " + ConcreteVisitor2" << endl;
  }

  void
  VisitConcreteComponentB(const ConcreteComponentB *element) const override {
    cout << element->ExclusiveMethodOfConcreteComponentB()
         << " + ConcreteVisitor2" << endl;
  }
};

void ClientCode(std::array<const Component *, 2> components, Visitor *visitor) {
  for (const Component *comp : components) {
    comp->Accept(visitor);
  }
}

int main() {
  std::array<const Component *, 2> components = {new ConcreteComponentA,
                                                 new ConcreteComponentB};
  ConcreteVisitor1 *visitor1 = new ConcreteVisitor1;
  ClientCode(components, visitor1);

  cout << endl;

  ConcreteVisitor2 *visitor2 = new ConcreteVisitor2;
  ClientCode(components, visitor2);

  for (const Component *comp : components) {
    delete comp;
  }
  delete visitor1;
  delete visitor2;
}