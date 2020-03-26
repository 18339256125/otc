﻿#pragma once

#include "Utils.h"

//Unknown rva.
#define SEGMENT_LIBRARY_RVA 0x2A6900
//The size of the original table. (The value was taken from the crack)
#define SEGMENT_INFO_TABLE_SIZE 0x18C
//The offset of the function to be intercepted. (Offset taken from the segment)
#define SEGMENT_FUNCTION_HOOK_RVA 0x3B30

//Legacy segment function.
typedef int (__fastcall *OriginalFunctionHook) (int* vTable, int index);
//A variable that indicates the original function from the hook.
static OriginalFunctionHook g_OriginalFunctionHookCaller;

class SegmentUtils {

public:

    /**
     * Used to initialize internal values ​​in segment. (About values: SegmentUtils.cpp)
     *
     * @param pointer - A pointer to the allocated memory for the segment.
     * @param nick - Player nickname in watermark (!32 character limit!)
     **/

     void CreateInfoTable (DWORD pointer, const char* nick);

    /**
     * It is necessary for the internal functions to work correctly. (More about netvars can be found on unknowncheats)
     *
     * @param pointer - A pointer to the allocated memory for the segment.
     **/

     void UpdateNetVars (DWORD pointer);

    /**
     * Intercept legacy function from the segment and replace it with your own. (About hook/lib: https://www.github.com/HoShiMin/HookLib)
     *
     * @param pointer - A pointer to the allocated memory for the segment.
     **/

     void CreateHook (DWORD pointer);

    //Legacy segment custom function.
    //Used to repair indexes that are broken. About vfunction: SegmentUtils.cpp
    static int __fastcall CustomFunctionHook(int* vTable, int index) {
        if (index >= 89) {
            index += 2;
            if (index >= 256) index++;
            if (index >= 300) index += 2;
            if (index >= 300) index++;
        }
       return g_OriginalFunctionHookCaller (vTable, index);
    }

protected:

    //Netvars are offsets to parent variables in valve sdk.
    struct NetVar {
        //Offset to variable.
        int rva;
        //Set value.
        int new_value;
    };
   
    //It is necessary for correct work.
    std::vector<NetVar> m_netvars = {
       //m_IsScope.
       NetVar ({ 0x95A250, 0x3914 })
    };

    //It is necessary for correct work.
    std::vector<const char*> m_libraries = {
       "client_panorama.dll",
       "vguimatsurface.dll",
       "shaderapidx9.dll",
       "vstdlib.dll"
    };

    //It is necessary for correct work.
    //TODO: Auto-Update.
    std::vector<DWORD> m_offsets = {
       0x900240, 0x3f1780, 0x1cef50, 0x1cf110, 0x2e8ab3, 0x1bdf50, 0x30a990, 0x298ac1, 0x3a3620, 0x3a4060, 0x1d6410, 0x3a2c20,
       0x3783ed, 0x34f779, 0x3a5a05, 0x2fedc1, 0x240e8e, 0x67ef3f, 0x3db830, 0x3b1a4c, 0x38e440, 0x38e497, 0x3e2690, 0x34af09,
       0x2ac270, 0x4b9a30, 0x254268, 0x4be890, 0x377b55, 0x4fa8e0, 0x3a3684, 0x1b612c, 0x1b8125, 0x1b7e39, 0x19cd00, 0x21bd20,
       0x6b5d00, 0x1ef1c0, 0x19d690, 0x617d90, 0x24d570, 0x1cf2c0, 0x194810, 0x1cfbd0 ,0x3f643f, 0x7122e0, 0x711c30, 0x1b7e20,
       0x3f20f0, 0x3f63b0, 0x19d550, 0x2cba1f, 0x1c3069, 0x35302a, 0x3ca482, 0x3a3666, 0x3f63f9, 0x61774e, 0x617a20, 0x39caa8,
       0x1ce35c, 0x3c0403, 0x1b8cc0, 0x3e57a8, 0x6101dc, 0x19792d, 0x184763, 0x8f4a67, 0x2a20c7, 0x1cdfd0, 0x29b900, 0x346225,
       0x39a760, 0x60d2b8, 0x60d2c6, 0x3b1a5a, 0x38e440, 0x60d2b8, 0x60d2c6, 0x198174, 0x8f7730, 0x8f7e30, 0x24e0e7, 0x1ce3e8,
       0x33b0d0, 0x1b6a30
    };

};