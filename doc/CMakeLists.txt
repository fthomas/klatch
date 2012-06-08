set(MANPAGE klatch.1.docbook)
kde4_create_manpage(${MANPAGE} 1 INSTALL_DESTINATION ${MAN_INSTALL_DIR})
add_custom_target(dummy SOURCES ${MANPAGE})
