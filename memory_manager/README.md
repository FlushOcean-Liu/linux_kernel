# 内存管理说明
## 相关概念
* 虚拟内存
* 物理内存
* 页表
* 页框
* 内存节点
* DMA内存区域
* 高端内存
* TBL：页表缓冲、转址旁路缓存；  
* PCB：进程控制块；  
* 内存共享：把两个虚拟地址空间通过页表映射到同一物理地址空间。


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
struct slab{
    struct list_head list;    /* 满、部分满或空链表 */
    unsigned long colouroff;  /* slab着色的偏移量 */
    void          *s_mem;     /* 在slab中的第一个对象 */
    unsigned int  inuse;      /* slab中已分配的对象数 */
    kmem_bufctl_t free;       /* 第一个空闲对象（如果有的话）*/
};

```


slab设计的目的：  
内核页必须经常分配内存，但无法借助标准库函数，按页分配内存，单位太大，不仅浪费空间而且完全不可接受；
因此引入slab管理机制。

### slab和buddy的关系

slab对上提供kmalloc，kfree接口；

buddy对上（slab）提供alloc_page,free_pages接口，对下管理物理内存；

![](./img/slab.jpg)


## 内核栈空间
用户空间可以奢侈的负担非常大的栈，而且栈空间还可以动态增长，内核却不能这么奢侈，内核栈小而且固定，每个进程都有两个页的内核栈。
