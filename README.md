# ft_containers - C++ Containers, Easy Mode

![C++](https://img.shields.io/badge/C%2B%2B-98-blue)
![Namespace](https://img.shields.io/badge/Namespace-ft-brightgreen)

## Introduction

The `ft_containers` project aims to implement a few container types of the C++ standard template library. The goal is to re-implement standard C++ containers to ensure a solid understanding of their functionality and underlying structure. This project version is 5.2.

## Features

The project involves implementing the following containers:

- `vector`: A dynamic array container similar to `std::vector`. The specialization for `vector<bool>` is not required.
- `map`: An associative container that stores key-value pairs in a sorted order, similar to `std::map`.
- `stack`: A container adapter that uses your implemented `vector` class as the default underlying container. It should be compatible with other containers, including the standard ones.

Additionally, you must also implement the following C++98 features:

- `std::iterator_traits`
- `std::reverse_iterator`
- `std::enable_if`
- `std::is_integral`
- `std::equal` and/or `std::lexicographical_compare`
- `std::pair`
- `std::make_pair`

## Compiling

To compile the project, use the following guidelines:

- Compile your code with `c++` and the flags `-Wall -Wextra -Werror`.
- The code should still compile with the flag `-std=c++98`.
- The project must include a `Makefile` that compiles the source files without relinking.
- The `Makefile` should contain at least the rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.

## Usage

To use the implemented containers, follow these steps:

1. Clone the `ft_containers` project to your local machine.
2. Compile the project using the provided `Makefile`.
3. Run the test binaries for both your implemented containers and the standard library containers.
4. Compare the outputs and performance/timing, noting that your containers may be up to 20 times slower.

**Note**: For more details on the project requirements, refer to the original instructions provided in the project folder.

Happy coding!
