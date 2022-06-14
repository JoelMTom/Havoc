cmake_minimum_required(VERSION 3.10)

Project(Havoc)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin-int/${PROJECT_NAME}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}")

set(PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}")


add_executable(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}/Main.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${CMAKE_SOURCE_DIR}"
                           )

install(TARGETS Havoc DESTINATION bin)