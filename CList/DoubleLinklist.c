//
//  DoubleLinklist.c
//  CList
//
//  Created by hexueshi on 2018/9/29.
//  Copyright © 2018年 i4season. All rights reserved.
//

#include "DoubleLinklist.h"
#include <stdlib.h>

// 将“pdata”插入到表头位置
int dlinklist_insert_first(dLinkList *plist, void *pdata);
// 将“pdata”插入到末尾位置
int dlinklist_append_last(dLinkList *plist, void *pdata);

// 删除第一个节点
int dlinklist_delete_first(dLinkList *plist);
// 删除组后一个节点
int dlinklist_delete_last(dLinkList *plist);

// 释放节点内存, 需要考虑到_data部分数据的释放
// dlinknodeData结构体改变需要要修改此处
static inline void free_dlinknodedata(dlinknode *pnode)
{
    if (NULL != pnode)
    {
        if (NULL != pnode->_data)
        {
            dlinknodeData *pnodedata = (dlinknodeData *)pnode->_data;
            if (NULL != pnodedata->_str)
            {
                free(pnodedata->_str);
                pnodedata->_str = NULL;
            }
            
            free(pnode->_data);
            pnode->_data = NULL;
        }
        
        free(pnode);
    }
}

// 打印_data部分数据
// dlinknodeData结构体改变需要要修改此处
static inline void print_dlinknodedata(dlinknode *pnode)
{
    dlinknodeData *data = (dlinknodeData *)pnode->_data;
    printf("_id = %d, str = %s\n", data->_id, data->_str);
}

static dlinknode *create_dlinknode(void *data)
{
    dlinknode *pnode = (dlinknode *)malloc(sizeof(dlinknode));
    if (NULL == pnode)
    {
        return NULL;
    }
    pnode->_data = data;
    pnode->_next = pnode->_prev = pnode;
    
    return pnode;
}

// 新建“双向链表”, 成功，返回链表；否则，返回NULL
dLinkList *create_dlinklist(void)
{
    dLinkList *plist = (dLinkList *)malloc(sizeof(struct _dLinkList));
    if (NULL == plist)
    {
        return NULL;
    }
    plist->_phead = NULL;
    plist->_count = 0;
    
    return plist;
}

// 销毁“双向链表”。成功，返回0；否则，返回-1
int destroy_dlinklist(dLinkList *plist)
{
    if (NULL == plist)
    {
        printf("%s failed! dlink is null!\n", __func__);
        return -1;
    }
    
    dlinknode *pnode = plist->_phead->_next;
    dlinknode *ptmp = NULL;
    while (pnode != plist->_phead)
    {
        ptmp = pnode;
        pnode = pnode->_next;
        free_dlinknodedata(ptmp);
    }
    
    // 释放头结点
    free_dlinknodedata(plist->_phead);
    plist->_phead = NULL;
    plist->_count = 0;
    
    return 0;
}

// “双向链表是否为空”.是，返回1，否则，返回0
int dlinklist_is_empty(dLinkList *plist)
{
    if (NULL == plist || plist->_count <= 0)
    {
        return 1;
    }
    
    return 0;
}

// 返回“双向链表的大小”
int dlinklist_size(dLinkList *plist)
{
    if (NULL == plist)
    {
        return 0;
    }
    
    return plist->_count;
}

static dlinknode *get_dlinknode(dLinkList *plist, int index)
{
    if (index < 0 || index >= plist->_count)
    {
        printf("%s failed! index out of bound!\n", __func__);
        return NULL;
    }
    
    // 判断index位置
    if (index <= (plist->_count/2))
    {
        int i = 0;
        dlinknode *pnode = plist->_phead;
        while ((i++) < index)
        {
            pnode = pnode->_next;
        }
        
        return pnode;
    }
    else
    {
        int j = 0;
        int rindex = plist->_count - index - 1;
        dlinknode *rnode = plist->_phead->_prev;
        while ((j++) < rindex)
        {
            rnode = rnode->_prev;
        }
        
        return rnode;
    }
}

// 获取“双向链表中第index位置的元素”。成功，返回节点数据；否则，返回NULL。
void *dlinklist_get(dLinkList *plist, int index)
{
    dlinknode *pnode = get_dlinknode(plist, index);
    if (NULL == pnode)
    {
        printf("%s failed!\n", __func__);
        return NULL;
    }
    
    return pnode->_data;
}

// 获取“双向链表中第1个元素”。成功，返回节点数据；否则，返回NULL。
void *dlinklist_get_first(dLinkList *plist)
{
    if (NULL == plist || plist->_count <= 0)
    {
        return NULL;
    }
    
    return plist->_phead->_data;
}

// 获取“双向链表中最后1个元素”。成功，返回节点数据；否则，返回NULL。
void *dlinklist_get_last(dLinkList *plist)
{
    if (NULL == plist || plist->_count <= 0)
    {
        return NULL;
    }
    
    return get_dlinknode(plist, plist->_count - 1)->_data;
}

// 将“pdata”插入到index位置。成功，返回0；否则，返回-1
int dlinklist_insert(dLinkList *plist, int index, void *pdata)
{
    // 判断位置
    if (0 == index)
    {
        return dlinklist_insert_first(plist, pdata);
    }
    else if (index == plist->_count)
    {
        return dlinklist_append_last(plist, pdata);
    }
    else
    {
        if (NULL == plist)
        {
            return -1;
        }
        
        // 得到将要插入的位置的节点
        dlinknode *pindex = get_dlinknode(plist, index);
        if (NULL == pindex)
        {
            return -1;
        }
        
        dlinknode *pnode = create_dlinknode(pdata);
        if (NULL == pnode)
        {
            return -1;
        }
        
        pnode->_next = pindex;
        pnode->_prev = pindex->_prev;
        pindex->_prev->_next = pnode;
        pindex->_prev = pnode;
        
        plist->_count++;
        
        return 0;
    }
}

// 将“pdata”插入到表头位置,表头需要单独处理
int dlinklist_insert_first(dLinkList *plist, void *pdata)
{
    if (NULL == plist)
    {
        return -1;
    }
    
    dlinknode *pnode = create_dlinknode(pdata);
    if (NULL == pnode)
    {
        return -1;
    }
    
    if (NULL == plist->_phead)
    {
        plist->_phead = pnode;
        plist->_count++;
    }
    else
    {
        pnode->_prev = plist->_phead->_prev;
        pnode->_next = plist->_phead;
        plist->_phead->_prev->_next = pnode;
        plist->_phead->_prev = pnode;
        
        plist->_phead = pnode;
        plist->_count++;
    }
    
    return 0;
}

// 将“pdata”插入到末尾位置
int dlinklist_append_last(dLinkList *plist, void *pdata)
{
    if (NULL == plist)
    {
        return -1;
    }
    
    dlinknode *pnode = create_dlinknode(pdata);
    if (NULL == pnode)
    {
        return -1;
    }
    
    if (NULL == plist->_phead)
    {
        plist->_phead = pnode;
        plist->_count++;
    }
    else
    {
        pnode->_prev = plist->_phead->_prev;
        pnode->_next = plist->_phead;
        plist->_phead->_prev->_next = pnode;
        plist->_phead->_prev = pnode;
        
        plist->_count++;
    }
    
    return 0;
}

// 删除“双向链表中index位置的节点”。成功，返回0；否则，返回-1
int dlinklist_delete(dLinkList *plist, int index)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        return -1;
    }
    
    if (index == 0)
    {
        return dlinklist_delete_first(plist);
    }
    else if (index == (plist->_count - 1))
    {
        return dlinklist_delete_last(plist);
    }
    else
    {
        dlinknode *pindex = get_dlinknode(plist, index);
        if (NULL == pindex)
        {
            return -1;
        }
        
        pindex->_prev->_next = pindex->_next;
        pindex->_next->_prev = pindex->_prev;
        
        free_dlinknodedata(pindex);
        plist->_count--;
        
        return 0;
    }
}

// 删除第一个节点
int dlinklist_delete_first(dLinkList *plist)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        return -1;
    }
    
    if (plist->_count == 1)
    {
        dlinknode *phead = plist->_phead;
        plist->_phead = NULL;
        plist->_count = 0;
        
        free_dlinknodedata(phead);
    }
    else
    {
        dlinknode *phead = plist->_phead;
        
        phead->_prev->_next = phead->_next;
        phead->_next->_prev = phead->_prev;
        
        plist->_phead = phead->_next;
        free_dlinknodedata(phead);
        plist->_count--;
    }
    
    return 0;
}

// 删除组后一个节点
int dlinklist_delete_last(dLinkList *plist)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        return -1;
    }
    
    if (1 == plist->_count)
    {
        dlinknode *phead = plist->_phead;
        plist->_phead = NULL;
        plist->_count = 0;
        
        free_dlinknodedata(phead);
    }
    else
    {
        dlinknode *plastnode = plist->_phead->_prev;
        
        plastnode->_prev->_next = plastnode->_next;
        plastnode->_next->_prev = plastnode->_prev;
        
        free_dlinknodedata(plastnode);
        plist->_count--;
    }
    
    return 0;
}

// 打印所有链表内容
void print_dlinklist(dLinkList *plist)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        printf("%s list is empty !!!\n", __func__);
        return;
    }
    
    printf("{list : \n");
    
    dlinknode *pnode = plist->_phead;
    int index = 0;
    for (; index < plist->_count; index++, pnode = pnode->_next)
    {
        print_dlinknodedata(pnode);
    }
    
    printf("}\n");
}

