//
//  DoubleLinklist.h
//  CList
//
//  Created by hexueshi on 2018/9/29.
//  Copyright © 2018年 i4season. All rights reserved.
//

#ifndef DoubleLinklist_h
#define DoubleLinklist_h

#include <stdio.h>

typedef struct _dlinknodeData
{
    int _id;
    char *_str;
}dlinknodeData;

typedef struct _dlinknode
{
    struct _dlinknode *_prev;
    struct _dlinknode *_next;
    void *_data;
}dlinknode;

typedef struct _dLinkList
{
    dlinknode *_phead;
    int _count;
}dLinkList;

// 新建“双向链表”, 成功，返回链表；否则，返回NULL
dLinkList *create_dlinklist(void);
// 销毁“双向链表”。成功，返回0；否则，返回-1
int destroy_dlinklist(dLinkList *plist);

// “双向链表是否为空”.是，返回1，否则，返回0
int dlinklist_is_empty(dLinkList *plist);
// 返回“双向链表的大小”
int dlinklist_size(dLinkList *plist);

// 获取“双向链表中第index位置的元素”。成功，返回节点数据；否则，返回NULL。
void *dlinklist_get(dLinkList *plist, int index);
// 获取“双向链表中第1个元素”。成功，返回节点数据；否则，返回NULL。
void *dlinklist_get_first(dLinkList *plist);
// 获取“双向链表中最后1个元素”。成功，返回节点数据；否则，返回NULL。
void *dlinklist_get_last(dLinkList *plist);

// 将“pdata”插入到index位置。成功，返回0；否则，返回-1
int dlinklist_insert(dLinkList *plist, int index, void *pdata);
// 将“pdata”插入到表头位置,表头需要单独处理
int dlinklist_insert_first(dLinkList *plist, void *pdata);
// 将“pdata”插入到末尾位置
int dlinklist_append_last(dLinkList *plist, void *pdata);

// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1
int dlinklist_delete(dLinkList *plist, int index);
// 删除第一个节点
int dlinklist_delete_first(dLinkList *plist);
// 删除组后一个节点
int dlinklist_delete_last(dLinkList *plist);

// 打印所有链表内容
void print_dlinklist(dLinkList *plist);

#endif /* DoubleLinklist_h */
