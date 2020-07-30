#pragma once
#ifndef _NGX_QUEUE_H_INCLUDED_ 
#define _NGX_QUEUE_H_INCLUDED_ 

/*在高并发 HTTP 反向代理服务器 Nginx 中，存在着一个跟性能息息相关的模块 - 文件缓存。
经常访问到的文件会被 nginx 从磁盘缓存到内存，这样可以极大的提高 Nginx 的并发能力，不过因为 内存的限制，
当缓存的文件数达到一定程度的时候就会采取淘汰机制，优先淘汰进入时间比较久或是最近 访问很少(LRU)的队列文件。 

具体实现方案： (使用反链表)
1. 使用双向循环队列保存缓存的文件节点，这样可以实现多种淘汰策略： 
比如：如果采用淘汰进入时间比较久的策略，就可以使用队列的特性，先进先出 如果要采用按照 LRU，就遍历链表，找到节点删除。
*/

typedef struct ngx_queue_s ngx_queue_t; 
struct ngx_queue_s { //链表节点 
	ngx_queue_t *prev; //前
	ngx_queue_t *next; //后
};

//宏函数:初始化链表
#define ngx_queue_init(q) \
            (q)->prev = q;\
            (q)->next = q 

//判断是否为空
#define ngx_queue_empty(h) \
            (h == (h)->prev) 

//宏函数:插入节点x是新节点,h是上一个节点(尾)
/*
 (x)->next = (h)->next;   \\(h)->next==h; 空间链表排序:NULL x h(新节点)  h h h(原节点)
 (x)->next->prev = x; \\(x)->next->prev==h->prev; 空间链表排序:x x h(新)  x h h(原)
 (x)->prev = h; \\空间链表排序:h x h(新)  x h h(原)
 (h)->next = x  \\空间链表排序:h x h(新)  x h x(原)
 //循环链接已链接 //从队头进
*/
#define ngx_queue_insert_head(h, x) \
                (x)->next = (h)->next; \
                (x)->next->prev = x; \
                (x)->prev = h; \
                (h)->next = x 

#define ngx_queue_insert_after ngx_queue_insert_head 

#define ngx_queue_insert_tail(h, x) \
                (x)->prev = (h)->prev; \
                (x)->prev->next = x; \
                (x)->next = h; \
                (h)->prev = x 

#define ngx_queue_head(h) \
                (h)->next 

#define ngx_queue_last(h) \
                (h)->prev

#define ngx_queue_sentinel(h) \
                          (h) 

#define ngx_queue_next(q) \
                     (q)->next 

#define ngx_queue_prev(q) \
                    (q)->prev 

//将x节点从链表去除
#define ngx_queue_remove(x) \
            (x)->next->prev = (x)->prev; \
            (x)->prev->next = (x)->next 

//获取ngx_cached_file_t的地址
#define ngx_queue_data(q, type, link) \
            (type*)((char*)q - offsetof(type, link))

#endif