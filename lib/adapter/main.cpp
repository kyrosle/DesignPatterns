#include <algorithm>
#include <iostream>
using namespace std;

class Target {
public:
  virtual ~Target() = default;
  virtual string Request() const {
    return "Target: The default target's behavior.";
  }
};

class Adaptee {
public:
  string SpecificRequest() const { return ".eetpadA eth fo roivaheb laiceps"; }
};

// multiple extend
class Adapter : public Target {
private:
  Adaptee *adaptee_;

public:
  Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
  string Request() const override {
    string to_reverse = this->adaptee_->SpecificRequest();
    reverse(to_reverse.begin(), to_reverse.end());
    return "Adapter: (TRANSLATED) " + to_reverse;
  }
};

void ClientCode(const Target *target) { cout << target->Request(); }

int main() {
  Target *target = new Target;
  ClientCode(target);
  cout << endl;
  Adaptee *adaptee = new Adaptee;
  cout << adaptee->SpecificRequest();
  cout << endl;
  Adapter *adapter = new Adapter(adaptee);
  ClientCode(adapter);
  cout << endl;

  delete target;
  delete adaptee;
  delete adapter;
}