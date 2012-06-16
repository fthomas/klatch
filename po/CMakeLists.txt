file(GLOB PO_FILES *.po)
gettext_create_translations(klatch.pot ALL ${PO_FILES})

add_custom_target(dummy SOURCES klatch.pot ${PO_FILES})
