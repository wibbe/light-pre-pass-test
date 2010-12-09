
SET(SOURCE
  Main.cpp
  Utils.cpp
  HotValue.cpp
  Mesh.cpp
  
  # SOIL Library
  SOIL/image_DXT.c
  SOIL/SOIL.c
  SOIL/stb_image_aug.c
  SOIL/image_helper.c

  # Glew library
  glew-1.5.7/src/glew.c
)


SET(NAME light_pre_pass)

IF (APPLE AND "${CMAKE_BUILD_TYPE}" EQUAL Release)
  SET(NAME LightPrePass)
  ADD_EXECUTABLE(${NAME} MACOSX_BUNDLE ${SOURCE})
ELSE()
  ADD_EXECUTABLE(${NAME} ${SOURCE})
ENDIF()

TARGET_LINK_LIBRARIES(${NAME} ${LIBRARIES})
