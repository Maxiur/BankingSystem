cmake_minimum_required(VERSION 3.19)
project(BankApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/Paczka")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_compile_options(-Wall -Wextra -Wpedantic)

include_directories("./include")

file(GLOB_RECURSE SOURCE_FILES "./src/*.cpp")
file(GLOB_RECURSE HEADER_FILES "./include/*.h" "./include/*.hpp")
file(GLOB_RECURSE UI_FILES "./ui/*.ui")

qt_add_executable(${PROJECT_NAME}
    WIN32 MACOSX_BUNDLE
    ${SOURCE_FILES}
    ${HEADER_FILES}
    ${UI_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOUIC_SEARCH_PATHS "ui")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})