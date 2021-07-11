project(lsorderedmap)

cmake_minimum_required(VERSION 3.10)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

aux_source_directory(sample SRC_SAMPLE)

include_directories(include)

add_executable(testcase ${SRC_SAMPLE})

target_link_libraries(testcase lsexception)

install(DIRECTORY include/ls DESTINATION include)
