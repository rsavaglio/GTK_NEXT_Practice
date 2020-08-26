#pragma once

#if _DEBUG == 1
	#define ASSERT(x) if (!(x)) __debugbreak();
#else
	#define ASSERT(x)
#endif
