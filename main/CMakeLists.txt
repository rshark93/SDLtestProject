set(MAIN_TARGET_NAME ${PROJECT_NAME}Main)
set(srcPath ../src/)
set(incPath ../hdr/)
set(SDL2_INCLUDE_DIRS ../../SDL2-2.0.16/include/)
set(SDL2_IMAGE_INCLUDE_DIRS ../../SDL2_image-2.0.5/include/)

if(WIN32)
    set(SDL2_LIBRARIES ../../../SDL2-2.0.16/lib/x64/SDL2)
    set(SDL2_IMAGE ../../../SDL2_image-2.0.5/lib/x64/SDL2_image)

endif()

find_file(SDL2_INCLUDE_DIRS NAME SDL.h HINTS SDL2)
find_library(SDL2_LIBRARY NAME SDL2) 

add_executable( ${MAIN_TARGET_NAME} 
    "main.cpp" "main.h" ${incPath}logger.h
    ${srcPath}Widget.cpp ${incPath}Widget.h
    ${srcPath}WidgetContainer.cpp ${incPath}WidgetContainer.h
    ${srcPath}Button.cpp ${incPath}Button.h
    ${srcPath}Image.cpp ${incPath}Image.h
    ${srcPath}MCore.cpp ${incPath}MCore.h
    ${srcPath}STexture.cpp ${incPath}STexture.h
)

target_include_directories(${MAIN_TARGET_NAME} PRIVATE "../src" "../hdr" "../img" 
    ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(${MAIN_TARGET_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE})