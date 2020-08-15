#include "darr.h"

//初始化
DARR *darr_creat(int size)
{
	DARR *handle = NULL;

	handle = (DARR *)malloc(sizeof(DARR));
	ERRP(NULL == handle, malloc handle, goto ERR1);

	handle->data = NULL;
	handle->size = size;
	handle->count = 0;

	return handle;
ERR1:
	return NULL;
}


//表示尾插
int darr_append(DARR *handle, void *data)
{
	void *new = NULL;

	new = (void *)malloc(handle->size * (handle->count + 1));
	ERRP(NULL == new, malloc, goto ERR1);

	memcpy(new, handle->data, handle->count * handle->size);
	free(handle->data);
	memcpy(new + handle->count * handle->size, data, handle->size);
	handle->data = new;
	handle->count++;

	return 0;
ERR1:
	return -1;
}
//前插
int darr_appprev(DARR *handle, void *data)
{
	ERRP(data == NULL, option err, goto ERR1);

	void *new = NULL;

	new = (void *)malloc(handle->size * (handle->count + 1));
	ERRP(NULL == new, malloc, goto ERR1);

	memmove(new, data, handle->size);
	memmove(new + handle->size, handle->data, handle->size * handle->count);
	free(handle->data);
	handle->data = new;
	handle->count++;


	return 0;
ERR1:
	return -1;
}
//指定位置插入
int darr_index_insert(DARR *handle, void *data, int index)
{
	void *new = NULL;

	ERRP(data == NULL, option data, goto ERR1);

	/*ERRP(index < 0 || index > handle->count, option index[0 ~ ], goto ERR1);*/
	if (index < 0 || index > handle->count)
	{
		printf("option index [0 ~ %d]\n", handle->count);
		goto ERR1;
	}

	new = (void *)malloc(handle->size * (handle->count + 1));
	ERRP(NULL == new, malloc, goto ERR1);

	//先写handle->data前半部分给new
	memmove(new, handle->data, index * handle->size);
	//拷贝新的数据给new
	memmove(new + index * handle->size, data, handle->size);
	//最后把handle->data剩余数据拷贝new
	memmove(new + (index + 1) * handle->size, handle->data + index * handle->size, (handle->count - index) * handle->size);
	free(handle->data);
	handle->data = new;
	handle->count++;


	return 0;
ERR1:
	return -1;
}



//删除，从前到后删除
void darr_front_del(DARR *handle, void *key, darr_cmp_t *cmp)
{
	int i;
	void *new = NULL;

	for (i = 0; i < handle->count; i++)
	{
		if (cmp(key, handle->data + i * handle->size) == 0)
		{
			new = (void *)malloc(handle->size * (handle->count - 1));
			ERRP(NULL == new, malloc,  goto ERR1);

			memcpy(new, handle->data, i * handle->size);
			memcpy(new + i * handle->size, handle->data + (i + 1) * handle->size, (handle->count - i - 1) * handle->size);
			free(handle->data);
			handle->data = new;
			handle->count--;
			return ;
		}
	}
	return ;
ERR1:
	return ;
}

void darr_index_del(DARR *handle, int index)
{
	void *new = NULL;

	ERRP(index < 0 || index >= handle->count, option index, goto ERR1);

	new = (void *)malloc(handle->size * (handle->count - 1));
	ERRP(new == NULL, malloc, goto ERR1);

	memcpy(new, handle->data, handle->size * index);
	memcpy(new + handle->size * index, handle->data + (index + 1) * handle->size, (handle->count - index - 1) * handle->size);
	free(handle->data);
	handle->data = new;
	handle->count--;

	return ;
ERR1:
	return ;
}


void darr_all_del(DARR *handle, void *key, darr_cmp_t *cmp)
{
	int i;
	void *new = NULL;

	for (i = 0; i < handle->count; i++)
	{
		if (cmp(key, handle->data + i * handle->size) == 0)
		{
			new = (void *)malloc(handle->size * (handle->count - 1));
			ERRP(NULL == new, malloc,  goto ERR1);

			memcpy(new, handle->data, i * handle->size);
			memcpy(new + i * handle->size, handle->data + (i + 1) * handle->size, (handle->count - i - 1) * handle->size);
			free(handle->data);
			handle->data = new;
			handle->count--;
			i--;
		
		}
	}
	return ;
ERR1:
	return ;
}

//查找 匹配所有信息
DARR *darr_all_find(DARR *handle, void *key, darr_cmp_t *cmp)
{
	int i;
	DARR *ind = NULL;

	ind = darr_creat(handle->size);
	ERRP(ind == NULL, darr_creat, goto ERR1);

	for (i = 0; i < handle->count; i++)
	{
		if (cmp(key, handle->data + i * handle->size) == 0)
		{
			darr_append(ind, handle->data + i * handle->size);
		}
	}

	return ind;
ERR1:
	return NULL;
}

void *darr_find(DARR *handle, void *key, darr_cmp_t *cmp)
{
	int i;

	for (i = 0; i < handle->count; i++)
	{
		if (cmp(key, handle->data + i * handle->size) == 0)
		{
			return handle->data + i * handle->size;
		}
	}

	return NULL;
}

void *darr_index_find(DARR *handle, int index)
{

	ERRP(index < 0 || index >= handle->count, option index, return NULL);

	return handle->data + index * handle->size;
}


int darr_num(DARR *handle)
{
	return handle->count;
}

//排序  由大到小
void darr_sort(DARR *handle, darr_cmp_t *cmp)
{
	int i, j;
	void *tmp;

	tmp = (void *)malloc(handle->size);
	ERRP(tmp == NULL, malloc, goto ERR1);

	for (i = 0; i < handle->count; i++)
	{
		for (j = i + 1; j < handle->count; j++)
		{
			if (cmp(handle->data + i * handle->size, handle->data + j * handle->size) > 0)
			{
				memmove(tmp, handle->data + i * handle->size, handle->size);
				memmove(handle->data + i * handle->size, handle->data + j * handle->size, 
					handle->size);
				memmove(handle->data + j * handle->size, tmp, handle->size);
			}
		}
	}
	return ;
ERR1:
	return ;
}

//存储
int darr_store(DARR *handle, const char *path)
{
	FILE *fp = NULL;
	int ret;

	fp = fopen(path, "w");
	ERRP(NULL == fp, fopen, goto ERR1);

	//保存数据类型和长度
	ret = fwrite(&handle->size, sizeof(handle->size), 1, fp);
	ERRP(ret != 1, fwrite size, goto ERR2);

	ret = fwrite(&handle->count, sizeof(handle->count), 1, fp);
	ERRP(ret != 1, fwrite count, goto ERR2);


	//存储数据到文件中
	ret = fwrite(handle->data, handle->size, handle->count, fp);
	ERRP(ret != handle->count, fwrite data, goto ERR2);


	fclose(fp);//缓冲区
	return 0;
ERR2:
	fclose(fp);
ERR1:
	return -1;
}

//加载
DARR *darr_load(const char *path)
{
	FILE *fp = NULL;
	DARR *handle = NULL;
	int size, count;
	int ret;

	//打开文件
	fp = fopen(path, "r");
	ERRP(NULL == fp, fopen read, goto ERR1);

	//抽象数据类型申请空间
	handle = (DARR *)malloc(sizeof(DARR));
	ERRP(NULL == handle, malloc handle, goto ERR2);

	//读取数据类型
	ret = fread(&size, sizeof(size), 1, fp);
	ERRP(ret != 1, fread size, goto ERR3);
	
	//读取数据长度
	ret = fread(&count, sizeof(count), 1, fp);
	ERRP(ret != 1, fread count, goto ERR3);


	//数据申请空间
	handle->data = (void *)malloc(size * count);
	ERRP(NULL == handle->data, malloc data, goto ERR3);
	handle->size = size;
	handle->count = count;
	
	//读取数据
	ret = fread(handle->data, size, count, fp);
	ERRP(ret != count, fread date, goto ERR4);

	//关闭文件
	fclose(fp);
	return handle;
ERR4:
	free(handle->data);
ERR3:
	free(handle);
ERR2:
	fclose(fp);
ERR1:
	return NULL;
}


//遍历
void darr_travel(DARR *handle, darr_op_t *op)
{
	int i;
	for (i = 0; i < handle->count; i++)
	{
		op(handle->data + i * handle->size);
	}
}

//销毁
void darr_destroy(DARR **handle)
{
	
	free((*handle)->data);
	(*handle)->data = NULL;
	free(*handle);
	*handle = NULL;
}
