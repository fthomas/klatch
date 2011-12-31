configure_file(KlatchData.cpp.in
  ${CMAKE_CURRENT_SOURCE_DIR}/KlatchData.cpp)

set(klatch_SRCS
    KlatchData.cpp
    KlatchData.cpp.in
    MainWindow.cpp
    main.cpp)

set(klatch_INCLUDE_DIRS
    ${KDE4_INCLUDES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})

set(klatch_LIBRARIES
    ${KDE4_KDEUI_LIBS})

kde4_add_ui_files(klatch_SRCS
    MainWindow.ui)

include_directories(${klatch_INCLUDE_DIRS})
kde4_add_executable(klatch ${klatch_SRCS})
target_link_libraries(klatch ${klatch_LIBRARIES})

install(TARGETS klatch ${INSTALL_TARGETS_DEFAULT_ARGS})
