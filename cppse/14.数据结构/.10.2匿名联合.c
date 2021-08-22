//匿名联合（C11）
/*匿名联合和匿名结构工作原理相同
 匿名联合是一个结构或联合的无名联合成员*/
//实例
struct owner
{
	char s1
};
struct s2
{
	char name[40];
	char headquaters[40]
};

struct car_data
{
	char make[15];
	int status;
	union {
		struct owner owncar;
		struct s2 leasecar;
	};
};