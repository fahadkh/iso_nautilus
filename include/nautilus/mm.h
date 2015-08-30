#ifndef __MM_H__
#define __MM_H__

#include <nautilus/naut_types.h>
#include <nautilus/list.h>

#define MAX_MMAP_ENTRIES 128

typedef struct mem_map_entry {
    uint64_t addr;
    uint64_t len;
    uint32_t type;
} mem_map_entry_t;

typedef struct mmap_info {
    uint64_t usable_ram; 
    uint64_t total_mem; /* includes I/O holes etc. */
    uint32_t last_pfn;
    uint32_t num_regions;
} mmap_info_t;

typedef struct boot_mem_info {
    ulong_t * page_map;
    ulong_t   npages;
    ulong_t   pm_len;
    ulong_t   last_offset;
    ulong_t   last_pos;
    ulong_t   last_success;
} boot_mem_info_t;

struct mem_map_entry * mm_boot_get_region(unsigned i);
unsigned mm_boot_num_regions(void);

uint64_t mm_get_usable_ram(void);
uint64_t mm_get_all_mem(void);
ulong_t mm_boot_last_pfn(void);
int mm_boot_init (ulong_t mbd);
void mm_boot_kmem_init(void);

void mm_boot_reserve_mem (addr_t start, ulong_t size);
void mm_boot_free_mem(addr_t start, ulong_t size);
void * __mm_boot_alloc(ulong_t size, ulong_t align, ulong_t goal);
void * mm_boot_alloc (ulong_t size);
void * mm_boot_alloc_aligned (ulong_t size, ulong_t align);
void mm_boot_free(void *addr, ulong_t size);


/* KMEM FUNCTIONS */

struct kmem_data {
    struct list_head ordered_regions;
};

int nk_kmem_init(void);

struct mem_region;

struct mem_region * kmem_get_base_zone(void);
struct mem_region * kmem_get_region_by_addr(ulong_t addr);
void kmem_add_memory(struct mem_region * mem, ulong_t base_addr, size_t size);
void * malloc(size_t size);
void free(const void * addr);


#endif /* !__MM_H__! */