#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(DeuteriumDataFormat SHARED ${module_sources} ${module_headers})
target_link_libraries(DeuteriumDataFormat ProtiumThreads)
set_target_properties(DeuteriumDataFormat PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS DeuteriumDataFormat DESTINATION lib EXPORT DeuteriumConfig)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Deuterium/DataFormat)

