include_directories (${QC_TO_XML_SOURCE_DIR}/qc_to_xml) 

link_directories (${QC_TO_XML_BINARY_DIR}/qc_to_xml) 

add_executable (qc_to_xml Entry.cpp Entry.h Groups.cpp Groups.h main.cpp QCParser.cpp QCParser.h)  
