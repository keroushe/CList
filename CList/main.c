//
//  main.c
//  CList
//
//  Created by hexueshi on 2018/9/29.
//  Copyright © 2018年 i4season. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinklist.h"
#include "Linklist.h"

void doublelinklist_test(void)
{
    dLinkList *list = create_dlinklist();
    
    int ret = dlinklist_is_empty(list);
    printf("list is empty, ret = %d\n", ret);
    int size = dlinklist_size(list);
    printf("list size, size = %d\n", size);
    
    dlinknodeData *pdata = (dlinknodeData *)dlinklist_get_first(list);
    printf("first data = %p\n", pdata);
    pdata = (dlinknodeData *)dlinklist_get_last(list);
    printf("last data = %p\n", pdata);
    pdata = (dlinknodeData *)dlinklist_get(list, 4);
    printf("index data = %p\n", pdata);
    
    dlinknodeData *data = NULL;
    for (int index = 0; index < 10; index++)
    {
        data = (dlinknodeData *)malloc(sizeof(dlinknodeData));
        data->_id = index;
        data->_str = (char *)malloc(sizeof(char) * 20);
        sprintf(data->_str, "index \(%d)", index);
        
//        dlinklist_insert_first(list, data);
//        dlinklist_append_last(list, data);
        dlinklist_insert(list, index, data);
    }
    
    print_dlinklist(list);
    
    ret = dlinklist_is_empty(list);
    printf("list is empty, ret = %d\n", ret);
    size = dlinklist_size(list);
    printf("list size, size = %d\n", size);
    
    pdata = (dlinknodeData *)dlinklist_get_first(list);
    printf("first data = %p\n", pdata);
    pdata = (dlinknodeData *)dlinklist_get_last(list);
    printf("last data = %p\n", pdata);
    pdata = (dlinknodeData *)dlinklist_get(list, 4);
    printf("index data = %p\n", pdata);
    
    // 删除
    int deleteRet = dlinklist_delete_first(list);
    printf("dlinklist_delete_first = %d\n", deleteRet);
    print_dlinklist(list);
    
    deleteRet = dlinklist_delete_last(list);
    printf("dlinklist_delete_last = %d\n", deleteRet);
    print_dlinklist(list);
    
    deleteRet = dlinklist_delete(list, 4);
    printf("dlinklist_delete = %d\n", deleteRet);
    print_dlinklist(list);
    
    // 尾部插入节点
    data = (dlinknodeData *)malloc(sizeof(dlinknodeData));
    data->_id = 100;
    data->_str = (char *)malloc(sizeof(char) * 20);
    sprintf(data->_str, "index \(%d)", 100);
    dlinklist_insert(list, list->_count - 2, data);
    
    print_dlinklist(list);
    
    destroy_dlinklist(list);
}

void linklist_test()
{
    linkList *list = create_linklist();
    
    int ret = linklist_is_empty(list);
    printf("list is empty, ret = %d\n", ret);
    int size = linklist_size(list);
    printf("list size, size = %d\n", size);
    
    linknodeData *pdata = (linknodeData *)linklist_get_first(list);
    printf("first data = %p\n", pdata);
    pdata = (linknodeData *)linklist_get_last(list);
    printf("last data = %p\n", pdata);
    pdata = (linknodeData *)linklist_get(list, 4);
    printf("index data = %p\n", pdata);
    
    linknodeData *data = NULL;
    for (int index = 0; index < 3; index++)
    {
        data = (linknodeData *)malloc(sizeof(linknodeData));
        data->_id = index;
        data->_str = (char *)malloc(sizeof(char) * 20);
        sprintf(data->_str, "index \(%d)", index);
        
//        linklist_insert_first(list, data);
//        linklist_append_last(list, data);
        linklist_insert(list, index, data);
    }
    
    print_linklist(list);
    
    ret = linklist_is_empty(list);
    printf("list is empty, ret = %d\n", ret);
    size = linklist_size(list);
    printf("list size, size = %d\n", size);
    
    pdata = (linknodeData *)linklist_get_first(list);
    printf("first data = %p\n", pdata);
    pdata = (linknodeData *)linklist_get_last(list);
    printf("last data = %p\n", pdata);
    pdata = (linknodeData *)linklist_get(list, 4);
    printf("index data = %p\n", pdata);
    
    // 删除
    int deleteRet = 0;
    deleteRet = linklist_delete_first(list);
    printf("linklist_delete_first = %d\n", deleteRet);
    print_linklist(list);
    
    deleteRet = linklist_delete_last(list);
    printf("linklist_delete_last = %d\n", deleteRet);
    print_linklist(list);
    
    deleteRet = linklist_delete(list, 1);
    printf("linklist_delete = %d\n", deleteRet);
    print_linklist(list);
    
    destory_linklist(list);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    doublelinklist_test();
//    linklist_test();
    return 0;
}

