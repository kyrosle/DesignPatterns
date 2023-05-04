#include <iostream>
using namespace std;
class AbstractClass {
public:
  void TemplateMethod() const {
    this->BaseOperation1();
    this->RequiredOperations1();
    this->BaseOperation2();
    this->Hook1();
    this->RequiredOperation2();
    this->BaseOperation3();
    this->Hook2();
  }

protected:
  void BaseOperation1() const {
    std::cout << "AbstractClass says: I am doing the bulk of the work\n";
  }
  void BaseOperation2() const {
    std::cout << "AbstractClass says: But I let subclasses override some "
                 "operations\n";
  }
  void BaseOperation3() const {
    std::cout
        << "AbstractClass says: But I am doing the bulk of the work anyway\n";
  }
  virtual void RequiredOperations1() const = 0;
  virtual void RequiredOperation2() const = 0;
  virtual void Hook1() const {}
  virtual void Hook2() const {}
};

class ConcreteClass1 : public AbstractClass {
protected:
  void RequiredOperations1() const override {
    cout << "ConcreteClass1 says: Implemented Operation1" << endl;
  }
  void RequiredOperation2() const override {
    cout << "ConcreteClass1 says: Implemented Operation2" << endl;
  }
};

class ConcreteClass2 : public AbstractClass {
protected:
  void RequiredOperations1() const override {
    cout << "ConcreteClass2 says: Implemented Operation1" << endl;
  }
  void RequiredOperation2() const override {
    cout << "ConcreteClass2 says: Implemented Operation2" << endl;
  }
  void Hook1() const override {
    cout << "ConcreteClass2 says: Overridden Hook1" << endl;
  }
};

void ClientCode(AbstractClass *class_) { class_->TemplateMethod(); }

int main() {
  ConcreteClass1 *concreteClass1 = new ConcreteClass1;
  ClientCode(concreteClass1);
  cout << endl;
  ConcreteClass2 *concreteClass2 = new ConcreteClass2;
  ClientCode(concreteClass2);
  delete concreteClass1;
  delete concreteClass2;
}