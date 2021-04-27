#pragma once

#pragma warning( disable : 4267 )

#define BOOST_ASIO_DISABLE_STD_COROUTINE
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include <cstring>
#include <ctime>

#include <algorithm>
#include <chrono>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <random>
#include <regex>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <variant>
#include <vector>

#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
