add_executable(PhysicsTest "PhysicsTest.cpp")

add_test(
	NAME PhysicsTest
	COMMAND PhysicsTest
)

target_link_libraries(PhysicsTest PUBLIC gtest_main)