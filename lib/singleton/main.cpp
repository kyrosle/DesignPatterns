#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

namespace base_singleton {
class Singleton {
protected:
  Singleton(const string value) : value_(value) {}
  static Singleton *singleton_;
  string value_;

public:
  Singleton(Singleton &other) = delete;
  void operator=(const Singleton &) = delete;
  static Singleton *GetInstance(const string &value);
  void SomeBusinesslogic() {}
  string value() const { return value_; }
};

Singleton *Singleton::singleton_ = nullptr;

Singleton *Singleton::GetInstance(const string &value) {
  if (singleton_ == nullptr) {
    singleton_ = new Singleton(value);
  }
  return singleton_;
}

void ThreadFoo() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("FOO");
  cout << singleton->value() << endl;
}

void ThreadBar() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("BAR");
  cout << singleton->value() << endl;
}
} // namespace base_singleton

namespace thread_safe {
class Singleton {
private:
  static Singleton *pinstance_;
  static std::mutex mutex_;

protected:
  Singleton(const string value) : value_(value) {}
  string value_;

public:
  Singleton(Singleton &other) = delete;
  void operator=(const Singleton &) = delete;
  static Singleton *GetInstance(const string &value);
  void SomeBussinessLogic() {}
  string value() const { return value_; }
};
Singleton *Singleton::pinstance_{nullptr};
std::mutex Singleton::mutex_;

Singleton *Singleton::GetInstance(const string &value) {
  std::lock_guard<std::mutex> lock(mutex_);
  if (pinstance_ == nullptr) {
    pinstance_ = new Singleton(value);
  }
  return pinstance_;
}

void ThreadFoo() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("FOO");
  cout << singleton->value() << endl;
}

void ThreadBar() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  Singleton *singleton = Singleton::GetInstance("BAR");
  cout << singleton->value() << endl;
}
} // namespace thread_safe

int main() {
  std::thread t1(base_singleton::ThreadFoo);
  std::thread t2(base_singleton::ThreadBar);
  t1.join();
  t2.join();

  cout << endl;

  std::thread t3(thread_safe::ThreadFoo);
  std::thread t4(thread_safe::ThreadBar);
  t3.join();
  t4.join();
}