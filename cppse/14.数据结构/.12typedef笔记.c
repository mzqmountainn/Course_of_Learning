/*
typedef与define有三处不同
*/
//假设用BYTE表示1字节的数组。只需要像定义个char类型一样定义BYTE，然后咋i定义前加上关键字typedef即可
typedef unsigned char BYTE;
//随后，可用BYTE表示
BYTE x, y[10], * z;
//还可以把typedef用于结构
typedef struct complex {
	float real;
	float imag;
};
