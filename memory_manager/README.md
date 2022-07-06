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
