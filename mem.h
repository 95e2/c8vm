//
// Created by urain39 on 18-9-16.
//

#ifndef C8VM_MEM_H
#define C8VM_MEM_H

#include <stdint.h>


/**
 * ZP    　0x0000~0x00FF      256
 * 未使用　　0x0100~0x0FFF     3840
 * 显示内存　0x1000~0x1FFF     4096 (4K)
 * 未使用   0x2000~0x6FFF     16384 (20K)
 * 栈 　  　0x7000～0x7FFF    4096 (4K)
 * ROM　 　0x8000~0xFFFF    32768 (32K)
 *
 * 其中0x00FE表示按键映射，0x00FF表示随机数
 */

#define MEM_SIZE        0x10000
#define DIPLAY_SIZE     0x1000
#define DISPLAY_BEGIN   0x1000
#define ROM_BEGIN       0x8000
#define STACK_SIZE      0x1000
#define STACK_BEGIN     0x6000
#define ROM_MAXSIZE     0x7000

typedef uint8_t mem_t;

void mem_init(void);

#endif //C8VM_MEM_H
