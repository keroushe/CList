//
//  Linklist.h
//  CList
//
//  Created by hexueshi on 2018/9/29.
//  Copyright © 2018年 i4season. All rights reserved.
//

#ifndef Linklist_h
#define Linklist_h

#include <stdio.h>

typedef struct _linknodeData
{
    int _id;
    char *_str;
}linknodeData;

typedef struct _linknode
{
    struct _linknode *_next;
    void *_data;
}linknode;

typedef struct _linkList
{
    linknode *_phead;
    int _count;
}linkList;

// 新建"链表",成功，返回链表;失败，返回NULL
linkList *create_linklist(void);
// 销毁"链表",成功，返回0；否则返回-1
int destory_linklist(linkList *plist);

// “链表是否为空”.是，返回1，否则，返回0
int linklist_is_empty(linkList *plist);
// 返回“链表的大小”
int linklist_size(linkList *plist);

// 获取“链表中第index位置的元素”。成功，返回节点数据；否则，返回NULL。
void *linklist_get(linkList *plist, int index);
// 获取“链表中第1个元素”。成功，返回节点数据；否则，返回NULL。
void *linklist_get_first(linkList *plist);
// 获取“链表中最后1个元素”。成功，返回节点数据；否则，返回NULL。
void *linklist_get_last(linkList *plist);

// 将“pdata”插入到index位置。成功，返回0；否则，返回-1
int linklist_insert(linkList *plist, int index, void *pdata);
// 将“pdata”插入到表头位置,表头需要单独处理
int linklist_insert_first(linkList *plist, void *pdata);
// 将“pdata”插入到末尾位置
int linklist_append_last(linkList *plist, void *pdata);

// 删除“链表中index位置的节点”。成功，返回0；否则，返回-1
int linklist_delete(linkList *plist, int index);
// 删除第一个节点
int linklist_delete_first(linkList *plist);
// 删除组后一个节点
int linklist_delete_last(linkList *plist);

// 打印所有链表内容
void print_linklist(linkList *plist);

#endif /* Linklist_h */
