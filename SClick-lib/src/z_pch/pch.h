#pragma once

#include <iostream>
#include <cassert>

#include <vector>
#include <unordered_map>
#include <tuple>
#include <cstdint>
#include <string>
//#include <sstream>
// 
//#include <algorithm>
#include <functional>
#include <chrono>

#if WINDOWS
#include <windows.h>
#include <stringapiset.h>
#include <d2d1.h>
#include <d3d11_1.h>
#include <d2d1_1.h>
#endif

#if LINUX
#include <wayland-client.h>
#endif
