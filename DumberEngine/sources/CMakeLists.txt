include_directories(${CMAKE_SOURCE_DIR}/headers)

file(GLOB_RECURSE ENGINE_SOURCES *.cpp *.c)
file(GLOB_RECURSE ENGINE_HEADERS *.h *.hpp *.inl)
file(GLOB_RECURSE IMGUI_SOURCES ../../external/imgui/*.cpp)

add_executable(DumberEngine ${ENGINE_SOURCES} ${IMGUI_SOURCES} ${ENGINE_HEADERS} ../headers/systems/ISystem.hpp ../headers/Engine.hpp Engine.cpp systems/input/IInputManager.cpp)
target_link_libraries(DumberEngine glfw3 BulletCollision BulletSoftBody LinearMath BulletDynamics)
