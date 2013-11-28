#include <cstring>

#include "catch.hpp"
#include "LuaDust.hpp"

void writeint(int str)
{
	std::cout << "int: " << str << std::endl;
}

void writechar(char str)
{
	std::cout << "char " << str << std::endl;
}

void writestr(const char *str)
{
	std::cout << "std::string: " << str << std::endl;
}

void writedouble(double d)
{
	std::cout << "double " << d << std::endl;
}

class Test
{
	int nb;

public:
	Test(LuaDust *dust, int n)
	{
		nb = n;
		dust->addRefGlobal("number", &this->nb);
	}

	void change(LuaDust *dust)
	{
		dust->doString("number = 42");
	}

	int getNb()
	{
		return this->nb;
	}
};

TEST_CASE("LuaDust class unit test", "[LuaDust]")
{
	LuaDust lua;

	SECTION("LuaDust::doString test")
	{
		REQUIRE(lua.doString("local a = 42"));
		REQUIRE_THROWS_AS(lua.doString("Foo.new()"), LuaDustException);
	}
	SECTION("LuaDust::doFile test")
	{
		REQUIRE(lua.doFile("doFile_test.lua"));
		REQUIRE_THROWS_AS(lua.doFile("doFile_test_unexist.lua"), LuaDustException);
	}
	SECTION("LuaDust::addGlobal test")
	{
		REQUIRE(lua.addGlobal("text", "test text :D \\o/"));
		REQUIRE(lua.addGlobal("number", 4.5));
		REQUIRE(lua.addGlobal("fnumber", 2.5f));
		REQUIRE(lua.addGlobal("integer", 4));
		REQUIRE(lua.doString("print(text)"));
		REQUIRE(lua.doString("print(number)"));
		REQUIRE(lua.doString("print(fnumber)"));
		REQUIRE(lua.doString("print(integer)"));
	}

	SECTION("LuaDust::addGlobal reference")
	{
		int ref = 43;
		float ref_float = 4.3f;
		double ref_double = 4.3;
		std::string ref_str = "Toto";
		REQUIRE(lua.addRefGlobal("ref", &ref));
		REQUIRE(lua.addRefGlobal("ref_float", &ref_float));
		REQUIRE(lua.addRefGlobal("ref_double", &ref_double));
		REQUIRE(lua.addRefGlobal("ref_str", &ref_str));
		REQUIRE(lua.doString("ref = 42"));
		REQUIRE(lua.doString("ref_float = 4.2"));
		REQUIRE(lua.doString("ref_double = 4.2"));
		REQUIRE(lua.doString("ref_str = \"Yeah !\""));
		REQUIRE(ref == 42);
		REQUIRE(ref_float == 4.2f);
		REQUIRE(ref_double == 4.2);
		REQUIRE(ref_str.compare("Yeah !") == 0);

		ref = 21;
		ref_float = 2.1f;
		ref_double = 2.1;
		ref_str = "Trop bien :D";
		REQUIRE(lua.doString("print(\"ref ===> \"..ref)"));
		REQUIRE(lua.doString("print(\"ref_float ===> \"..ref_float)"));
		REQUIRE(lua.doString("print(\"ref_double ===> \"..ref_double)"));
		REQUIRE(lua.doString("print(\"ref_str ===> \"..ref_str)"));
	}

	SECTION("LuaDust::addFunction test")
	{
		REQUIRE(lua.addFunction("writedouble", &writedouble) != ((void*)0));
		REQUIRE(lua.addFunction("writeint", &writeint) != ((void*)0));
		REQUIRE(lua.addFunction("writestr", &writestr) != ((void*)0));
		REQUIRE(lua.doString("writestr(\"toto\")"));
		REQUIRE(lua.doString("writedouble(42.2)"));
		REQUIRE(lua.doString("writeint(42)"));
	}

	SECTION("LuaDust::addRefGlobal test class")
	{
		Test t(&lua, 43);

		REQUIRE(lua.doString("print(number)"));
		t.change(&lua);
		REQUIRE(lua.doString("print(number)"));
		REQUIRE(t.getNb() == 42);
	}
}