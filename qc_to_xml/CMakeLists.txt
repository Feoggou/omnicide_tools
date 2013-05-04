set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package( Boost 1.53.0 COMPONENTS date_time filesystem system REQUIRED)

if(Boost_FOUND)
   include_directories (${Boost_INCLUDE_DIRS} ${QC_TO_XML_SOURCE_DIR}/qc_to_xml) 
   link_directories (${QC_TO_XML_BINARY_DIR}/qc_to_xml)

   add_executable (qc_to_xml Entry.cpp Entry.h Groups.cpp Groups.h main.cpp QCParser.cpp QCParser.h)  
   target_link_libraries(qc_to_xml ${Boost_LIBRARIES})
endif() 
