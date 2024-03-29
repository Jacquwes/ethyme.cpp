﻿cmake_minimum_required (VERSION 3.8)

project ("ethyme.cpp")

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(websocketpp CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
 find_package(cppcoro CONFIG REQUIRED)

find_path(BOOST_RANDOM_INCLUDE_DIR boost/cxx11_char_types.hpp)
if(WIN32)
find_library(BOOST_RANDOM_LIBRARY boost_random-vc140-mt.lib)
else()
find_library(BOOST_RANDOM_LIBRARY libboost_random.a)
endif()
include_directories(${BOOST_RANDOM_INCLUDE_DIR})
link_libraries(${BOOST_RANDOM_LIBRARY})

add_library (${PROJECT_NAME}
	"include/common.hpp"
	"include/constants.hpp"

	"src/commands/command.cpp"

	"src/collections/collection.cpp"

	"src/structures/channels/channel.cpp"
	"src/structures/channels/directmessage.cpp"
	"src/structures/channels/groupdirectmessage.cpp"
	"src/structures/channels/guildcategory.cpp"
	"src/structures/channels/guildchannel.cpp"
	"src/structures/channels/guildnews.cpp"
	"src/structures/channels/guildstore.cpp"
	"src/structures/channels/guildtext.cpp"
	"src/structures/channels/guildvoice.cpp"
	"src/structures/channels/textchannel.cpp"
	"src/structures/entity.cpp"
	"src/structures/guild.cpp"
	"src/structures/member.cpp"
	"src/structures/mentions.cpp"
	"src/structures/message.cpp"
	"src/structures/role.cpp"
	"src/structures/snowflake.cpp"
	"src/structures/user.cpp"

	"src/client.cpp"
	"src/commandhandler.cpp"
	"src/logger.cpp"
	"src/websocketmessage.cpp"

	"src/events/messagecreate.cpp"
	"src/events/ready.cpp"
	"src/events/guildcreate.cpp"
 "include/structures/exception.hpp")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME} PRIVATE "./include")

target_link_libraries(${PROJECT_NAME} PRIVATE cppcoro)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE websocketpp::websocketpp)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)


project("example")

add_executable (${PROJECT_NAME}
	"example.cpp"
	"commands/channel.hpp"
	"commands/greet.hpp"
	"commands/guilds.hpp"
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

include_directories("./include")

target_link_libraries(${PROJECT_NAME} PRIVATE ethyme.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE cppcoro)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json nlohmann_json::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE websocketpp::websocketpp)
