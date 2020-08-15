#ifndef __KEN_DARR_H__
#define __KEN_DARR_H__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>//gf
#include <share.h>

#define FRONT	1// 0
#define END		2//10
#define INDEX	3//index


//定义函数指针类型
typedef void (darr_op_t)(void *);
typedef int (darr_cmp_t)(void *, void *);

//抽象数据类型
typedef struct darr_t{
	void *data;//数据内容
	int size;//数据类型
	int count;//数据空间大小 
}DARR;


//初始化
DARR *darr_creat(int size);

//新的数据添加到原数据结尾
int darr_append(DARR *handle, void *data);
//添加数据到前面
int darr_appprev(DARR *handle, void *data);
//指定位置插入
int darr_index_insert(DARR *handle, void *data, int index);

//按关键字删除删除 从前到后删除 从后到前删除
void darr_front_del(DARR *handle, void *key, darr_cmp_t *cmp);
void darr_end_del(DARR *handle, void *key, darr_cmp_t *cmp);
void darr_index_del(DARR *handle, int index);
void darr_all_del(DARR *handle, void *key, darr_cmp_t *cmp);

//查找 按关键字查找
void *darr_find(DARR *handle, void *key, darr_cmp_t *cmp);
//按位置查找
void *darr_index_find(DARR *handle, int index);
//返回所有
DARR *darr_all_find(DARR *handle, void *key, darr_cmp_t *cmp);

//求数据大小 个数
int darr_num(DARR *handle);


//排序 
void darr_sort(DARR *handle, darr_cmp_t *cmp);

//存储
int darr_store(DARR *handle, const char *path);
//加载
DARR *darr_load(const char *path);


//遍历
void darr_travel(DARR *handle, darr_op_t *op);
//销毁
void darr_destroy(DARR **handle);

#endif //DARR_H
