set(SFML_BUILD_AUDIO OFF)
set(SFML_BUILD_DOC OFF)
set(SFML_BUILD_EXAMPLES OFF)
set(SFML_BUILD_GRAPHICS ON)
set(SFML_BUILD_NETWORK OFF)
set(SFML_BUILD_WINDOW ON)

add_subdirectory(SFML)

cmake_path(SET sfmlFontPath "${CMAKE_CURRENT_SOURCE_DIR}/NotoSans/fonts/otf/unhinted/instance_otf/NotoSans-Regular.otf")

add_library(sfmlFont INTERFACE)
target_compile_definitions(sfmlFont
INTERFACE
    SFML_FONT_PATH="${sfmlFontPath}"
)

add_subdirectory(googletest)
include(CTest)

