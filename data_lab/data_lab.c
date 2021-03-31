int bitAnd(int x, int y) {     //用取反运算和或运算完成对与的操作
    return ~((~x)|(~y));   //逻辑门的公式 
}

int getByte(int x, int n){
    return (x>>(n>>3))&0xff; //获取第n个字节，即8*n ~ 8*(n+1)位的数字放在最低位返回
}

int logicalShift(int x, int n){     //逻辑右移
    int a = 1;                      //注意有符号数是算数右移，需要添加额外操作
    return (x>>n)&~(((a<<31)>>n)<<1);//注意a不能直接使用32进行移位，因为这样就变成0，因此先左移31位，右移n位后在左移1位，这样a的结果就是000..1111111。
}

int bitCount(int v){        //计算一个三十二位的整数中有位是1的数量（属实是难到我了）
    int i;//采用分治的思想
    //计算每两位二进制数中1的个数（都保存在各自的位里）
    i = ( i & 0x55555555) + ((i >> 1) & 0x55555555);
    //计算每四位二进制数中1的个数
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    //计算每八位二进制数中1的个数
    i = (i & 0x0F0F0F0F) + ((i >> 4) & 0x0F0F0F0F);
    //将每八位二进制数中1的个数和相加，并移至最低位八位
    i = (i * 0x01010101) >> 24);  //0x01010101*i后，i的高8位即结果
    return i;
}

int bang(int x){
    return ((x|(~x+1))>>31)&1;//对于其它数字，其正数和相反数相或后其最高位为1，对于0，其正数和相反数相或后其最高位为0
}


int tmin(void){
    return 1<<31;       //送分题
}


int fitsBits(int x, int n){//判断是否可以用n位数字容纳x的值
    return !(((x>>(n+(~0)))+1)>>1);//利用特性：x为负数，则只有前n-1位有0；x为正数，只有前n-1位有1
                                    //因为不能用‘-’号，n+~0的结果为n-1。
                                    //若x为负数，且能用n位来容纳，那么x>>(n-1)位后，结果为-1，加1后结果为0。！后结果为1；若不能用n位来容纳，那么x>>(n-1)位后，结果小于-1，+1后仍为负数.右移1位再取！结果为0
                                    //若x为正数，且能用n位来容纳，那么x>>(n-1)位后，结果为0，加1后结果为1，右移1位后结果为0，取！结果为1；若不能用n位来容纳，那么x>>(n-1)位后，结果大于等于1，加1后大于等于2，右移1位大于等于1，取！结果为0
}

int divpwr2(int x, int n){//输出x/2^n
    return (x + ((x >> 31) & ((1 << n) + ~0))) >> n; //主要注意正数向下取整，负数向上取整，因此如果为负数，需要添加2^n-1.
}


int negate(int x){
    return (~x)+1;      //相反数，送分题
}

int isPositive(int x){//判断该数是否是正数
    return !(((x>>31)&1)|(!x));//对于正数，(x>>31)&1为0，!x为0，两者相或再取!为1
                                //对于负数,(x>>31)&1为1，两者相或取非为0
                                //对于0，(x>>31)&1为0，!x为1，两者相或取非后为0
}

int isLessOrEqual(int x, int y){
    int diff_sgn = !(x >> 31) ^ !(y >> 31);       // 当结果为1时，说明符号不同
    int a = diff_sgn & (x >> 31);                 // 若x是负数，且x,y符号不同,a=1,即x<y
    int b = !diff_sgn & !((y + (~x + 1)) >> 31);  // 若两数符号相同，则用x-y计算结果判断正负,若两数符号不同，则为0
    int f = a | b;
    return f;
}

int ilog2(int x){//这道题也属实难到我了
	int y = 0;//运用分治思想
	y = (!!(x >> 16)) << 4;//如果x在十六位以上有数字，则加16，否则为0
	y = y + ((!!(x >> (y + 8))) << 3);//继续之前的情况，如果x在y+8位以上有数字，则+8，否则+0
	y = y + ((!!(x >> (y + 4))) << 2);//同上
	y = y + ((!!(x >> (y + 2))) << 1);//同上
	y = y + (!!(x >> (y + 1)));//同上
	return y;
}

unsigned float_neg(unsigned uf){    //判断浮点数的相反数
    unsigned int b = uf&0x7fffffff; 
    unsigned int c = 0x7f800000;
    if(b>c)     //判断是否是NaN
        return uf;
    return uf^0x80000000;//不是NaN则符号位取反后返回
}

unsigned float_i2f(int x){//整数转浮点数
    int sign=(x>>31)&1; //符号位
    int exp;//阶码
    int frac;//小数字段
    if(x==0)        //浮点数如果为0，直接返回
        return x;
    if(x==0x80000000)//因为最大的负值的按位取反加1后仍为原数值，需要先行处理
        return 0xCF000000;
    if(sign)
        x = ~x+1;//转换成正数来处理
    int bits=1;     
    while((x>>bits)!=0)//计算x中位数为1的最大位置
        bits++;
    bits--;
    exp=127+bits;   //确定exp
    x=x<<(31-bits);//这两步主要得到frac的初值
    frac=(x>>8)&0x007fffff;
    if(bits>23)//若位数大于23，需要进行舍入操作
    {
        unsigned int a = (x>>7)&1;//得到离舍入位最近的位的值
        if(a && (frac&1))//如果a为1且frac的第0位为1
            frac+=1;
        if((frac>>23))//可能溢出
        {
            frac=0;
            exp+=1;
        }
    }
    return sign<<31 | exp<<23 | frac; 
}

unsigned float_twice(unsigned uf){//浮点数*2
    int sign=(uf>>31)&1;//符号位
    int exp=(uf>>23)&0xff;//exp
    int frac=uf&0x7fffff;//小数部分
    if(exp==255||exp==254)//如果是无穷大或者NaN,返回原值，如果是exp是254，乘2后出现问题，也直接返回原址
        return uf;
    if(exp==0)//如果是非规格化部分
    {
        frac=frac*2;//小数部分乘2，即使溢出了，表示仍相同
    }
    else 
        exp++;
    return sign<<31 | (exp)<<23 | frac;
}