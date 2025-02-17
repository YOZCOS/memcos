
#include <uapi/linux/perf_event.h>

#define BUFFER_SIZE	512 /* 1MB */
#define CPUS_PER_SOCKET 20


/* pebs events */
#define DRAM_LLC_LOAD_MISS  0x1d3
#define NVM_LLC_LOAD_MISS   0x80d1
#define ALL_STORES	    0x82d0
#define ALL_LOADS	    0x81d0
#define STLB_MISS_STORES    0x12d0
#define STLB_MISS_LOADS	    0x11d0

struct htmm_event {
    struct perf_event_header header;
    __u64 ip;
    __u32 pid, tid;
    __u64 addr;
};


enum events {
    DRAMREAD = 0,
    NVMREAD = 1,
    MEMWRITE = 2,
    TLB_MISS_LOADS = 3,
    TLB_MISS_STORES = 4,
    N_HTMMEVENTS
};

/* htmm_core.c */
extern void htmm_mm_init(struct mm_struct *mm);
extern void prep_transhuge_page_for_htmm(struct vm_area_struct *vma,
					 struct page *page);
extern void update_pginfo(pid_t pid, unsigned long address);

/* htmm_sampler.c */
extern int ksamplingd_init(pid_t pid, int node);
extern void ksamplingd_exit(void);

/* htmm_migrater.c */
#define HTMM_MIN_FREE_PAGES 256 * 10 // 10MB
extern void add_memcg_to_kmigraterd(struct mem_cgroup *memcg, int nid);
extern void del_memcg_from_kmigraterd(struct mem_cgroup *memcg, int nid);
extern int kmigraterd_init(void);
