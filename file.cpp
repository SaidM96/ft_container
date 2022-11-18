#include <iostream>


template<class T>
T func(T a, T b, typename  std::enable_if<std::is_integral<T>::value, T>::type* = NULL)
{
    return a;
}

// template<>
// int func(int a, int b)
// {
//     std::cout << "int\n";
//     return a + b;
// }


int main() {
    std::cout << func(4,4) << "\n";

}