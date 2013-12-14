# LuaDust

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
}

```

In the Lua script :

```lua
-- main.lua

print(integer)
print(number)
print(string)

```
Output :

```
42
42.2
42
```