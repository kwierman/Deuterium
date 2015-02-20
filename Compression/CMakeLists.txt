#Get together the sources
file(GLOB module_sources *.cc)
file(GLOB module_headers *.hh)

#Make the library
add_library(DeuteriumCompression SHARED ${module_sources} ${module_headers})
target_link_libraries(DeuteriumCompression )
set_target_properties(DeuteriumCompression PROPERTIES LINKER_LANGUAGE CXX)


#Install Headers and CMake Config
install(TARGETS DeuteriumCompression DESTINATION lib EXPORT DeuteriumConfig)
install(FILES ${module_headers} DESTINATION include/Deuterium/Compression)

