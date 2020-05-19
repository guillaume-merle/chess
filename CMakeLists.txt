# OPTIMISATION FLAGS : FIXME
# In cmake, we define variables with set(VAR Value [Value]*)
# set(MYVAR "val1") assigns value val1 to MYVAR
# set(MYVAR "val1" "val2") creates a list

set(OPT_FLAGS
    -Ofast
)

# END OPTIMIZATION FLAGS
# SOURCES : FIXME
# Put all your sources here EXCEPT YOUR MAIN.CC
set(SRC_ENGINE
    src/chess_engine/ai/evaluation.cc
    src/chess_engine/ai/evaluation.hh
    src/chess_engine/ai/move-heuristics.cc
    src/chess_engine/ai/move-heuristics.hh
    src/chess_engine/ai/move-ordering.cc
    src/chess_engine/ai/move-ordering.hh
    src/chess_engine/ai/search.cc
    src/chess_engine/ai/search.hh
    src/chess_engine/ai/uci.cc
    src/chess_engine/ai/uci.hh
    src/chess_engine/ai/zobrist.cc
    src/chess_engine/ai/zobrist.hh
    src/chess_engine/board/attacks.cc
    src/chess_engine/board/attacks.hh
    src/chess_engine/board/bitboard.cc
    src/chess_engine/board/bitboard.hh
    src/chess_engine/board/chessboard-interface.hh
    src/chess_engine/board/chessboard.cc
    src/chess_engine/board/chessboard.hh
    src/chess_engine/board/color.hh
    src/chess_engine/board/knight.hh
    src/chess_engine/board/magic.cc
    src/chess_engine/board/magic.hh
    src/chess_engine/board/move.cc
    src/chess_engine/board/move.hh
    src/chess_engine/board/movegen.cc
    src/chess_engine/board/movegen.hh
    src/chess_engine/board/pawn.hh
    src/chess_engine/board/perft.cc
    src/chess_engine/board/perft.hh
    src/chess_engine/board/pgn.cc
    src/chess_engine/board/pgn.hh
    src/chess_engine/board/piece-type.hh
    src/chess_engine/board/position.hh
    src/chess_engine/board/position.hxx
    src/listener/listener-manager.cc
    src/listener/listener-manager.hh
    src/listener/listener.hh
    src/parsing/fen-object.cc
    src/parsing/fen-object.hh
    src/parsing/fen-rank.cc
    src/parsing/fen-rank.hh
    src/parsing/option-parser.cc
    src/parsing/option-parser.hh
    src/parsing/perft-object.cc
    src/parsing/perft-object.hh
    src/parsing/perft-parser.cc
    src/parsing/perft-parser.hh
    src/parsing/pgn-exception.cc
    src/parsing/pgn-exception.hh
    src/parsing/pgn-move.cc
    src/parsing/pgn-move.hh
    src/parsing/pgn-parser.cc
    src/parsing/pgn-parser.hh
    src/parsing/report-type.hh
    src/utils/logger.cc
    src/utils/logger.hh
    src/utils/utils.hh
    src/utils/utype.hh
)


# Directories containing headers must be specified in the include_directories()
include_directories(
    src
    src/chess_engine
    src/chess_engine/board
    src/chess_engine/ai
    src/parsing
    src/listener
    src/utils
    tests
)


# Put your test files here
set(SRC_GTEST
    tests/test_main.cc
    tests/test_king.hh
    tests/test_knight.hh
    tests/test_pawn.hh
    tests/test_bishop.hh
    tests/test_rook.hh
    tests/test_bitboard.hh
    tests/test_queen.hh
    tests/test_chessboard.hh
    tests/test_zobrist.hh
    tests/test_move_ordering.hh
)

# END SOURCES


# SETUP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
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
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -fsanitize=address")

# LIBRARIES
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Boost REQUIRED COMPONENTS system program_options)
set(LIBRARIES Boost::system Boost::program_options ${CMAKE_DL_LIBS})

# CHESSENGINE
add_executable(chessengine)
target_sources(chessengine PRIVATE "src/main.cc" ${SRC_ENGINE})
target_link_libraries(chessengine PRIVATE ${LIBRARIES})

# TESTS
# Check if GTest is installed
find_package(GTest)

# If it is, create a dedicated target "tests"
if(GTest_FOUND)
  include(GoogleTest)

  add_executable(tests)
  target_sources(tests PRIVATE
    ${SRC_GTEST}
    ${SRC_ENGINE}
  )

  target_compile_options(tests PRIVATE -Wall -Werror -Wextra)
  target_link_libraries(tests PRIVATE GTest::GTest ${LIBRARIES})

  add_custom_target(check
                    COMMAND ./tests
                    DEPENDS
                    tests
  )
endif()

# STATIC TARGET
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_executable(chessengine-static)
    target_sources(chessengine-static PRIVATE "src/main.cc" ${SRC_ENGINE})
    target_link_libraries(chessengine-static PRIVATE ${LIBRARIES} -static)
endif()
