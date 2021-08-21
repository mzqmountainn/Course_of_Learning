//匿名结构（c11）
//C11中，可以用嵌套的匿名成员结构定义person
struct person
{
	int id;
	struct
	{
		char first[20];
		char last[20];
	};
};

//初始化ted

struct person ted = { 8899,{"ted","garamm"} };
//访问ted
puts(ted.first);