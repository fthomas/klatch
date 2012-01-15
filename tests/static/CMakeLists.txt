get_target_property(klatch_SOURCES      klatch klatch_SOURCES)
get_target_property(klatch_HEADERS      klatch klatch_HEADERS)
get_target_property(klatch_INCLUDE_DIRS klatch klatch_INCLUDE_DIRS)

foreach(DIR ${klatch_INCLUDE_DIRS})
    set(INCLUDE_ARGS ${INCLUDE_ARGS} -I${DIR})
endforeach()

set(CURR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CURR_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})
string(REPLACE "/" "\\/" ESC_SRC_DIR ${CMAKE_SOURCE_DIR}/)

function(run_static_analyzer CMD ARGS OUTFILE)
    find_program(ANALYZER_${CMD} ${CMD})
    find_program(SED_EXEC sed)

    if(ANALYZER_${CMD} AND SED_EXEC)
        add_custom_command(
          OUTPUT ${OUTFILE}
          COMMAND ${ANALYZER_${CMD}} ${ARGS} > ${OUTFILE} 2>&1 || true
          COMMAND ${SED_EXEC} -i 's/${ESC_SRC_DIR}//' ${OUTFILE}
          COMMAND ${CMAKE_COPY} ${OUTFILE} ${CURR_SRC_DIR}/
          DEPENDS ${klatch_SOURCES} ${klatch_HEADERS})
        set(RESULTS ${RESULTS};${CURR_BIN_DIR}/${OUTFILE} PARENT_SCOPE)
    endif()
endfunction()

set(clang_ARGS --analyze -x c++ -std=c++11 -Wall -Wextra
  ${INCLUDE_ARGS} ${klatch_SOURCES})
run_static_analyzer(clang "${clang_ARGS}" sa-clang.txt)

set(flawfinder_ARGS --dataonly --quiet --minlevel=0
  ${klatch_SOURCES} ${klatch_HEADERS})
run_static_analyzer(flawfinder "${flawfinder_ARGS}" sa-flawfinder.txt)

set(g++_ARGS -S -std=c++11 -Wall -Wextra -Weffc++
  ${INCLUDE_ARGS} ${klatch_SOURCES})
run_static_analyzer(g++ "${g++_ARGS}" sa-g++-effc++.txt)

set(sloccount_ARGS ${CMAKE_SOURCE_DIR})
run_static_analyzer(sloccount "${sloccount_ARGS}" sa-sloccount.txt)

add_custom_target(static-analyses DEPENDS ${RESULTS})
