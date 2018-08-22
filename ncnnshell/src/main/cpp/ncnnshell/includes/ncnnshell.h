//
// Created by Administrator on 2018/8/21.
//

#ifndef NCNNDEMO3_NCNNSHELL_H
#define NCNNDEMO3_NCNNSHELL_H

#include <string>
#include <android/bitmap.h>

#ifdef __cplusplus
extern "C" {
#endif

char* ncnnShell_DebugInterface(unsigned char* param, unsigned char* bin, char*repot);

char*  ncnnShell_Init(unsigned char* param, unsigned char* bin, char*repot);

char* ncnnShell_DetectSSD(int h, int w, void* bitmapData, char*repot);

#ifdef __cplusplus
}
#endif

#endif //NCNNDEMO3_NCNNSHELL_H
