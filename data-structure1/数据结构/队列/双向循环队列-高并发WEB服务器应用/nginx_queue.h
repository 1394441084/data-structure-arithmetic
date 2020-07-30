#pragma once
#ifndef _NGX_QUEUE_H_INCLUDED_ 
#define _NGX_QUEUE_H_INCLUDED_ 

/*�ڸ߲��� HTTP ������������ Nginx �У�������һ��������ϢϢ��ص�ģ�� - �ļ����档
�������ʵ����ļ��ᱻ nginx �Ӵ��̻��浽�ڴ棬�������Լ������� Nginx �Ĳ���������������Ϊ �ڴ�����ƣ�
��������ļ����ﵽһ���̶ȵ�ʱ��ͻ��ȡ��̭���ƣ�������̭����ʱ��ȽϾû������ ���ʺ���(LRU)�Ķ����ļ��� 

����ʵ�ַ����� (ʹ�÷�����)
1. ʹ��˫��ѭ�����б��滺����ļ��ڵ㣬��������ʵ�ֶ�����̭���ԣ� 
���磺���������̭����ʱ��ȽϾõĲ��ԣ��Ϳ���ʹ�ö��е����ԣ��Ƚ��ȳ� ���Ҫ���ð��� LRU���ͱ��������ҵ��ڵ�ɾ����
*/

typedef struct ngx_queue_s ngx_queue_t; 
struct ngx_queue_s { //����ڵ� 
	ngx_queue_t *prev; //ǰ
	ngx_queue_t *next; //��
};

//�꺯��:��ʼ������
#define ngx_queue_init(q) \
            (q)->prev = q;\
            (q)->next = q 

//�ж��Ƿ�Ϊ��
#define ngx_queue_empty(h) \
            (h == (h)->prev) 

//�꺯��:����ڵ�x���½ڵ�,h����һ���ڵ�(β)
/*
 (x)->next = (h)->next;   \\(h)->next==h; �ռ���������:NULL x h(�½ڵ�)  h h h(ԭ�ڵ�)
 (x)->next->prev = x; \\(x)->next->prev==h->prev; �ռ���������:x x h(��)  x h h(ԭ)
 (x)->prev = h; \\�ռ���������:h x h(��)  x h h(ԭ)
 (h)->next = x  \\�ռ���������:h x h(��)  x h x(ԭ)
 //ѭ������������ //�Ӷ�ͷ��
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

//��x�ڵ������ȥ��
#define ngx_queue_remove(x) \
            (x)->next->prev = (x)->prev; \
            (x)->prev->next = (x)->next 

//��ȡngx_cached_file_t�ĵ�ַ
#define ngx_queue_data(q, type, link) \
            (type*)((char*)q - offsetof(type, link))

#endif