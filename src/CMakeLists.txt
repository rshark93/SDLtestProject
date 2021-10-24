find_package(jsoncpp CONFIG REQUIRED)


file(GLOB SdlTestProject_SRC "*.h" "*.cpp")

add_library(trait_normalizer SHARED
    "../include/tnm_API" "../../common/tdm_container.h" "../../common/tdm_logger.h" "../../common/cv.h"
    "../../common/tdm_image_struct.h" "../normalizer.json"
	${SdlTestProject_SRC}
)

if(WIN32)
    target_link_libraries(trait_normalizer PRIVATE ${OpenCV_LIBS} jsoncpp_lib_static)
else()
    target_link_libraries(trait_normalizer PRIVATE ${OpenCV_LIBS} jsoncpp_lib)
endif()

target_include_directories(trait_normalizer PUBLIC "../include" "../../common/" ${OpenCV_INCLUDE_DIRS})

set(MY_PRODUCT_NUMBER 2)
set(MY_PRODUCT_VERSION 4)
set(MY_BUILD_NUMBER 17)

set(CMAKE_VERBOSE_MAKEFILE on)

set_target_properties(trait_normalizer
    PROPERTIES OUTPUT_NAME
    trait_normalizer.${MY_PRODUCT_NUMBER}.${MY_PRODUCT_VERSION}.${MY_BUILD_NUMBER})

if(WIN32)
    ADD_CUSTOM_TARGET( trait_normalizer_link ALL
                        COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:trait_normalizer> $<TARGET_FILE_DIR:trait_normalizer>/trait_normalizer.dll
                        COMMENT "Generating TNM symbolic link" )
else()
    ADD_CUSTOM_TARGET( trait_normalizer_link ALL
                        COMMAND ${CMAKE_COMMAND} -E create_symlink $<TARGET_FILE:trait_normalizer> $<TARGET_FILE_DIR:trait_normalizer>/libtrait_normalizer.so
                        COMMENT "Generating TNM symbolic link" )
endif()

if(${BUILD_TESTS_COVERAGE})
    target_compile_options(trait_normalizer PUBLIC -fprofile-arcs -ftest-coverage)
    target_link_libraries(trait_normalizer PUBLIC gcov)
endif()

