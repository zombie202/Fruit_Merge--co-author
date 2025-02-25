# Mateusz Zalewski, Dariusz Wroblewski, Kamil Troszczynski, Karol Pieczka
cmake_minimum_required(VERSION 3.16)
project("FruitMerge")

set(CMAKE_CXX_STANDARD 20)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Include directories
include_directories(PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Add executable with all source files
add_executable(Main
    source/main.cpp
    source/Game.cpp
    source/graphics/Menu.cpp
    source/core/Board.cpp
    source/core/Ball.cpp
    source/fruits/Fruit.cpp
    source/graphics/UiManager.cpp 
    source/EventHandler.cpp 
    source/graphics/GameWindow.cpp
    source/RankingManager.cpp
    source/graphics/ExitWindow.cpp
    source/graphics/Cloud.cpp
    source/SoundManager.cpp
    source/graphics/FinalWindow.cpp
    source/graphics/Progressbar.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Main PROPERTY CXX_STANDARD 20)
endif()

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
# Add gtest library and enabling linking
enable_testing()
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Add SFML library and enabling linking
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

# Link SFML libraries
target_link_libraries(Main PUBLIC sfml-graphics sfml-window sfml-system sfml-audio)

add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
)
add_dependencies(Main copy_assets)

# Add subdirectories
add_subdirectory(tests)
