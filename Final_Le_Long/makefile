###
### Program Name: Isa's Adventures
### Author: Long Le
### Date: 6/12/2017 
### Description: Basic makefile for the Isa's Adventures program.
###

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 
CXXFLAGS += -g
CXXFLAGS += -Wall 
CXXFLAGS += -Wextra 
CXXFLAGS += -pedantic-errors


# Source files
SRCS = room.cpp 
SRCS += space.cpp 
SRCS += ground.cpp 
SRCS += tree.cpp 
SRCS += water.cpp 
SRCS += rock.cpp 
SRCS += door.cpp 
SRCS += campfire.cpp 
SRCS += main.cpp 
SRCS += character.cpp 
SRCS += player.cpp 
SRCS += goblin.cpp 
SRCS += orc.cpp 
SRCS += ogre.cpp 
SRCS += bandit.cpp 
SRCS += billy.cpp 
SRCS += dead.cpp 
SRCS += princess.cpp 
SRCS += item.cpp 
SRCS += menu.cpp 
SRCS += inputValidation.cpp

# Create an object for each source file
OBJS = $(SRCS:.cpp=.o)

# Header files
HEADERS = room.hpp 
HEADERS += space.hpp 
HEADERS += ground.hpp 
HEADERS += tree.hpp 
HEADERS += water.hpp 
HEADERS += rock.hpp 
HEADERS += door.hpp 
HEADERS += campfire.hpp 
HEADERS += character.hpp 
HEADERS += player.hpp 
HEADERS += goblin.hpp 
HEADERS += orc.hpp 
HEADERS += ogre.hpp 
HEADERS += bandit.hpp 
HEADERS += billy.hpp 
HEADERS += dead.hpp 
HEADERS += princess.hpp 
HEADERS += item.hpp 
HEADERS += menu.hpp 
HEADERS += inputValidation.hpp 

EXECUTABLE = final 

# target: dependencies
# rules to build
${EXECUTABLE} : ${OBJS} ${HEADERS}
	${CXX} ${OBJS} -o ${EXECUTABLE} 

${OBJS}: ${SRCS}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp) 

# target: clean
clean: $(CLEAN)
	@echo "Removed object files"
	@echo "Removed" ${EXECUTABLE}
	@rm ${OBJS} ${EXECUTABLE} 
