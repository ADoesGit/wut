#pragma once
#include <wut.h>
#include "memheap.h"

/**
 * \defgroup coreinit_memexpheap Expanded Heap
 * \ingroup coreinit
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MEMExpHeap MEMExpHeap;
typedef struct MEMExpHeapBlock MEMExpHeapBlock;
typedef struct MEMExpHeapBlockList MEMExpHeapBlockList;

typedef void (*MEMExpHeapBlockVisitor)(void *block, MEMHeapHandle heap,
                                       void *context);

typedef enum MEMExpHeapMode
{
   MEM_EXP_HEAP_MODE_FIRST_FREE     = 0,
   MEM_EXP_HEAP_MODE_NEAREST_SIZE   = 1,
} MEMExpHeapMode;

typedef enum MEMExpHeapDirection
{
   MEM_EXP_HEAP_DIR_FROM_TOP        = 0,
   MEM_EXP_HEAP_DIR_FROM_BOTTOM     = 1,
} MEMExpHeapDirection;

struct MEMExpHeapBlock
{
   uint32_t attribs;
   uint32_t blockSize;
   MEMExpHeapBlock *prev;
   MEMExpHeapBlock *next;
   uint16_t tag;
   UNKNOWN(0x02);
};
CHECK_OFFSET(MEMExpHeapBlock, 0x00, attribs);
CHECK_OFFSET(MEMExpHeapBlock, 0x04, blockSize);
CHECK_OFFSET(MEMExpHeapBlock, 0x08, prev);
CHECK_OFFSET(MEMExpHeapBlock, 0x0c, next);
CHECK_OFFSET(MEMExpHeapBlock, 0x10, tag);
CHECK_SIZE(MEMExpHeapBlock, 0x14);

struct MEMExpHeapBlockList
{
   MEMExpHeapBlock *head;
   MEMExpHeapBlock *tail;
};
CHECK_OFFSET(MEMExpHeapBlockList, 0x00, head);
CHECK_OFFSET(MEMExpHeapBlockList, 0x04, tail);
CHECK_SIZE(MEMExpHeapBlockList, 0x08);

struct MEMExpHeap
{
   MEMHeapHeader header;
   MEMExpHeapBlockList freeList;
   MEMExpHeapBlockList usedList;
   uint16_t groupId;
   uint16_t attribs;
};
CHECK_OFFSET(MEMExpHeap, 0x00, header);
CHECK_OFFSET(MEMExpHeap, 0x40, freeList);
CHECK_OFFSET(MEMExpHeap, 0x48, usedList);
CHECK_OFFSET(MEMExpHeap, 0x50, groupId);
CHECK_OFFSET(MEMExpHeap, 0x52, attribs);
CHECK_SIZE(MEMExpHeap, 0x54);

MEMHeapHandle
MEMCreateExpHeapEx(void *heap,
                   uint32_t size,
                   uint16_t flags);

void *
MEMDestroyExpHeap(MEMHeapHandle heap);

void *
MEMAllocFromExpHeapEx(MEMHeapHandle heap,
                      uint32_t size,
                      int alignment);

void
MEMFreeToExpHeap(MEMHeapHandle heap,
                 void *block);

MEMExpHeapMode
MEMSetAllocModeForExpHeap(MEMHeapHandle heap,
                          MEMExpHeapMode mode);

MEMExpHeapMode
MEMGetAllocModeForExpHeap(MEMHeapHandle heap);

uint32_t
MEMAdjustExpHeap(MEMHeapHandle heap);

uint32_t
MEMResizeForMBlockExpHeap(MEMHeapHandle heap,
                          void *block,
                          uint32_t size);

uint32_t
MEMGetTotalFreeSizeForExpHeap(MEMHeapHandle heap);

uint32_t
MEMGetAllocatableSizeForExpHeapEx(MEMHeapHandle heap,
                                  int alignment);

uint16_t
MEMSetGroupIDForExpHeap(MEMHeapHandle heap,
                        uint16_t id);

uint16_t
MEMGetGroupIDForExpHeap(MEMHeapHandle heap);

uint32_t
MEMGetSizeForMBlockExpHeap(void *block);

uint16_t
MEMGetGroupIDForMBlockExpHeap(void *block);

MEMExpHeapDirection
MEMGetAllocDirForMBlockExpHeap(void *block);

void
MEMVisitAllocatedForExpHeap(MEMHeapHandle heap,
                            MEMExpHeapBlockVisitor callback,
                            void *context);

#ifdef __cplusplus
}
#endif

/** @} */
