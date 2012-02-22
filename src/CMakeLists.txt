configure_file(KlatchData.cpp.in KlatchData.cpp)

set(klatch_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/config/DictPage.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/DatabaseInfo.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/Definition.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/DictClient.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/Matches.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/stream.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/string.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/view/DefinitionItem.cpp
  ${CMAKE_CURRENT_BINARY_DIR}/KlatchData.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/KlatchData.cpp.in
  ${CMAKE_CURRENT_SOURCE_DIR}/LookupWidget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

set(klatch_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/config/DictPage.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/DatabaseInfo.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/Definition.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/DictClient.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/Matches.h
  ${CMAKE_CURRENT_SOURCE_DIR}/dict/codes.h
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/stream.h
  ${CMAKE_CURRENT_SOURCE_DIR}/utility/string.h
  ${CMAKE_CURRENT_SOURCE_DIR}/view/DefinitionItem.h
  ${CMAKE_CURRENT_SOURCE_DIR}/KlatchData.h
  ${CMAKE_CURRENT_SOURCE_DIR}/LookupWidget.h
  ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h)

set(klatch_UIS
  ${CMAKE_CURRENT_SOURCE_DIR}/config/DictPage.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/view/DefinitionItem.ui
  ${CMAKE_CURRENT_SOURCE_DIR}/LookupWidget.ui)

set(klatch_RCS
  ${CMAKE_CURRENT_SOURCE_DIR}/klatchui.rc)

set(klatch_KCFGS
  ${CMAKE_CURRENT_SOURCE_DIR}/config/klatch.kcfg)

set(klatch_KCFGCS
  ${CMAKE_CURRENT_SOURCE_DIR}/config/klatchconfig.kcfgc)

kde4_add_ui_files(klatch_GENERATED_UIS ${klatch_UIS})

kde4_add_kcfg_files(klatch_GENERATED_KCFGCS ${klatch_KCFGCS})

set(klatch_ALL_SOURCES
  ${klatch_SOURCES}
  ${klatch_HEADERS}
  ${klatch_UIS}
  ${klatch_RCS}
  ${klatch_GENERATED_UIS}
  ${klatch_GENERATED_KCFGCS})

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
  klatch_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
  klatch_SOURCES "${klatch_SOURCES}"
  klatch_HEADERS "${klatch_HEADERS}"
  klatch_UIS "${klatch_UIS}"
  klatch_KCFGCS "${klatch_KCFGCS}"
  klatch_INCLUDE_DIRS "${klatch_INCLUDE_DIRS}"
  klatch_LIBRARIES "${klatch_LIBRARIES}")

install(TARGETS klatch ${INSTALL_TARGETS_DEFAULT_ARGS})
install(FILES ${klatch_RCS} DESTINATION ${DATA_INSTALL_DIR}/klatch)
install(FILES ${klatch_KCFGS} DESTINATION ${KCFG_INSTALL_DIR})
install(FILES klatch.desktop DESTINATION ${XDG_APPS_INSTALL_DIR})

add_custom_target(dummy SOURCES ${klatch_KCFGS} klatch.desktop)
