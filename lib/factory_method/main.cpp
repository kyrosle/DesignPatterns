#include <iostream>

using namespace std;

class Product {
public:
  virtual ~Product() {}
  virtual string Operation() const = 0;
};

class ConcreteProduct1 : public Product {
public:
  string Operation() const override {
    return "{Result of the ConcreteProduct1}";
  }
};

class ConcreteProduct2 : public Product {
public:
  string Operation() const override {
    return "{Result of the ConcreteProduct2}";
  }
};

class Creator {
public:
  virtual ~Creator() {}
  virtual Product *FactoryMethod() const = 0;
  string SomeOperation() const {
    Product *product = this->FactoryMethod();
    string result = "Creator: The same create's code has just worked with" +
                    product->Operation();
    delete product;
    return result;
  }
};

class ConcreteCreator1 : public Creator {
public:
  Product *FactoryMethod() const override { return new ConcreteProduct1(); }
};

class ConcreteCreator2 : public Creator {
public:
  Product *FactoryMethod() const override { return new ConcreteProduct2(); }
};

void ClientCode(const Creator &creator) {
  cout << creator.SomeOperation() << endl;
};

int main() {
  Creator *creator = new ConcreteCreator1();
  ClientCode(*creator);
  cout << endl;
  Creator *creator2 = new ConcreteCreator2();
  ClientCode(*creator2);
}