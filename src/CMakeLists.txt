configure_file(KlatchData.cpp.in KlatchData.cpp)

set(klatch_SOURCES
    dict/Definition.cpp
    dict/DictClient.cpp
    utility/stream.cpp
    utility/string.cpp
    KlatchData.cpp.in
    LookupWidget.cpp
    MainWindow.cpp
    main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/KlatchData.cpp)

set(klatch_HEADERS
    dict/Definition.h
    dict/DictClient.h
    dict/codes.h
    utility/stream.h
    utility/string.h
    KlatchData.h
    LookupWidget.h
    MainWindow.h)

set(klatch_UIS
    LookupWidget.ui)

set(klatch_RCS
    klatchui.rc)

set(klatch_ALL_SOURCES
    ${klatch_SOURCES}
    ${klatch_HEADERS}
    ${klatch_UIS}
    ${klatch_RCS})

set(klatch_INCLUDE_DIRS
    ${KDE4_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

set(klatch_LIBRARIES
    ${KDE4_KDEUI_LIBS}
    ${QT_QTNETWORK_LIBRARY})

include_directories(${klatch_INCLUDE_DIRS})
kde4_add_ui_files(klatch_SOURCES ${klatch_UIS})
kde4_add_executable(klatch ${klatch_ALL_SOURCES})
target_link_libraries(klatch ${klatch_LIBRARIES})

install(TARGETS klatch ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES klatchui.rc DESTINATION ${DATA_INSTALL_DIR}/klatch)
