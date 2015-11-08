#ifndef PAGING_H
#define PAGING_H

#include "types.h"

typedef struct {
  unsigned long reserved1 : 3;
  unsigned long pwt       : 1;
  unsigned long pcd       : 1;
  unsigned long reserved2 : 7;
  unsigned long address   : 40;
  unsigned long reserved3 : 12;
} CR3;

typedef struct {
  unsigned long physical_offset : 12;
  unsigned long pm_l1_offset    : 9;
  unsigned long pm_l2_offset    : 9;
  unsigned long pm_l3_offset    : 9;
  unsigned long pm_l4_offset    : 9;
  unsigned long sign_extend     : 16;
} VirtualAddress;

typedef struct {
  unsigned long p         : 1;
  unsigned long rw        : 1;
  unsigned long us        : 1;
  unsigned long pwt       : 1;
  unsigned long pcd       : 1;
  unsigned long a         : 1;
  unsigned long ign       : 1;
  unsigned long mbz       : 2;
  unsigned long avl       : 3;
  unsigned long address   : 40;
  unsigned long available : 11;
  unsigned long nx        : 1;
} PM_L4;

typedef struct {
  PM_L4 table[512];
} PM_L4_TABLE;

typedef struct {
  unsigned long p         : 1;
  unsigned long rw        : 1;
  unsigned long us        : 1;
  unsigned long pwt       : 1;
  unsigned long pcd       : 1;
  unsigned long a         : 1;
  unsigned long ign       : 1;
  unsigned long mbz       : 2;
  unsigned long avl       : 3;
  unsigned long address   : 40;
  unsigned long available : 11;
  unsigned long nx        : 1;
} PM_L3;

typedef struct {
  PM_L3 table[512];
} PM_L3_TABLE;

typedef struct {
  unsigned long p         : 1;
  unsigned long rw        : 1;
  unsigned long us        : 1;
  unsigned long pwt       : 1;
  unsigned long pcd       : 1;
  unsigned long a         : 1;
  unsigned long ign1      : 1;
  unsigned long zero      : 1;
  unsigned long ign2      : 1;
  unsigned long avl       : 3;
  unsigned long address   : 40;
  unsigned long available : 11;
  unsigned long nx        : 1;
} PM_L2;

typedef struct {
  PM_L2 table[512];
} PM_L2_TABLE;

typedef struct {
  unsigned long p         : 1;
  unsigned long rw        : 1;
  unsigned long us        : 1;
  unsigned long pwt       : 1;
  unsigned long pcd       : 1;
  unsigned long a         : 1;
  unsigned long d         : 1;
  unsigned long pat       : 1;
  unsigned long g         : 1;
  unsigned long avl       : 3;
  unsigned long address   : 40;
  unsigned long available : 11;
  unsigned long nx        : 1;
} PM_L1;

typedef struct {
  PM_L1 table[512];
} PM_L1_TABLE;

/* ASM functions */
void writeCR0(uint64_t value);
uint64_t readCR0();
void writeCR2(uint64_t value);
uint64_t readCR2();
void writeCR3(uint64_t value);
uint64_t readCR3();
void writeCR4(uint64_t value);
uint64_t readCR4();

/* Paging functions */
void vmm_initialize();
void page_fault_handler();
PM_L4_TABLE* new_pml4(int us);
void generic_l2_table(PM_L2_TABLE* table, int us);
PM_L1_TABLE* identity_l1_map(int first_l2_table_idx, int rw, int us);
uint64_t add_page(VirtualAddress addr);
PM_L3_TABLE* get_l3_table(PM_L4_TABLE* l4_table, uint64_t idx);
PM_L2_TABLE* get_l2_table(PM_L3_TABLE* table, uint64_t idx);
PM_L1_TABLE* get_l1_table(PM_L2_TABLE* table, uint64_t idx);
uint64_t add_to_l1_table(PM_L1_TABLE* table, uint64_t idx);

void l4_table_test();

void hex_log(char* pre, uint64_t num);

#endif