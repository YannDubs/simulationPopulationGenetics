project (Pool CXX) 
cmake_minimum_required (VERSION 2.6) 
set (CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11") 

enable_testing()
add_subdirectory(gtest) 
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package (Doxygen) 
add_custom_target(doc 
    ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/Doxyfile 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
              COMMENT  "Generating  API  documentation  with  Doxygen" 
VERBATIM)

Include_directories (Before tclap/include)
add_executable (Pool src/Pool.h src/main.cpp src/Pool.cpp src/MetaPool.cpp src/MetaPool.hpp src/VectorConstraintTCLAP.h src/PoolDrep.h src/PoolDrep.cpp src/MetaPoolDrep.cpp src/MetaPoolDrep.hpp src/World.hpp src/World.cpp) 


add_executable (pool_unittest src/main_test.cpp src/Pool.h src/Pool.cpp src/MetaPool.cpp src/MetaPool.hpp src/VectorConstraintTCLAP.h ) 
target_link_libraries (pool_unittest gtest gtest_main) 
add_test (pool_unittest pool_unittest) 


