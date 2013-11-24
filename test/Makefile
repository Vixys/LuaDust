ifeq ($(OS),Windows_NT)
	EXEC	= test.exe
else
	EXEC	= test
endif


CXX			= g++
RM			= del
MKDIR		= md
CP 			= copy /Y

CXXFLAGS	= -std=c++11 -W -Wall
LDFLAGS		= 

SrcExt		= cpp
IncExt		= h*
LibExt		= dll

SrcDir		= ./
IncDir		= ../hdr/
ObjDir		= obj/
OutDir		= ../bin/
LibDir		= ../lib/

CD			= cd

ifeq ($(OS),Windows_NT)
	LUALIB	= lua_dust.dll
else
	LUALIB	= lua_dust.so
endif

TARGET		= $(EXEC)

SRC			= $(notdir $(wildcard $(SrcDir)*.$(SrcExt)))
INC			= $(notdir $(wildcard $(IncDir)*.$(IncExt)))
OBJ			= $(SRC:.$(SrcExt)=.o)
LIB			= $(wildcard $(LibDir)*.$(LibExt))

INCLUDE		= -I include -I E:\Dev\C++\lua\lua-5.2.2\src

VPATH		= $(SrcDir):$(ObjDir):$(IncDir)

all: 		directories start $(EXEC)
	@echo "$(EXEC) compilation and linking sucessfull"
	@echo.
	@echo "Launch test"
	@echo.
ifeq ($(OS),Windows_NT)
	@$(CP) $(subst /,\,$(OutDir)$(LUALIB)) .
else
	@$(CP) $(OutDir)$(LUALIB) .
endif
	@$(EXEC)

directories:
ifeq ($(OS),Windows_NT)
	@if not exist "$(subst /,\,$(patsubst  %/,%,$(ObjDir)))" $(MKDIR) $(subst /,\,$(patsubst  %/,%,$(ObjDir)))
	@if not exist "$(subst /,\,$(patsubst  %/,%,$(OutDir)))" $(MKDIR) "$(subst /,\,$(patsubst  %/,%,$(OutDir)))"
endif

start:
	@echo " = Start $(EXEC) compilation = "

.PHONY:		all clean fclean re

$(EXEC): 	$(OBJ)
	@echo "Linking $(TARGET)"
	$(CXX) $(addprefix $(ObjDir), $(OBJ)) $(LDFLAGS) -o $(TARGET) $(OutDir)$(LUALIB) $(LIB)

%.o: 		%.$(SrcExt) $(INC)
	@echo $@ Compilation
	$(CXX) -o $(addprefix $(ObjDir), $@) -c $< $(CXXFLAGS) -I $(IncDir) $(INCLUDE)

clean:
ifeq ($(OS),Windows_NT)
		@$(RM) $(subst /,\,$(addprefix $(ObjDir), $(OBJ)))
else
		@$(RM) $(addprefix $(ObjDir), $(OBJ))
		@$(RM) *~
endif

fclean:		clean
ifeq ($(OS),Windows_NT)
		@$(RM) $(subst /,\,$(TARGET))
else
		@$(RM) $(TARGET)
endif

re:			fclean all