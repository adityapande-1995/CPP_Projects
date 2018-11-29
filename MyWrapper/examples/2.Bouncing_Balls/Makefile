#OBJS specifies which files to compile as part of the project
OBJS = main.cpp 

#CC specifies which compiler we're using
CC = g++ -std=c++17

#COMPILER_FLAGS specifies the additional compilation options we're using
COMPILER_FLAGS = -w 

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lGLU -lGL -lglut 

# HEADER_INCLUDE specifies include path for headers
HEADER_INCLUDE = -I ../../#-I/usr/include/SDL2  -I/usr/include/eigen3/	

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = a

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(HEADER_INCLUDE) -o $(OBJ_NAME)

run : $(OBJ_NAME)
	./$(OBJ_NAME)