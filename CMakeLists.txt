cmake_minimum_required(VERSION 3.26.3)
project(Tempest VERSION 0.1.0)
add_executable(Tempest main.c glad.c image.c shader.c game.c scene.c renderer.c camera.c)

add_subdirectory(vendor/glfw)

target_link_libraries(${PROJECT_NAME}
	PRIVATE glfw)

target_include_directories(${PROJECT_NAME}
	PUBLIC ./vendor/cgltf/include
	PUBLIC ./vendor/cglm/include
	PUBLIC ./vendor/glad/include
	PUBLIC ./vendor/glfw/include)

