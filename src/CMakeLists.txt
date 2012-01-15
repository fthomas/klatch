set(CSD ${CMAKE_CURRENT_SOURCE_DIR})
set(CBD ${CMAKE_CURRENT_BINARY_DIR})

configure_file(KlatchData.cpp.in KlatchData.cpp)

set(klatch_SOURCES
    ${CSD}/dict/Definition.cpp
    ${CSD}/dict/DictClient.cpp
    ${CSD}/dict/Matches.cpp
    ${CSD}/utility/stream.cpp
    ${CSD}/utility/string.cpp
    ${CBD}/KlatchData.cpp
    ${CSD}/KlatchData.cpp.in
    ${CSD}/LookupWidget.cpp
    ${CSD}/MainWindow.cpp
    ${CSD}/main.cpp)

set(klatch_HEADERS
    ${CSD}/dict/Definition.h
    ${CSD}/dict/DictClient.h
    ${CSD}/dict/Matches.h
    ${CSD}/dict/codes.h
    ${CSD}/utility/stream.h
    ${CSD}/utility/string.h
    ${CSD}/KlatchData.h
    ${CSD}/LookupWidget.h
    ${CSD}/MainWindow.h)

set(klatch_UIS
    ${CSD}/LookupWidget.ui)

set(klatch_RCS
    ${CSD}/klatchui.rc)

kde4_add_ui_files(klatch_GENERATED_UIS ${klatch_UIS})

set(klatch_ALL_SOURCES
    ${klatch_SOURCES}
    ${klatch_HEADERS}
    ${klatch_UIS}
    ${klatch_RCS}
    ${klatch_GENERATED_UIS})

set(klatch_INCLUDE_DIRS
    ${KDE4_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

set(klatch_LIBRARIES
    ${KDE4_KDEUI_LIBS}
    ${QT_QTNETWORK_LIBRARY})

include_directories(${klatch_INCLUDE_DIRS})
kde4_add_executable(klatch ${klatch_ALL_SOURCES})
target_link_libraries(klatch ${klatch_LIBRARIES})
set_target_properties(klatch PROPERTIES
  klatch_SOURCES "${klatch_SOURCES}"
  klatch_HEADERS "${klatch_HEADERS}"
  klatch_INCLUDE_DIRS "${klatch_INCLUDE_DIRS}")

install(TARGETS klatch ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES klatchui.rc DESTINATION ${DATA_INSTALL_DIR}/klatch)
