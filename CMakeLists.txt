# OPTIMISATION FLAGS : FIXME

set(OPT_FLAGS)

# END OPTIMIZATION FLAGS
# SOURCES : FIXME

set(SRC_ENGINE
    src/main.cc
    src/chess_engine/ai/uci.hh
    src/chess_engine/ai/uci.cc
    src/chess_engine/board/chessboard.hh
    src/chess_engine/board/chessboard-interface.hh
    src/chess_engine/board/color.hh
    src/chess_engine/board/move.hh
    src/chess_engine/board/piece-type.hh
    src/chess_engine/board/position.hh
    src/chess_engine/board/position.hxx
    src/parsing/report-type.hh
    src/parsing/pgn-exception.cc
    src/parsing/pgn-exception.hh
    src/parsing/pgn-move.cc
    src/parsing/pgn-move.hh
    src/parsing/pgn-parser.cc
    src/parsing/pgn-parser.hh
    src/listener/listener.hh
    src/utils/utype.hh)

include_directories(src)
include_directories(src/chess_engine)
include_directories(src/chess_engine/board)
include_directories(src/chess_engine/ai)
include_directories(src/parsing)
include_directories(src/listener)
include_directories(src/utils)

# END SOURCES


# SETUP
cmake_minimum_required(VERSION 3.12)
project(Chess)

# BUILD OPTIONS
set(CMAKE_CXX_STANDARD 17)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${OPT_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g3 -fsanitize=address")

# LIBRARIES
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system program_options)
set(LIBRARIES Boost::system Boost::program_options ${CMAKE_DL_LIBS})

# CHESSENGINE
add_executable(chessengine)
target_sources(chessengine PRIVATE ${SRC_ENGINE})
target_link_libraries(chessengine PRIVATE ${LIBRARIES} -static)
