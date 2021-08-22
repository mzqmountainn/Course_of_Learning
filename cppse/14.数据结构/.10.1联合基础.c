//联合是一种数据类型，典型用法是设计一种表以存储既无规律、实现也不知道顺序的混合类型。
//创建联合的的方法与创建结构一样
union hold
{
	int digit;
	double bifdl;
	char letter;
};
//下面定义了3个与hold类型相关的变量
union hold fit;//hold类型的联合变量+
union hold save[10];//内涵10个联合变量的数组
union hold* pu;//指向hold类型联合变量的指针
//注意：联合只能存储一个值，这与结构并不同
//以下为初始化方法
union hold valA;
valA.letter = 'r';
union hold valB =valA
union hold valC = {88}
union hold valD = { .bigfl = 118.2 };
//联合的简单用法
fit.digit = 23;//占2字节
fit.bidfl = 2.0//清楚23，因为联合只能存储一个值，占8字节
//用指针
pu = &fit;
x = pu->digit;//相当于x=fit.digit
