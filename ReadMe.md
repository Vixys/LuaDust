# LuaDust v0.2

LuaDust is a lua binding C++ library. This library user C++11 features.

### Compilation

#### Dependency

- [Lua](http://lua.org)
- [cmake](http://www.cmake.org/cmake/resources/software.html)

#### Compile library using cmake

After get lua, you have to configure cmake to generate the Makefile. You have to specify where are the Lua include directory and the library directory.

### Usage

#### Bind C++ language

```cpp
// main.cpp

#include "LuaDust.hpp"

int main()
{
	LuaDust dust;

	dust.addGlobal("integer", 42);
	dust.addGlobal("number", 42.2);
	dust.addGlobal("string", "42");

	dust.addFunction("write", &write);
	dust.addFunction("writeStaticFunction", &Class::writeStaticFunction); // This method must be static
	dust.addFunction("writeMethod", class_ptr, &Class::writeMethod);

	int ref_integer = 21;

	dust.addRefGlobal("ref_integer", &ref_integer);

	std::vector<int> vector = { 21, 42 };

	dust.addArray("vector", &vector);

	dust.doFile("main.lua");

	std::cout << "ref_integer = " << ref_integer << std::endl;
	return 0;
}

```

In the Lua script :

```lua
-- main.lua

print(integer)
print(number)
print(string)

write("Some text")
writeStaticFunction("Some text")
writeMethod("Some text")

ref_integer = 42;

print(vector[0])
print(vector[1])

```
Output :

```
42
42.2
42
Some text
Some text
Some text
21
42
ref_integer = 42
```

### More

For more information please check the [online documentation](http://vixys.github.io/LuaDust).