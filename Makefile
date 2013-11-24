ifeq ($(OS),Windows_NT)
	EXEC	= lua_dust.dll
else
	EXEC	= lua_dust.so
endif

CXX			= g++
RM			= del
MKDIR		= md
CD			= cd

CXXFLAGS	= -fpic -std=c++11
LDFLAGS		= -shared
INCLUDE		= -I ../../lua/lua-5.2.2/src

SrcExt		= cpp
IncExt		= h*
LibExt		= dll

SrcDir		= src/
IncDir		= hdr/
ObjDir		= obj/
LibDir		= lib/
OutDir		= bin/

TestDir		= test/

SRC			= $(notdir $(wildcard $(SrcDir)*.$(SrcExt)))
OBJ			= $(SRC:.$(SrcExt)=.o)
LIB			= $(subst lib,,$(basename $(notdir $(wildcard $(LibDir)*.$(LibExt)))))

VPATH		= $(SrcDir):$(ObjDir):$(IncDir)

all: 		directories $(EXEC) unittest

.PHONY:		all clean fclean re

$(EXEC): 	$(OBJ)
	@$(CXX) $(addprefix $(ObjDir), $(OBJ)) $(LDFLAGS) -o $(OutDir)/$(EXEC) -L $(LibDir) $(addprefix -l, $(LIB))

%.o: 		%.$(SrcExt)
	@echo $@ Compilation
	@$(CXX) -o $(addprefix $(ObjDir), $@) -c $< $(CXXFLAGS) -I $(IncDir) $(INCLUDE)

clean:
	@$(CD) $(TestDir) && $(MAKE) -s clean
ifeq ($(OS),Windows_NT)
		@$(RM) $(subst /,\,$(addprefix $(ObjDir), $(OBJ)))
else
		@$(RM) $(addprefix $(ObjDir), $(OBJ))
		@$(RM) *~
endif

directories:
ifeq ($(OS),Windows_NT)
	@if not exist "$(subst /,\,$(patsubst  %/,%,$(ObjDir)))" $(MKDIR) $(subst /,\,$(patsubst  %/,%,$(ObjDir)))
	@if not exist "$(subst /,\,$(patsubst  %/,%,$(OutDir)))" $(MKDIR) "$(subst /,\,$(patsubst  %/,%,$(OutDir)))"
endif

unittest:
	@echo.
	@echo " == Start unit test compilation == "
	@$(CD) $(TestDir) && $(MAKE) -s


fclean:		clean
	@$(CD) $(TestDir) && $(MAKE) -s fclean
ifeq ($(OS),Windows_NT)
		@$(RM) $(subst /,\,$(OutDir)/$(EXEC))
else
		@$(RM) $(OutDir)/$(EXEC)
endif

re:			fclean all