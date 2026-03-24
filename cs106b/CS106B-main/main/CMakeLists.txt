cmake_minimum_required (VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
# 删除了 -ldl
SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")
project(main)

include_directories(lib/StanfordCPPLib)
include_directories(lib/StanfordCPPLib/util)
include_directories(lib/StanfordCPPLib/collections)
include_directories(lib/StanfordCPPLib/graphics)
include_directories(lib/StanfordCPPLib/io)
include_directories(lib/StanfordCPPLib/private)
include_directories(lib/StanfordCPPLib/system)
file(GLOB stanford_files
        "lib/StanfordCPPLib/graphics/*.h"
        "lib/StanfordCPPLib/graphics/*.cpp"
        "lib/StanfordCPPLib/util/*.h"
        "lib/StanfordCPPLib/util/*.cpp"
        "lib/StanfordCPPLib/system/*.h"
        "lib/StanfordCPPLib/system/*.cpp"
        "lib/StanfordCPPLib/collections/*.h"
        "lib/StanfordCPPLib/collections/*.cpp"
        "lib/StanfordCPPLib/private/*.h"
        "lib/StanfordCPPLib/private/*.cpp"
        "lib/StanfordCPPLib/io/*.h"
        "lib/StanfordCPPLib/io/*.cpp"
)
add_library(stanford ${stanford_files})

aux_source_directory(src main_SOURCES)

link_libraries(stanford)
add_executable(main ${main_SOURCES})

target_link_libraries(${PROJECT_NAME}
        PUBLIC ${Boost_STACKTRACE_BASIC_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_BACKTRACE_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_ADDR2LINE_LIBRARY}
        PUBLIC ${Boost_STACKTRACE_NOOP_LIBRARY}
        # 删除了 dl
        PUBLIC pthread
        PUBLIC dbghelp
)