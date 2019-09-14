#pragma once

// This is a convenient way of building and loading an IMPLICITLY linked DLL.
// This header file can be used twice! (DLL source and then declarations for the client).
// In the library project simply define 'BUILDING_DLL' and then the functions get exported.
#ifdef BUILDING_DLL
#  define DLLAPI  __declspec(dllexport)
#else
#  define DLLAPI  __declspec(dllimport)
#endif

void DLLAPI printHello();