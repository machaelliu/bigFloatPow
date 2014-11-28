#ifndef _DEBUG_H_
#define _DEBUG_H_

// 程序中可能需要将 DEBUG 定义为某个值，因而去除先前的定义
#ifdef DEBUG
#undef DEBUG
#endif

#define DEBUG

#ifdef DEBUG
#define private public
#endif
#endif
