#include <iostream>
#include <list>
using namespace std;

class Component {
protected:
  Component *parent_;

public:
  virtual ~Component() {}
  void SetParent(Component *parent) { this->parent_ = parent; }
  Component *GetParent() { return this->parent_; }
  virtual void Add(Component *component) {}
  virtual void Remove(Component *component) {}

  virtual bool IsComposite() const { return false; }
  virtual string Operation() const = 0;
};

class Leaf : public Component {
public:
  string Operation() const override { return "Leaf"; }
};

class Composite : public Component {
protected:
  list<Component *> children_;

public:
  void Add(Component *component) override {
    this->children_.push_back(component);
    component->SetParent(this);
  }

  void Remove(Component *component) override {
    this->children_.remove(component);
    component->SetParent(nullptr);
  }

  bool IsComposite() const override { return true; }

  string Operation() const override {
    string result;
    for (const Component *c : this->children_) {
      if (c == children_.back()) {
        result += c->Operation();
      } else {
        result += c->Operation() + "+";
      }
    }
    return "Branch(" + result + ")";
  }
};

void ClientCode(Component *compoent) {
  cout << "Result: " << compoent->Operation();
}

void ClientCode2(Component *compoent1, Component *compoent2) {
  if (compoent1->IsComposite()) {
    compoent1->Add(compoent2);
  }
  cout << "Result: " << compoent1->Operation();
}

int main() {
  Component *simple = new Leaf;
  ClientCode(simple);
  cout << endl;

  Component *tree = new Composite;
  Component *branch1 = new Composite;

  Component *leaf_1 = new Leaf;
  Component *leaf_2 = new Leaf;
  Component *leaf_3 = new Leaf;

  branch1->Add(leaf_1);
  branch1->Add(leaf_2);

  Component *branch2 = new Composite;
  branch2->Add(leaf_3);

  tree->Add(branch1);
  tree->Add(branch2);
  ClientCode(tree);
  cout << endl;

  ClientCode2(tree, simple);
  cout << endl;

  delete simple;
  delete tree;
  delete branch1;
  delete branch2;
  delete leaf_1;
  delete leaf_2;
  delete leaf_3;
}