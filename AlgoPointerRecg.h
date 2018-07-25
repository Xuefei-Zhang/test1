#ifndef ALGO_POINTERECOG_H
#define ALGO_POINTERECOG_H

#if defined(_WIN32)
#ifdef POINTERRECOG_EXPORTS
#define DLL_ALGO_API __declspec(dllexport)
#else
#define DLL_ALGO_API __declspec(dllimport)
#endif
#else
#define DLL_ALGO_API
#endif

#include"Function.h"
#include<time.h>

#ifdef _WIN32

	extern "C" DLL_ALGO_API int __stdcall PointerRec(char* Image_Path, char* Model_Path, float& WYB_data, float WYB_Area[8]);
#else

	int  PointerRec(char* Image_Path, char* Model_Path, float& WYB_data, float WYB_Area[8]);

#endif // WIN32




#endif
