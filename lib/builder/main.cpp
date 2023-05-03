#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;
class Product1 {
public:
  vector<string> parts_;
  void ListParts() const {
    cout << "Product parts: ";
    for (size_t i = 0; i < parts_.size(); i++) {
      if (parts_[i] == parts_.back()) {
        cout << parts_[i];
      } else {
        cout << parts_[i] << ", ";
      }
    }
    cout << endl;
  }
};

class Builder {
public:
  virtual ~Builder() {}
  virtual void ProductPartA() const = 0;
  virtual void ProductPartB() const = 0;
  virtual void ProductPartC() const = 0;
};

class ConcerteBuilder1 : public Builder {
private:
  Product1 *product;

public:
  ConcerteBuilder1() { this->Reset(); }
  ~ConcerteBuilder1() { delete product; }
  void Reset() { this->product = new Product1(); }
  void ProductPartA() const override {
    this->product->parts_.push_back("PartA1");
  }
  void ProductPartB() const override {
    this->product->parts_.push_back("PartB1");
  }
  void ProductPartC() const override {
    this->product->parts_.push_back("PartC1");
  }
  Product1 *GetProduct() {
    Product1 *result = this->product;
    this->Reset();
    return result;
  }
};

class Director {
private:
  Builder *builder;

public:
  void set_builder(Builder *builder) { this->builder = builder; }
  void BuildMinimalViableProduct() { this->builder->ProductPartA(); }
  void BuildFullFeaturedProduct() {
    this->builder->ProductPartA();
    this->builder->ProductPartB();
    this->builder->ProductPartC();
  }
};

void ClientCode(Director &director) {
  ConcerteBuilder1 *builder = new ConcerteBuilder1();
  director.set_builder(builder);
  director.BuildMinimalViableProduct();

  Product1 *p = builder->GetProduct();
  p->ListParts();
  delete p;

  director.BuildFullFeaturedProduct();

  p = builder->GetProduct();
  p->ListParts();
  delete p;

  builder->ProductPartA();
  builder->ProductPartC();
  p = builder->GetProduct();
  p->ListParts();
  delete p;

  delete builder;
}

int main() {
  Director *director = new Director();
  ClientCode(*director);
  delete director;
}