// Copyright 2020 Your Name euvie

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_
#include <iostream>
#include <utility>

template <typename T>   //структура, описывающая узел списка
struct Node{
  T value;              //поле данных
  Node *next = nullptr; //указатель на следующий элемент
};

template <typename T>
class Stack
{
 public:
  Stack() = default; // дефолтный конструктор, по умолчанию создает объект
                     // класса

  Stack(const Stack &stack) = delete; // консруктор копирования
                                      // delete запрещает копирование
  auto operator = (const Stack &stack) = delete;

  Stack(Stack &&stack) noexcept { // конструктор перемещения
    this->top = stack.top;
    stack.top = nullptr;
  }
  auto operator = (Stack &&stack)  noexcept -> Stack&{ //noexcept отвечает за
                                                       // исключения// работает
                                                       // быстрее чем throw()
                                                       // оператор перегрузки
                                                       // для объектов класса
    this->top = stack.top;
    stack.top = nullptr;
  }

  void push(T&& value){
    Node<T> *newnode;
    newnode = top;
    top = new Node<T>;
    top->next = newnode;
    top->value = value;
  }

  void push(const T& value){//передаем value по константной ссылке, чтобы не
    // было перерасхода памяти (много  раз будет
    // копироваться)
    Node<T> *newnode;
    newnode = top;
    top = new Node<T>;
    top->next = newnode;
    top->value = std::move(value);
  }

  void pop(){
    if (top){
      Node<T> *_top = top->next;
      delete top;
      top = _top;
    }else {
      throw std::runtime_error("Empty stack pop");
    }
  }

  const T& head() const{ //возвращаем константную сылку чтобы не копировать
    if (top) {
      return top->value;
    } else {
      throw std::runtime_error("Empty stack head");
    }
  }

  void clearer(){
    while (top) {
      Node<T> *tmp = top->next;
      delete (top);

      top = tmp;
    }
  }

  ~Stack(){
    clearer();
  }

  private:
   Node<T> *top = nullptr; //указатель на вершину стэка
};

#endif // INCLUDE_STACK_HPP_
