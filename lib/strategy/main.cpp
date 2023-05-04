#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string_view>
using namespace std;

class Strategy {
public:
  virtual ~Strategy() = default;
  virtual string doAlgorithm(string_view) const = 0;
};

class Context {
private:
  std::unique_ptr<Strategy> strategy_;

public:
  explicit Context(std::unique_ptr<Strategy> &&strategy = {})
      : strategy_(std::move(strategy)) {}
  void set_strategy(std::unique_ptr<Strategy> &&strategy) {
    strategy_ = std::move(strategy);
  }
  void doSomeBusinessLogic() const {
    if (strategy_) {
      cout << "Context: Sorting data using the strategy" << endl;
      string result = strategy_->doAlgorithm("aecbd");
      cout << result << endl;
    } else {
      cout << "Context: Strategy isn't set" << endl;
    }
  }
};

class ConcreteStrategyA : public Strategy {
public:
  string doAlgorithm(string_view data) const override {
    string result(data);
    std::sort(result.begin(), result.end());
    return result;
  }
};

class ConcreteStrategyB : public Strategy {
public:
  string doAlgorithm(string_view data) const override {
    string result(data);
    std::sort(result.begin(), result.end(), greater<>());
    return result;
  }
};

void ClientCode() {
  Context context(std::make_unique<ConcreteStrategyA>());
  context.doSomeBusinessLogic();
  cout << endl;
  context.set_strategy(std::make_unique<ConcreteStrategyB>());
  context.doSomeBusinessLogic();
}

int main() { ClientCode(); }