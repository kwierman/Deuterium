file(GLOB applications *.cc)
foreach(_app ${applications})
	get_filename_component (name_without_extension ${_app} NAME_WE)
	add_executable(${name_without_extension} ${_app} )
	target_link_libraries(${name_without_extension} 
		DeuteriumFileSystem 
		DeuteriumOptions 
		DeuteriumNetworking 
		DeuteriumDataFormat
		ProtiumUtilities 
	)
	install(TARGETS ${name_without_extension} DESTINATION bin EXPORT DeuteriumConfig)
endforeach()