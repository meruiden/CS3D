# CMake entry point
cmake_minimum_required(VERSION 3.0)
project (project)

find_package(OpenGL REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -pedantic -O2 -g -pg")
	set(CMAKE_CXX_FLAGS "-Wall -Wstrict-aliasing -std=c++0x -O2")

	set(CMAKE_CXX_FLAGS "-Wall -pthread")
	set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11 ")
endif(UNIX)

if(WIN32)
	add_definitions(
		-D_SCL_SECURE_NO_WARNINGS
	)
endif(WIN32)
add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_subdirectory(external/glfw-3.2.1)
add_subdirectory(external/glm)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE
	external/glew-2.0.0/src/glew.c
)

add_library( GLEW_200 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_200
	${OPENGL_LIBRARY}
)

############

### SOIL ###

set(SOIL_SOURCE
	external/soil/src/image_DXT.c
	external/soil/src/image_DXT.h
	external/soil/src/image_helper.c
	external/soil/src/image_helper.h
	external/soil/src/SOIL.c
	external/soil/src/SOIL.h
	external/soil/src/stbi_DDS_aug.h
	external/soil/src/stbi_DDS_aug_c.h
	external/soil/src/stb_image_aug.c
	external/soil/src/stb_image_aug.h
)

add_library(soil STATIC
	${SOIL_SOURCE}
)

############

include_directories(
	external/glew-2.0.0/include
	external/glfw-3.2.1/include
	external/glm
	external/soil/src
	cs3d
)


set(ALL_LIBS
	${OPENGL_LIBRARIES}
	soil
	glfw
	GLEW_200
)

add_library(cs3d SHARED
	cs3d/engine/renderer.cpp
	cs3d/engine/renderer.h
	cs3d/engine/shader.cpp
	cs3d/engine/shader.h
	cs3d/engine/mesh.cpp
	cs3d/engine/mesh.h
	cs3d/engine/entity.cpp
	cs3d/engine/entity.h
	cs3d/engine/scene.cpp
	cs3d/engine/scene.h
	cs3d/engine/scenemanager.cpp
	cs3d/engine/scenemanager.h
	cs3d/engine/material.cpp
	cs3d/engine/material.h
	cs3d/engine/texture.cpp
	cs3d/engine/texture.h
	cs3d/engine/defaultmaterial.cpp
	cs3d/engine/defaultmaterial.h
	cs3d/engine/objloader.cpp
	cs3d/engine/objloader.h
	cs3d/engine/resourcemanager.cpp
	cs3d/engine/resourcemanager.h
	cs3d/engine/stringutils.h
	cs3d/engine/light.cpp
	cs3d/engine/light.h
	cs3d/engine/input.cpp
	cs3d/engine/input.h
	cs3d/engine/keycode.h
	cs3d/engine/cs3d.h
	cs3d/engine/camera.cpp
	cs3d/engine/camera.h
	cs3d/engine/dylibhandle.h
)

target_link_libraries(cs3d
	${ALL_LIBS}
)

add_executable(project
	cs3d/project/main.cpp
	cs3d/project/mainscene.cpp
	cs3d/project/mainscene.h
)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT project)

target_link_libraries(project
	cs3d
)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(project
		-lGL
	)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Xcode and Visual working directories
#set_target_properties(project PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/project/“)
#create_target_launcher(project WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/project/“)


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
#add_custom_command(
#   TARGET project POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/project${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/project/“
#)
elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )


# Copy assets to the build directory
file(
	COPY cs3d/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY cs3d/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
