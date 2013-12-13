#include "LuaDust.hpp"
#include "LuaDustException.hpp"

namespace LuaDust
{
    LuaDust::LuaDust()
    {
    	this->_state = luaL_newstate();
    	luaL_openlibs(this->_state);
    }

    LuaDust::~LuaDust()
    {
    	if (this->_state)
    		lua_close(this->_state);
        for (auto ref : this->_refs)
        {
            delete ref;
        }
    }

    bool LuaDust::doFile(const std::string &file)
    {
    	for (auto ref : this->_refs)
        {
        	ref->pushRef();
        }

       	if(luaL_dofile(this->_state, file.c_str()))
        	throw LuaDustException(luaL_checkstring(this->_state, -1));

        for (auto ref : this->_refs)
        {
        	ref->updateRef();
        }

        return true;
    }

    bool LuaDust::doString(const std::string &lua)
    {
    	for (auto ref : this->_refs)
        {
        	ref->pushRef();
        }

    	if(luaL_dostring(this->_state, lua.c_str()))
        	throw LuaDustException(luaL_checkstring(this->_state, -1));

        for (auto ref : this->_refs)
        {
        	ref->updateRef();
        }

        return true;
    }

    lua_State *LuaDust::getState() const
    {
        return this->_state;
    }

    bool LuaDust::addGlobal(const std::string &name, bool value)
    {
        lua_pushboolean(this->_state, value);
        lua_setglobal(this->_state, name.c_str());
        return true;
    }

    bool LuaDust::addGlobal(const std::string &name, int value)
    {
        lua_pushinteger(this->_state, value);
        lua_setglobal(this->_state, name.c_str());
        return true;
    }

    bool LuaDust::addGlobal(const std::string &name, double value)
    {
    	lua_pushnumber(this->_state, value);
    	lua_setglobal(this->_state, name.c_str());
        return true;
    }

    bool LuaDust::addGlobal(const std::string &name, const char *value)
    {
        lua_pushstring(this->_state, value);
        lua_setglobal(this->_state, name.c_str());
        return true;
    }

    bool LuaDust::addGlobal(const std::string &name, const std::string &value)
    {
    	lua_pushstring(this->_state, value.c_str());
    	lua_setglobal(this->_state, name.c_str());
        return true;
    }

} // End LuaDust namespace
