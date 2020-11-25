cmake_minimum_required (VERSION 3.8)

project ("ethyme.cpp")

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(websocketpp CONFIG REQUIRED)

find_path(BOOST_RANDOM_INCLUDE_DIR boost/random/random_device.h)
find_library(BOOST_RANDOM_LIBRARY boost_random-vc140-mt.lib)
include_directories(${BOOST_RANDOM_INCLUDE_DIR})
link_libraries(${BOOST_RANDOM_LIBRARY})
find_package(OpenSSL REQUIRED)

add_library (${PROJECT_NAME}
	"src/ethyme.cpp"
	
	"include/common.hpp"
	"include/constants.hpp"

	"src/structures/entity.cpp"
	"src/structures/message.cpp"
	"src/structures/user.cpp"
	"src/structures/snowflake.cpp"

	"src/client.cpp"
	"src/websocketmessage.cpp"

	"src/events/messagecreate.cpp"
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE "./include")

target_link_libraries(${PROJECT_NAME} PRIVATE cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE websocketpp::websocketpp)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)


project("example")

add_executable (${PROJECT_NAME} "example.cpp")
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME} PRIVATE "./include")

target_link_libraries(${PROJECT_NAME} PRIVATE ethyme.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE websocketpp::websocketpp)
