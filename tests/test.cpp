// Copyright 2020 Your Name euvie

#include <gtest/gtest.h>
#include "stack.hpp"
#include "stack2.hpp"

template<typename T> //тесты структуры
struct Traffic_light{
  T red;
  T yellow;
  T green;
};

TEST(Example, EmptyTest) {
  EXPECT_TRUE(true);
}

TEST(Stack, NonCopiable_Movable){
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value); //
                                                              // проверка что
                                                              // класс создан
                                                              // перемещаемым
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value); //
                                                               // проверка что
                                                               // класс не
                                                               // копируемый
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
  EXPECT_TRUE(std::is_nothrow_move_constructible<Stack<int>>::value);
                                      // конструктор не выбрасывает исключения
}

TEST(Stack, Push_rvalue){
  Stack<double> a;

  EXPECT_THROW(a.head(), std::runtime_error);

  a.push(3.14); // rvalue
  EXPECT_EQ(a.head(), 3.14);

  double tmp = 41.3; // lvalue
  a.push(std::move(tmp));
  EXPECT_EQ(a.head(), 41.3);
}

TEST(Stack, Push_lvalue){
  Stack<std::string> plants;

  EXPECT_THROW(plants.head(), std::runtime_error);

  std::string tree = "maple"; //дерево - клён
                              // кладем в стек первый
                              // элемент(строку)
  plants.push(tree);
  EXPECT_EQ(plants.head(), "maple"); //проверяем верхушку стека

  std::string bush = "blackberry"; //куст - ежевика
  std::string flower = "rose";     //цветок - роза
  plants.push(bush);   //кладем в стек второй и третий элемент
  plants.push(flower);
  EXPECT_EQ(plants.head(), "rose"); //проверяем верхушку стека
}

TEST(Stack, Pop){
  Stack<int> b;    //проверяем работу с int
  EXPECT_THROW(b.head(), std::runtime_error);

  b.push(0);
  b.push(1);
  b.push(2);
  b.pop();
  EXPECT_EQ(b.head(), 1);

  b.pop();
  EXPECT_EQ(b.head(), 0);

  b.pop();
  EXPECT_THROW(b.head(), std::runtime_error);
}

TEST(Stack, head){
  Stack<int> b;
  b.push(0);
  EXPECT_EQ(b.head(), 0);
  b.push(1);
  EXPECT_EQ(b.head(), 1);
  b.push(2);
  EXPECT_EQ(b.head(), 2);
}

TEST(Stack, Struct){
  Stack<Traffic_light<int>> amount;
  Traffic_light<int> test_struct1{1, 2,3 };
  amount.push(test_struct1);
  EXPECT_EQ(amount.head().red, 1);
  EXPECT_EQ(amount.head().yellow, 2);
  EXPECT_EQ(amount.head().green, 3);

  Traffic_light<int> test_struct2{4, 5,6 };
  Traffic_light<int> test_struct3{7, 8, 9 };
  amount.push(test_struct2);
  amount.push(test_struct3);
  EXPECT_EQ(amount.head().red, 7);
  EXPECT_EQ(amount.head().yellow, 8);
  EXPECT_EQ(amount.head().green, 9);

  amount.pop();
  EXPECT_EQ(amount.head().red, 4);
  EXPECT_EQ(amount.head().yellow, 5);
  EXPECT_EQ(amount.head().green, 6);
}

template<typename T>
class Weather {
 public:
  Weather(T t1, T t2, T t3)
      :snow(t1), rain(t2), sun(t3)
  {}
  Weather(const Weather &Weather_today) = delete;
  auto operator=(const Weather &Weather_today) = delete;
  Weather(Weather &&Weather_today) = default;
  auto operator=(Weather &&Weather_today) noexcept -> Weather& = default;

  T snow;
  T rain;
  T sun;
};

TEST(Stack2, Constructor){
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
}

TEST(Stack2, push_pop){
  Stack2<Weather<int>> amount;
  Weather<int> test1 (1, 2, 3);
  Weather<int> test2 (4, 5, 6);
  Weather<int> test3 (7, 8, 9);
  amount.push(std::move(test1));
  amount.push(std::move(test2));
  amount.push(std::move(test3));
  EXPECT_EQ(amount.head().snow,  7);
  EXPECT_EQ(amount.head().rain,  8);
  EXPECT_EQ(amount.head().sun,  9);

  amount.pop();
  EXPECT_EQ(amount.head().snow,  4);
  EXPECT_EQ(amount.head().rain,  5);
  EXPECT_EQ(amount.head().sun,  6);
}

TEST(Stack2, push_emplace){
  Stack2<Weather<int>> amount;
  amount.push_emplace(1,2,3);
  amount.push_emplace(4,5,6);
  amount.push_emplace(7,8,9);
  EXPECT_EQ(amount.head().snow,  7);
  EXPECT_EQ(amount.head().rain,  8);
  EXPECT_EQ(amount.head().sun,  9);
  amount.pop();
  EXPECT_EQ(amount.head().snow,  4);
  EXPECT_EQ(amount.head().rain,  5);
  EXPECT_EQ(amount.head().sun,  6);
}
