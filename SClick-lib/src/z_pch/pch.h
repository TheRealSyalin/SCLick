#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

#if WINDOWS
#include <windows.h>
#include <stringapiset.h>
#include <d2d1.h>

#endif

#if LINUX
#include <Xlib.h>
#endif
