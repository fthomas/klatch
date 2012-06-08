file(GLOB PO_FILES *.po *.pot)
add_custom_target(dummy SOURCES ${PO_FILES})
