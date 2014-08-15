#Get together the sources
file(GLOB module_sources *.cxx)
file(GLOB module_headers *.h)

#Make the library
add_library(ProtiumAll SHARED ${module_sources} ${module_headers})
target_link_libraries(ProtiumAll ProtiumAllocation ProtiumDesign ProtiumThreads ProtiumSingleton ProtiumUtilities)
set_target_properties(ProtiumAll PROPERTIES LINKER_LANGUAGE CXX)
install(TARGETS ProtiumAll DESTINATION lib EXPORT ProtiumConfig)

#Install Headers
install(FILES ${module_headers} DESTINATION include/Protium/Allocation)

