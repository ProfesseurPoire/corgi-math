project(corgi-math_tests)

add_executable(${PROJECT_NAME}
	main_test.cpp
	ut_matrix.cpp
	ut_vec2.cpp
	ut_vec3.cpp
	ut_vec4.cpp
	ut_collisions.cpp
	benchmarks.cpp
)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)

find_package(corgi-test)

target_link_libraries(${PROJECT_NAME}  PUBLIC
	corgi-math
	corgi-test
)

add_test(NAME ${PROJECT_NAME}  COMMAND ${PROJECT_NAME} )
