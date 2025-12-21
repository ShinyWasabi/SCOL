#pragma once

#include <AsyncLogger/Logger.hpp>
#include <MinHook.h>
#include <Windows.h>
#include <array>
#include <atomic>
#include <chrono>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string_view>
#include <thread>
#include <unordered_set>
#include <vector>

using namespace al;
#include "Logging.hpp"
#include "Settings.hpp"
#include "util/Joaat.hpp"

namespace SCOL
{
    using namespace std::chrono_literals;
}