// Copyright 2020 Your Name euvie

#ifndef INCLUDE_STACK2_HPP_
#define INCLUDE_STACK2_HPP_
#include <utility>

template <typename T>
class Stack2 {
 public:
  Stack2() = default;

  Stack2(const Stack2 &stack) = delete;
  auto operator=(const Stack2 &stack) = delete;

  Stack2(Stack2 &&stack) noexcept {
    this->top = stack.top;
    stack.top = nullptr;
  }
  auto operator=(Stack2 &&stack) noexcept -> Stack2 & {
    this->top = stack.top;
    stack.top = nullptr;
  }

  template<typename...Args>
  void push_emplace(Args&&...value){ // push для нескольких элементов
    top = new Node<T>{{std::forward<Args>(value)...}, top};   // forward
                                                              // сохраняет тип
                                                              // ссылки которую
                                                              // передают
  }

  void push(T &&value) {
    top = new Node<T>{std::forward<T>(value), top};
  }

  const T &head() const {
    if (top){
      return top->value;
    }else {
      throw std::runtime_error("Empty stack head");
    }
  }

  T pop() {
    if (top){
      auto *tmp = top;
      T data = std::move(top->value);
      top = top->next;
      delete tmp;
      return data;
    }else {
      throw std::runtime_error("Empty stack pop");
    }
  }

  void clearer() {
    while (top) {
      Node<T> *tmp = top->next;
      delete (top);
      top = tmp;
    }
  }

  ~Stack2() { clearer(); }

 private:
  Node<T> *top = nullptr;
};

#endif // INCLUDE_STACK2_HPP_
