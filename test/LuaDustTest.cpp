#include <cstring>

#include "LuaDust.hpp"
#include "catch.hpp"

bool funcint(int str)
{
	return true;
}

bool funcbool(bool str)
{
	return true;
}

bool funcchar(char str)
{
	return true;
}

bool funcfloat(float str)
{
	return true;
}

bool funcstr(const char *str)
{
	return true;
}

bool funcconststring(const std::string &str)
{
	return true;
}

bool funcstring(std::string str)
{
	return true;
}

bool funcdouble(double d)
{
	return true;
}

class Test
{
	int nb;
	int nb2;

public:
	Test(LuaDust::LuaDust *dust, int n)
	{
		nb = n;
		nb2 = n;
		dust->addRefGlobal("number", &this->nb);
		dust->addFunction("class_add", this, &Test::add);
		dust->addFunction("class_getNb", this, &Test::getNb2);
	}

	void add(int n)
	{
		this->nb2 += n;
	}

	void change(LuaDust::LuaDust *dust)
	{
		dust->doString("number = 42");
	}

	int getNb()
	{
		return this->nb;
	}

	int getNb2()
	{
		return this->nb2;
	}
};

TEST_CASE("LuaDust class unit test", "[LuaDust]")
{
	LuaDust::LuaDust lua;

	SECTION("LuaDust::doString test")
	{
		REQUIRE(lua.doString("local a = 42"));
		REQUIRE_THROWS_AS(lua.doString("Foo.new()"), LuaDust::LuaDustException);
	}
	SECTION("LuaDust::doFile test")
	{
		REQUIRE(lua.doFile("doFile_test.lua"));
		REQUIRE_THROWS_AS(lua.doFile("doFile_test_unexist.lua"), LuaDust::LuaDustException);
	}
	SECTION("LuaDust::addGlobal test")
	{
		REQUIRE(lua.addGlobal("global_text", "test"));
		REQUIRE(lua.addGlobal("number", 4.5));
		REQUIRE(lua.addGlobal("fnumber", 2.5f));
		REQUIRE(lua.addGlobal("integer", 4));
		REQUIRE(lua.addGlobal("boolean", false));
		REQUIRE(lua.doString("assert(global_text == \"test\")"));
		REQUIRE(lua.doString("assert(number == 4.5)"));
		REQUIRE(lua.doString("assert(fnumber == 2.5)"));
		REQUIRE(lua.doString("assert(integer == 4)"));
		REQUIRE(lua.doString("assert(boolean == false)"));
	}

	SECTION("LuaDust::addGlobal reference")
	{
		int ref = 43;
		bool ref_bool = true;
		float ref_float = 4.3f;
		double ref_double = 4.3;
		std::string ref_str = "Toto";
		REQUIRE(lua.addRefGlobal("ref", &ref));
		REQUIRE(lua.addRefGlobal("ref_float", &ref_float));
		REQUIRE(lua.addRefGlobal("ref_double", &ref_double));
		REQUIRE(lua.addRefGlobal("ref_str", &ref_str));
		REQUIRE(lua.addRefGlobal("ref_bool", &ref_bool));
		REQUIRE(lua.doString("ref = 42"));
		REQUIRE(lua.doString("ref_bool = false"));
		REQUIRE(lua.doString("ref_float = 4.2"));
		REQUIRE(lua.doString("ref_double = 4.2"));
		REQUIRE(lua.doString("ref_str = \"Yeah !\""));
		REQUIRE(ref == 42);
		REQUIRE(ref_bool == false);
		REQUIRE(ref_float == 4.2f);
		REQUIRE(ref_double == 4.2);
		REQUIRE(ref_str.compare("Yeah !") == 0);

		ref = 21;
		ref_float = 2.1f;
		ref_double = 2.1;
		ref_str = "Trop bien :D";
		REQUIRE(lua.doString("assert(ref == 21)"));
		REQUIRE(lua.doString("assert(ref_float > 2.09)"));
		REQUIRE(lua.doString("assert(ref_float < 2.11)"));
		REQUIRE(lua.doString("assert(ref_double == 2.1)"));
		REQUIRE(lua.doString("assert(ref_str == \"Trop bien :D\")"));
	}

	SECTION("LuaDust::addFunction test")
	{
		REQUIRE(lua.addFunction("funcfloat", &funcfloat) != ((void*)0));
		REQUIRE(lua.addFunction("funcbool", &funcbool) != ((void*)0));
		REQUIRE(lua.addFunction("funcstring", &funcstring) != ((void*)0));
		REQUIRE(lua.addFunction("funcdouble", &funcdouble) != ((void*)0));
		REQUIRE(lua.addFunction("funcint", &funcint) != ((void*)0));
		REQUIRE(lua.addFunction("funcstr", &funcstr) != ((void*)0));
		REQUIRE(lua.doString("assert(funcstring(\"toto\"))"));
		REQUIRE(lua.doString("assert(funcstr(\"toto\"))"));
		REQUIRE(lua.doString("assert(funcfloat(42.2))"));
		REQUIRE(lua.doString("assert(funcdouble(42.2))"));
		REQUIRE(lua.doString("assert(funcint(42))"));
		REQUIRE(lua.doString("assert(funcbool(true))"));
	}

	SECTION("LuaDust::addRefGlobal test in class")
	{
		Test t(&lua, 43);

		REQUIRE(lua.doString("assert(number == 43)"));
		t.change(&lua);
		REQUIRE(lua.doString("assert(number == 42)"));
		REQUIRE(t.getNb() == 42);
		REQUIRE(lua.doString("class_add(41)"));
		REQUIRE(t.getNb2() == 84);
		REQUIRE(lua.doString("assert(class_getNb() == 84)"));
	}

	SECTION("LuaDust::addArray int test")
	{
		std::vector<int> int_array = { 42, 45, 78, 96};

		REQUIRE(lua.addArray("int_array", &int_array) != ((void*)0));
		REQUIRE(lua.doString("assert(int_array[1] == 42)"));
		REQUIRE(lua.doString("assert(int_array[2] == 45)"));
		REQUIRE(lua.doString("assert(int_array[3] == 78)"));
		REQUIRE(lua.doString("assert(int_array[4] == 96)"));

		int_array[1] = 42;
		int_array[2] = 42;
		int_array[3] = 42;

		REQUIRE(lua.doString("assert(int_array[2] == 42)"));
		REQUIRE(lua.doString("assert(int_array[3] == 42)"));
		REQUIRE(lua.doString("assert(int_array[4] == 42)"));

		REQUIRE(lua.doString("int_array[1] = 21"));
		REQUIRE(lua.doString("int_array[2] = 21"));
		REQUIRE(lua.doString("int_array[3] = 21"));
		REQUIRE(lua.doString("int_array[4] = 21"));
		REQUIRE(int_array[0] == 21);
		REQUIRE(int_array[1] == 21);
		REQUIRE(int_array[2] == 21);
		REQUIRE(int_array[3] == 21);
	}

	SECTION("LuaDust::addArray string test")
	{
		std::vector<std::string> string_array = { "toto", "tata", "yaourt", "pantalon"};

		REQUIRE(lua.addArray("first_array", &string_array) != ((void*)0));
		REQUIRE(lua.doString("assert(first_array[1] == \"toto\")"));
		REQUIRE(lua.doString("assert(first_array[2] == \"tata\")"));
		REQUIRE(lua.doString("assert(first_array[3] == \"yaourt\")"));
		REQUIRE(lua.doString("assert(first_array[4] == \"pantalon\")"));

		string_array[1] = "42";
		string_array[2] = "42";
		string_array[3] = "42";

		REQUIRE(lua.doString("assert(first_array[2] == \"42\")"));
		REQUIRE(lua.doString("assert(first_array[3] == \"42\")"));
		REQUIRE(lua.doString("assert(first_array[4] == \"42\")"));

		REQUIRE(lua.doString("first_array[1] = \"STRING\""));
		REQUIRE(lua.doString("first_array[2] = \"STRING\""));
		REQUIRE(lua.doString("first_array[3] = \"STRING\""));
		REQUIRE(lua.doString("first_array[4] = \"STRING\""));
		REQUIRE(string_array[0] == "STRING");
		REQUIRE(string_array[1] == "STRING");
		REQUIRE(string_array[2] == "STRING");
		REQUIRE(string_array[3] == "STRING");
	}

	SECTION("IVarRef::getStringValue test")
	{
		bool v_bool = true;
		auto ref_v_bool = lua.addRefGlobal("v_bool", &v_bool);
		std::string v_string = "test string";
		auto ref_v_string = lua.addRefGlobal("v_string", &v_string);
		std::vector<int> v_int_array = { 42, 45, 78, 96};
		auto ref_v_int_array = lua.addArray("v_int_array", &v_int_array);
		std::vector<std::string> v_string_array = { "toto", "tata", "yaourt", "pantalon"};
		auto ref_v_string_array = lua.addArray("v_string_array", &v_string_array);

		REQUIRE(ref_v_bool->getStringValue(true) == "true");
		REQUIRE(ref_v_string->getStringValue(true) == "\"test string\"");
		REQUIRE(ref_v_int_array->getStringValue(true) == "{ 42, 45, 78, 96 }");
		REQUIRE(ref_v_string_array->getStringValue(true) == "{ \"toto\", \"tata\", \"yaourt\", \"pantalon\" }");
	}
}