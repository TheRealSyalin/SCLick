#pragma once

#include <iostream>
#include <functional>
#include <vector>
//#include <string>
//#include <sstream>
//#include <algorithm>
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
