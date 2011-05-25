if (UNIX)
	set(CMAKE_MODULE_PATH "/usr/lib/OGRE/cmake/;${CMAKE_MODULE_PATH}")
endif (UNIX)

find_package(OGRE REQUIRED)
find_package(OIS REQUIRED)

#find_package(PkgConfig)
#pkg_check_modules(CLAM REQUIRED clam_audioio clam_processing clam_core)
#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${CLAM_CFLAGS} ${CLAM_CFLAGS_OTHER})
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CLAM_CFLAGS} ${CLAM_CFLAGS_OTHER})
#message(STATUS ${CLAM_INCLUDE_DIRS})

set(AUDIO_LIB_FILES
)

set(AUDIO_BIN_FILES
	AudioPlayer.cpp
	TestMonitor.cpp
	SpectrumXMLWriter.cpp
)

set(OGRE_LIB_FILES
)

set(OGRE_BIN_FILES
	main.cpp
	AdvancedOgreFramework.cpp
	AppStateManager.cpp
	DemoApp.cpp
	DotSceneLoader.cpp
	GameState.cpp
	Map.cpp
	MenuState.cpp
	PauseState.cpp
	Player.cpp
)

# explicitly include headers for Visual Studio
if (WIN32)
	set(AUDIO_LIB_FILES ${AUDIO_LIB_FILES}
	)

	set(AUDIO_BIN_FILES ${AUDIO_BIN_FILES}
		TestMonitor.hpp
		TestDataSource.hpp
		SpectrumXMLWriter.hpp
	)

	set(OGRE_LIB_FILES ${OGRE_LIB_FILES}
	)

	set(OGRE_BIN_FILES ${OGRE_BIN_FILES}
		AdvancedOgreFramework.hpp
		AppState.hpp
		AppStateManager.hpp
		DemoApp.hpp
		DotSceneLoader.hpp
		GameState.hpp
		Map.hpp
		MenuState.hpp
		PauseState.hpp
		Player.hpp
		rapidxml.hpp
	)
endif (WIN32)

include_directories(${OGRE_INCLUDE_DIRS} ${OIS_INCLUDE_DIRS})

#add_library(rauschaudio STATIC ${AUDIO_LIB_FILES})
#add_executable(rauschplayer ${AUDIO_BIN_FILES})
add_executable(rauschgame ${OGRE_BIN_FILES} ${AUDIO_BIN_FILES})

#target_link_libraries(rauschplayer clam_processing clam_audioio clam_core)
target_link_libraries(rauschgame ${OGRE_LIBRARIES} OgreTerrain ${OIS_LIBRARIES} clam_processing clam_audioio clam_core)
