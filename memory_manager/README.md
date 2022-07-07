# 内存管理说明

## 页

```c
struct page{
    unsigned long flags;        # 页状态，是不是脏的
    atomic_t      _count;       # 页被引用次数， -1表示内核当前没有引用这一页
    atomic_t      _mapcount;
    unsigned long private;
    struct address_space *mapping;
    pgoff_t       index;
    struct list_head  lru;
    void          *virtual;     # 页虚拟地址
};

```
定义在<linux/page-flags.h>每一页都要分配这样一个结构。


## 区


Linux主要使用四种区
* ZONE_DMA: 这个区包含的页能用来执行DMA操作；
* ZONE_DMA32: 类似ZONE_DMA，不同之处只能被32位设备访问；
* ZONE_NORMAL: 这个区包含都是能正常映射的页；
* ZONE_HIGHEM: 这个区包含“高端内存”，其中的页并不能永久映射到内核地址空间。
 
## slab原理
slab三种状态：
满、部分满、空；  
内核需要新对象，先从部分满的slap中进行分配，如果没有部分满的，就从空的slap中分配，空的也没有就要新创建一个slap；

```c
struct slap{
    struct list_head list;    /* 满、部分满或空链表 */
    unsigned long colouroff;  /* slab着色的偏移量 */
    void          *s_mem;     /* 在slab中的第一个对象 */
    unsigned int  inuse;      /* slab中已分配的对象数 */
    kmem_bufctl_t free;       /* 第一个空闲对象（如果有的话）*/
};

```

### slab和buddy的关系

slab对上提供kmalloc，kfree接口；

buddy对上（slab）提供alloc_page,free_pages接口，对下管理物理内存；

(./img/slab.jpg)
