configure_file(KlatchData.cpp.in KlatchData.cpp)

set(CSD ${CMAKE_CURRENT_SOURCE_DIR})
set(CBD ${CMAKE_CURRENT_BINARY_DIR})

set(klatch_SOURCES
  ${CSD}/config/DictPage.cpp
  ${CSD}/config/DictServerItem.cpp
  ${CSD}/config/DictServerList.cpp
  ${CSD}/dict/ClientPool.cpp
  ${CSD}/dict/DatabaseInfo.cpp
  ${CSD}/dict/Definition.cpp
  ${CSD}/dict/DictClient.cpp
  ${CSD}/dict/Matches.cpp
  ${CSD}/results/ResultList.cpp
  ${CSD}/utility/stream.cpp
  ${CSD}/utility/string.cpp
  ${CBD}/KlatchData.cpp
  ${CSD}/KlatchData.cpp.in
  ${CSD}/LookupWidget.cpp
  ${CSD}/MainWindow.cpp
  ${CSD}/main.cpp)

set(klatch_HEADERS
  ${CSD}/config/DictPage.h
  ${CSD}/config/DictServerItem.h
  ${CSD}/config/DictServerList.h
  ${CSD}/dict/ClientPool.h
  ${CSD}/dict/DatabaseInfo.h
  ${CSD}/dict/Definition.h
  ${CSD}/dict/DictClient.h
  ${CSD}/dict/Matches.h
  ${CSD}/dict/codes.h
  ${CSD}/results/ResultList.h
  ${CSD}/utility/algorithm.h
  ${CSD}/utility/stream.h
  ${CSD}/utility/string.h
  ${CSD}/KlatchData.h
  ${CSD}/LookupWidget.h
  ${CSD}/MainWindow.h)

set(klatch_UIS
  ${CSD}/config/DictPage.ui
  ${CSD}/LookupWidget.ui)

set(klatch_RCS
  ${CSD}/klatchui.rc)

set(klatch_KCFGS
  ${CSD}/config/klatch.kcfg)

set(klatch_KCFGCS
  ${CSD}/config/klatchconfig.kcfgc)

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
