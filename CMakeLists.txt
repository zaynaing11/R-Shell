CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
	src/rshell.cpp src/commands.cpp src/connectors.cpp
)

ADD_EXECUTABLE(test
	unit_tests/test.cpp  src/commands.cpp src/connectors.cpp src/prototype.cpp
)

TARGET_LINK_LIBRARIES(test gtest)

TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON
			   
)

