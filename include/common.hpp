#pragma once

#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "cpr/cpr.h"
#include "nlohmann/json.hpp"
#include "websocketpp/config/asio_client.hpp"
#include "websocketpp/client.hpp"

#define DefineClient namespace Ethyme { class Client; }
#define ClientMembers private: std::shared_ptr<Ethyme::Client> m_client; public: const std::shared_ptr<Ethyme::Client>& Client() const;
#define Client_ const std::shared_ptr<Ethyme::Client>& client