//
//  Linklist.c
//  CList
//
//  Created by hexueshi on 2018/9/29.
//  Copyright © 2018年 i4season. All rights reserved.
//

#include "Linklist.h"
#include <stdlib.h>

// 将“pdata”插入到表头位置,表头需要单独处理
int linklist_insert_first(linkList *plist, void *pdata);
// 将“pdata”插入到末尾位置
int linklist_append_last(linkList *plist, void *pdata);

// 删除第一个节点
int linklist_delete_first(linkList *plist);
// 删除组后一个节点
int linklist_delete_last(linkList *plist);

// 释放节点内存, 需要考虑到_data部分数据的释放
// dlinknodeData结构体改变需要要修改此处
static inline void free_linknodedata(linknode *pnode)
{
    if (NULL != pnode)
    {
        if (NULL != pnode->_data)
        {
            linknodeData *pnodedata = (linknodeData *)pnode->_data;
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
static inline void print_linknodedata(linknode *pnode)
{
    linknodeData *data = (linknodeData *)pnode->_data;
    printf("_id = %d, str = %s\n", data->_id, data->_str);
}

static linknode *create_linknode(void *data)
{
    linknode *pnode = (linknode *)malloc(sizeof(linknode));
    if (NULL == pnode)
    {
        return NULL;
    }
    pnode->_data = data;
    pnode->_next = NULL;
    
    return pnode;
}

// 新建"链表",成功，返回链表;失败，返回NULL
linkList *create_linklist(void)
{
    linkList *plist = (linkList *)malloc(sizeof(linkList));
    if (NULL == plist)
    {
        return NULL;
    }
    plist->_phead = NULL;
    plist->_count = 0;
    
    return plist;
}

// 销毁"链表",成功，返回0；否则返回-1
int destory_linklist(linkList *plist)
{
    if (NULL == plist)
    {
        printf("%s failed! dlink is null!\n", __func__);
        return -1;
    }
    
    linknode *pnode = plist->_phead;
    linknode *ptmp = NULL;
    while (pnode != NULL)
    {
        ptmp = pnode;
        pnode = pnode->_next;
        free_linknodedata(ptmp);
    }
    
    plist->_phead = NULL;
    plist->_count = 0;
    
    return 0;
}

// “链表是否为空”.是，返回1，否则，返回0
int linklist_is_empty(linkList *plist)
{
    if (NULL == plist || plist->_count <= 0)
    {
        return 1;
    }
    
    return 0;
}

// 返回“链表的大小”
int linklist_size(linkList *plist)
{
    if (NULL == plist)
    {
        return 0;
    }
    
    return plist->_count;
}

static linknode *get_linknode(linkList *plist, int index)
{
    if (index < 0 || index >= plist->_count)
    {
        printf("%s failed! index out of bound!\n", __func__);
        return NULL;
    }
    
    int i = 0;
    linknode *pnode = plist->_phead;
    while ((i++) < index)
    {
        pnode = pnode->_next;
    }
    
    return pnode;
}

// 获取“链表中第index位置的元素”。成功，返回节点数据；否则，返回NULL。
void *linklist_get(linkList *plist, int index)
{
    linknode *pnode = get_linknode(plist, index);
    if (NULL == pnode)
    {
        printf("%s failed!\n", __func__);
        return NULL;
    }
    
    return pnode->_data;
}

// 获取“链表中第1个元素”。成功，返回节点数据；否则，返回NULL。
void *linklist_get_first(linkList *plist)
{
    if (NULL == plist || plist->_count <= 0)
    {
        return NULL;
    }
    
    return plist->_phead->_data;
}

// 获取“链表中最后1个元素”。成功，返回节点数据；否则，返回NULL。
void *linklist_get_last(linkList *plist)
{
    if (NULL == plist || plist->_count <= 0)
    {
        return NULL;
    }
    
    return get_linknode(plist, plist->_count - 1)->_data;
}

// 将“pdata”插入到index位置。成功，返回0；否则，返回-1
int linklist_insert(linkList *plist, int index, void *pdata)
{
    if (0 == index)
    {
        return linklist_insert_first(plist, pdata);
    }
    else if (index == plist->_count)
    {
        return linklist_append_last(plist, pdata);
    }
    else
    {
        if (NULL == plist)
        {
            return -1;
        }
        
        // 得到要插入位置的节点
        linknode *pindex = get_linknode(plist, index);
        if (NULL == pindex)
        {
            return -1;
        }
        linknode *preindex = get_linknode(plist, index - 1);
        if (NULL == preindex)
        {
            return -1;
        }
        
        linknode *pnode = create_linknode(pdata);
        if (NULL == pnode)
        {
            return -1;
        }
        pnode->_next = pindex;
        preindex->_next = pnode;
        
        plist->_count++;
        
        return 0;
    }
}

// 将“pdata”插入到表头位置,表头需要单独处理
int linklist_insert_first(linkList *plist, void *pdata)
{
    if (NULL == plist)
    {
        return -1;
    }
    
    linknode *pnode = create_linknode(pdata);
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
        pnode->_next = plist->_phead;
        plist->_phead = pnode;
        
        plist->_count++;
    }
    
    return 0;
}

// 将“pdata”插入到末尾位置
int linklist_append_last(linkList *plist, void *pdata)
{
    if (NULL == plist)
    {
        return -1;
    }
    
    linknode *pnode = create_linknode(pdata);
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
        linknode *plastnode = get_linknode(plist, plist->_count - 1);
        plastnode->_next = pnode;
        plist->_count++;
    }
    
    return 0;
}

// 删除“链表中index位置的节点”。成功，返回0；否则，返回-1
int linklist_delete(linkList *plist, int index)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        return -1;
    }
    
    if (index == 0)
    {
        return linklist_delete_first(plist);
    }
    else if (index == (plist->_count-1))
    {
        return linklist_delete_last(plist);
    }
    else
    {
        linknode *pindex = get_linknode(plist, index);
        if (NULL == pindex)
        {
            return -1;
        }
        linknode *preindex = get_linknode(plist, index - 1);
        if (NULL == preindex)
        {
            return -1;
        }
        
        preindex->_next = pindex->_next;
        
        free_linknodedata(pindex);
        plist->_count--;
    }
    
    return 0;
}

// 删除第一个节点
int linklist_delete_first(linkList *plist)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        return -1;
    }
    
    linknode *phead = plist->_phead;
    plist->_phead = plist->_phead->_next;
    
    free_linknodedata(phead);
    plist->_count--;
    
    return 0;
}

// 删除组后一个节点
int linklist_delete_last(linkList *plist)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        return -1;
    }
    
    // 找到倒数第二个节点
    linknode *plastsecondnode = get_linknode(plist, plist->_count - 2);
    if (NULL != plastsecondnode)
    {
        // 释放最后一个节点
        linknode *plastnode = plastsecondnode->_next;
        plastsecondnode->_next = NULL;
        
        free_linknodedata(plastnode);
        plist->_count--;
    }
    else
    {
        // 没有倒数第二个节点，说明仅包含一个节点
        linknode *plastnode = get_linknode(plist, plist->_count - 1);
        plist->_phead = NULL;
        plist->_count = 0;
        
        free_linknodedata(plastnode);
    }
    
    return 0;
}

// 打印所有链表内容
void print_linklist(linkList *plist)
{
    if (NULL == plist || NULL == plist->_phead || plist->_count <= 0)
    {
        printf("%s list is empty !!!\n", __func__);
        return;
    }
    
    printf("{list : \n");
    
    linknode *pnode = plist->_phead;
    while (pnode != NULL)
    {
        print_linknodedata(pnode);
        pnode = pnode->_next;
    }
    
    printf("}\n");
}

