#include "darr.h"

#define MAX 10

struct cls_t{
	char name[64];
	int id;
	int age;
	char sex;
	float cn;
	float en;
};

void ls(void *data)
{
	struct cls_t *cls = (struct cls_t *)data;

	printf("name : %8s | id : %d | age : %d | sex : %c | cn : %.2f | en : %.2f\n", 
		cls->name, cls->id, cls->age, cls->sex, cls->cn, cls->en);
}

int cmp_name(void *d1, void *d2)
{
	return strcmp((char *)d1, ((struct cls_t *)d2)->name);
}
int sort_name(void *d1, void *d2)
{
	return strcmp(((struct cls_t *)d1)->name, ((struct cls_t *)d2)->name);
}
int cmp_id(void *d1, void *d2)
{
	return *(int *)d1 - ((struct cls_t *)d2)->id;
}
int sort_id(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->id - ((struct cls_t *)d2)->id;
}
int cmp_age(void *d1, void *d2)
{
	return *(int *)d1 - ((struct cls_t *)d2)->age;
}
int sort_age(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->age - ((struct cls_t *)d2)->age;
}
int cmp_sex(void *d1, void *d2)
{
	return *(char *)d1 - ((struct cls_t *)d2)->sex;
}
int sort_sex(void *d1, void *d2)
{
	return ((struct cls_t *)d1)->sex - ((struct cls_t *)d2)->sex;
}
int cmp_cn(void *d1, void *d2)
{
	float ret;
	ret = *(float *)d1 - ((struct cls_t *)d2)->cn;

	/*printf("ret = %f\n", ret);*/

	if (ret < 0.005 && ret > -0.005)
		return 0;
	else if (ret > 0.005)
		return 1;
	else if (ret < -0.005)
		return -1;
}
int sort_cn(void *d1, void *d2)
{
	float ret;
	ret = ((struct cls_t *)d1)->cn - ((struct cls_t *)d2)->cn;

	if (ret < 0.005 && ret > -0.005)
		return 0;
	else if (ret > 0.005)
		return 1;
	else if (ret < -0.005)
		return -1;
}
int cmp_en(void *d1, void *d2)
{
	return *(float *)d1 - ((struct cls_t *)d2)->en;
}

int main(int argc, char *argv[])
{
	int i;
	DARR *handle = NULL;
	struct cls_t cls = {}, stu = {"lili", 1711059, 19, 'F', 88.88, 99.99};
	int ret;
	int index;
	char name[128];
	int id;
	char sex;
	int age;
	float cn;

	/*srand(time(NULL));*/
	if (argc == 2)
	{
		printf("load : \n");
		handle = darr_load("./stu.db");
		darr_travel(handle, ls);
	}
	else
	{
		//初始化
		handle = darr_creat(sizeof(struct cls_t));
		ERRP(NULL == handle, darr_creat, goto ERR1);

		//建立动态数据 int
		for (i = 0; i < MAX; i++)
		{
			snprintf(cls.name, sizeof(cls.name), "cls_%c%c", rand() % 26 + 'A', rand() % 26 + 'a');
			cls.id = rand() % 100 + 1711000;
			cls.age = rand() % 3 + 20;
			cls.sex = "MF"[rand() % 2];
			cls.cn = rand() / ((double)(RAND_MAX)) * 30 + 70;
			cls.en = rand() / ((double)(RAND_MAX)) * 20 + 80;
			//尾插
			/*ret = darr_append(handle, &cls);*/
			ret = darr_appprev(handle, &cls);
			if (ret == -1)
			{
				break;
			}
		}
		darr_travel(handle, ls);
		printf("==================\n");
		printf("num : %d\n", darr_num(handle));

		printf("id : \n");
		darr_sort(handle, sort_id);
		darr_travel(handle, ls);
		printf("==================\n");

		printf("name : \n");
		darr_sort(handle, sort_name);
		darr_travel(handle, ls);
		printf("==================\n");

		printf("cn : \n");
		darr_sort(handle, sort_cn);
		darr_append(handle, &stu);
		darr_store(handle, "./stu.db");
		printf("sizeof(struct cls_t) = %d\n", sizeof(struct cls_t));
		/*
		 *printf("please input del cn : ");
		 *scanf("%f", &cn);
		 *[>printf("cn : %f\n", cn);<]
		 *darr_front_del(handle, &cn, cmp_cn);
		 */

		/*sex = 'K';*/
		/*age = 20;*/
		/*darr_travel(darr_all_find(handle, &sex, cmp_sex), ls);*/
		/*darr_travel(darr_all_find(handle, &age, cmp_age), ls);*/
		/*
		 *GETLINES("please input del name : ", name);
		 *darr_front_del(handle, name, cmp_name);
		 */
		/*
		 *printf("please input del id : ");
		 *scanf("%c", &sex);
		 *darr_all_del(handle, &sex, cmp_sex);
		 */

	/*
	 *    printf("please input del index : ");
	 *    scanf("%d", &index);
	 *
	 *    darr_index_del(handle,index);
	 */

		/*ls(darr_index_find(handle, 4));*/

		//遍历
		darr_travel(handle, ls);

		//销毁
		darr_destroy(&handle);
	}
	return 0;
ERR1:
	return -1;
}
