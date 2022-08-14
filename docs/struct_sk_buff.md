## struct sk_buff 结构详解

参考 https://blog.51cto.com/weiguozhihui/1586777


```c
struct sk_buff_head 
{
    struct sk_buff *next;
    struct sk_buff *prev;
    
    __u32 qlen;
    spinlock_t lock;
}


struct sk_buff
{
    struct sk_buff *next;
    struct sk_buff *prev;
    struct sock *sock ;//struct sock是socket在网络层的表示，其中存放了网络层的信息
    
    unsigned int len;//下面有介绍
    unsigned int data_len; //下面有介绍
    __u16   mac_len ; //数路链路层的头长度
    __u16   hdr_len ; //writable header length of cloned skb
    unsigned int truesize ; //socket buffer(套接字缓存区的大小)
    atomic_t users ; //对当前的struct sk_buff结构体的引用次数；
    __u32   priority ; //这个struct sk_buff结构体的优先级
    
    sk_buff_data_t transport_header ; //传输层头部的偏移量
    sk_buff_data_t network_header ;   //网络层头部的偏移量
    sk_buff_data_t mac_header ;       //数据链路层头部的偏移量
    
    char *data ;            //socket buffer中数据的起始位置；
    sk_buff_data_t tail ;   //socket buffer中数据的结束位置；
    char *head ;            //socket buffer缓存区的起始位置；
    sk_buffer_data_t end ;  //socket buffer缓存区的终止位置；
    
    struct net_device *dev; //将要发送struct sk_buff结构体的网络设备或struct sk_buff的接收
                            //网络设备
    int iif;  //网络设备的接口索引号；
    
    
    struct timeval tstamp ; //用于存放接受的数据包的到达时间；
    
    __u8  local_df : 1,  //allow local fragmentaion;
          cloned   : 1,  // head may be cloned;
    
    __u8  pkt_type : 3,  //数据包的类型；
          fclone   : 2,  // struct sk_buff clone status
    
}


```
