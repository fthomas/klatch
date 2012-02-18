get_target_property(klatch_SOURCE_DIR   klatch klatch_SOURCE_DIR)
get_target_property(klatch_SOURCES      klatch klatch_SOURCES)
get_target_property(klatch_HEADERS      klatch klatch_HEADERS)
get_target_property(klatch_UIS          klatch klatch_UIS)
get_target_property(klatch_INCLUDE_DIRS klatch klatch_INCLUDE_DIRS)
get_target_property(klatch_LIBRARIES    klatch klatch_LIBRARIES)
list(REMOVE_ITEM klatch_SOURCES "${klatch_SOURCE_DIR}/main.cpp")

set(ut_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/Matches_t.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/string_t.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

set(ut_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/Matches_t.h
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/string_t.h)

kde4_add_ui_files(klatch_GENERATED_UIS ${klatch_UIS})

set(ut_ALL_SOURCES
  ${ut_SOURCES}
  ${ut_HEADERS}
  ${klatch_SOURCES}
  ${klatch_HEADERS}
  ${klatch_UIS}
  ${klatch_GENERATED_UIS})

set(ut_INCLUDE_DIRS
  ${klatch_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR})

set(ut_LIBRARIES
  ${klatch_LIBRARIES}
  ${QT_QTTEST_LIBRARY})

include_directories(${ut_INCLUDE_DIRS})
kde4_add_unit_test(ut TESTNAME unit_tests ${ut_ALL_SOURCES})
target_link_libraries(ut ${ut_LIBRARIES})

if(CMAKE_COMPILER_IS_GNUCXX)
    add_custom_command(TARGET ut PRE_BUILD
      COMMAND find ${CMAKE_CURRENT_BINARY_DIR} -name *.gcda -delete)

    set_target_properties(ut PROPERTIES
      COMPILE_FLAGS "--coverage -g -O0"
      LINK_FLAGS "--coverage")

    find_program(LCOV_EXEC lcov)
    find_program(GENHTML_EXEC genhtml)
    if(LCOV_EXEC AND GENHTML_EXEC)
        set(COVERAGE_OUTFILE ${CMAKE_CURRENT_BINARY_DIR}/coverage.info)
        add_custom_target(lcov
          COMMAND ${LCOV_EXEC}
            --zerocounters
            --directory ${CMAKE_CURRENT_BINARY_DIR}
          COMMAND ${CMAKE_CURRENT_BINARY_DIR}/ut
          COMMAND ${LCOV_EXEC}
            --capture
            --directory ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/ut.dir/
            --base-directory ${CMAKE_SOURCE_DIR}
            --output-file ${COVERAGE_OUTFILE}
          COMMAND ${LCOV_EXEC}
            --extract ${COVERAGE_OUTFILE} "${klatch_SOURCE_DIR}/\\*"
            --output-file ${COVERAGE_OUTFILE}
          COMMAND ${GENHTML_EXEC}
            --output-directory ${CMAKE_CURRENT_SOURCE_DIR}/lcov-report
            --prefix ${CMAKE_SOURCE_DIR}
            --legend --demangle-cpp --title ${CMAKE_PROJECT_NAME}
            ${COVERAGE_OUTFILE}
          DEPENDS ut
          WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    endif()
endif()
