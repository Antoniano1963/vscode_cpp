#include <vector>
#include <algorithm>
#include <string>
#include<iostream>
#include <sstream>
#include<math.h>
#include<deque>
using namespace std;

const int base = 10;//每个单元存一个十进制数，方便以后进行修改
//const int power = 4;   //位数

class big
{
	deque<int> v;
	deque<int> v2;
	bool flag;   //符号位，为1是正数，0是负数
	bool dot;   //记录数字是不是有小数部分
	int count;//记录小数位数的重要值
	int count1;

public:

	//无参构造
	big() {
		v.push_back(0);
		flag = 1;//默认0为正数
	}

	//有参构造
	big(std::string &s) {
		int len, w, t, i;
		len = s.size();
		count = 0;
		count1 = 0;
		bool dot = false;
		for (i = 0; i < len; i++) {//先判断小数位数，并记录到count中，方便后面读取和比较
			if (dot) {
				count++;
			}
			if (s.at(i) == '.') {
				dot = true;
			}
		}
		if (s[0] == '-') {//负数的赋值
			flag = 0;
			reverse(s.begin() + 1, s.end());//逆序存储，v[0]为低四位
			if (dot) {
				for (i = 1, t = -1; i < count + 1; i++) {//读入小数部分，存储到v2
					v2.push_back(0);
					t++;
					v2[t] += (s[i] - '0');
				}
				for (i = count + 2, t = -1; i < len; i++) {//再接着储存整数部分
					v.push_back(0);
					w = 1;
					t++;
					v[t] += (s[i] - '0');
				}
			}
			else {
				for (i = 1, t = -1; i < len; i++) {
					v.push_back(0);
					w = 1;
					t++;
					v[t] += (s[i] - '0');
				}
			}
		}
		else {//正数的赋值
			flag = 1;
			reverse(s.begin(), s.end());
			if (dot) {
				for (i = 0, t = -1; i < count; i++) {//读入小数部分，存储到v2
					v2.push_back(0);
					t++;
					v2[t] += (s[i] - '0');
				}
				for (i = count + 1, t = -1; i < len; i++) {//再接着储存整数部分
					v.push_back(0);
					w = 1;
					t++;
					v[t] += (s[i] - '0');
				}

			}
			else {//这个就是整数部分的输入，很常见
				for (i = 0, t = -1; i < len; i++) {
					v.push_back(0);
					w = 1;
					t++;
					v[t] += (s[i] - '0');
				}
			}
		}
	}

	//输出函数
	string print() {
		string s("\0"), s1;
		std::ostringstream oss;
		int a;
		if (v[0] == base) s = "ERROR";//用来检测是不是程序出了问题
		else {
			if (flag == 0) s = s + "-";//若答案符号位为负，则先输出一个负号
			int n = v.size() - 1;//逆序输出，从尾部（最高位）开始
			oss.str("");
			for (; n >= 0; n--) {//先输出整数部分
				a = v[n];
				oss << a;
				s1 = oss.str();
				oss.str("");
				s = s + s1;
			}
			if (!v2.empty()) {
				s += ".";//加一个小数点接着输出小数部分
				n = v2.size() - 1;
				for (; n >= 0; n--) {
					a = v2[n];
					oss << a;
					s1 = oss.str();
					oss.str("");
					s = s + s1;
				}
			}
		}
		return s;
	}
	bool operator >= (const big &x) {
		int i = v.size(), j = x.v.size(), n;
		if (flag == 1 && x.flag == 0) return 1;//符号位不同可直接判断
		if (flag == 0 && x.flag == 1) return 0;
		if (flag == 1 && x.flag == 1) {//均为正数时
			if (i < j) return 0;
			if (i > j) return 1;
			for (n = i - 1; n >= 0; n--) {
				if (v[n] < x.v[n]) return 0;
				if (v[n] > x.v[n]) return 1;
			}
			if (dot) {//如果整数部分比较不了再来比较小数部分
				if (v2.size() > x.v2.size()) {
					return 1;
				}
				if (v2.size() < x.v2.size()) {
					return 0;
				}
				for (n = v2.size() - 1; n >= 0; n--) {
					if (v2[n] < x.v2[n]) {
						return 0;
					}
					if (v2[n] > x.v2[n]) {
						return 1;
					}
				}
			}
			return 1;//最后还没比较出结果，则为相等
		}
		if (i < j) return 0;//均为负数时
		if (i > j) return 1;
		for (n = i - 1; n >= 0; n--) {
			if (v[n] > x.v[n]) return 0;
			if (v[n] < x.v[n]) return 1;
		}
		if (dot) {//还是整数部分比较不出来再比较小数部分
			if (v2.size() > x.v2.size()) {
				return 0;
			}
			if (v2.size() < x.v2.size()) {
				return 1;
			}
			for (n = v2.size() - 1; n >= 0; n--) {
				if (v2[n] < x.v2[n]) {
					return 1;
				}
				if (v2[n] > x.v2[n]) {
					return 0;
				}
			}
		}
		return 1;
	}

	//比较绝对值大小的函数
	bool absolute_larger(const big &y, const big &x)
	{//忽略符号位，只比较vector
		int i = y.v.size(), j = x.v.size(), n;
		if (i < j) return 0;
		if (i > j) return 1;
		for (n = i - 1; n >= 0; n--) {
			if (y.v[n] < x.v[n]) return 0;
			if (y.v[n] > x.v[n]) return 1;
		}
		if (dot) {//整数部分比较不出来再比较小数部分
			if (y.v2.size() > x.v2.size()) {
				return 1;
			}
			if (y.v2.size() < x.v2.size()) {
				return 0;
			}
			for (n = y.v2.size() - 1; n >= 0; n--) {
				if (y.v2[n] < x.v2[n]) {
					return 0;
				}
				if (y.v2[n] > x.v2[n]) {
					return 1;
				}
			}
		}
		return 1;
	}

	//自增运算
	big & operator ++ (int k) {
		int i, n = v.size(), m;
		//负数时
		if (flag == 0) {
			v[0]--;
			for (m = 0; m < n - 1; m++) {
				if (v[m] < 0) {//借位操作
					v[m] += base;
					v[m + 1]--;
				}
			}
			while (v[m] == 0 && m >= 0) {//将高位的零删去
				v.erase(v.end() - 1);
				m--;
			}
			if (m == -1) {//若最后结果为零，则全部被删除，再赋值0
				flag = 1;
				v.push_back(0);
			}
			return *this;
		}
		//正数时
		v[0]++;
		for (i = 0; v[i] == base && i < n - 1; i++) {//进位操作
			v[i + 1]++;
			v[i] = 0;
		}
		if (v[n - 1] == base) {//最后一位的进位需要重新分配空间，单独讨论
			v[n - 1] = 0;
			v.push_back(1);
		}
		return *this;
	}

	//加法运算
	big operator + (const big &x) {
		int i = v.size(), j = x.v.size(), n, m;
		big ans;
		//异号时
		if (flag != x.flag) {
			if (absolute_larger(*this, x)) {//当this绝对值>=x大时
				ans = *this;//用this-x计算，答案符号与绝对值较大的数（this）一致，不用管flag
				for (n = 0; n < j; n++) {
					ans.v[n] -= x.v[n];
				}
				if (count != 0 || x.count != 0) {//判断是不是有小数
					if (count < x.count) {//然后开始减
						for (int k = 0; k < x.count - count; k++) {
							ans.v2.push_front(0);//如果被减数的小数位数比整数小，就要加0进行补位
						}
						for (int k = 0; k < x.count; k++) {
							ans.v2[k] -= x.v2[k];
						}
						for (int k = 0; k < x.count - 1; k++) {
							if (ans.v2[k] < 0) {
								ans.v2[k] += 10;
								ans.v2[k + 1]--;
							}
						}
						if (ans.v2[x.count - 1] < 0) {
							ans.v2[x.count - 1] += 10;
							ans.v[0]--;
						}
					}
					else {
						for (int k = count - x.count, o = 0; k < count; k++, o++) {//被减数小数位数比较大的时候就可以直接减，但是要注意对齐
							ans.v2[k] -= x.v2[o];
						}
						for (int k = 0; k < count - 1; k++) {
							if (ans.v2[k] < 0) {
								ans.v2[k] += 10;
								ans.v2[k + 1]--;
							}
						}
						if (ans.v2[count - 1] < 0) {
							ans.v2[count - 1] += 10;
							ans.v[0]--;
						}
					}
				}
				for (m = 0; m < i - 1; m++) {
					if (ans.v[m] < 0) {
						ans.v[m] += base;
						ans.v[m + 1]--;
					}
				}
				while (ans.v[m] == 0 && m > 0) {
					ans.v.erase(ans.v.end() - 1);
					m--;
				}
				if (ans.v.size() == 1 && ans.v[0] == 0) ans.flag = 1;//若结果为0，则重新赋值符号位
				return ans;
			}
			else {//当this绝对值比x小时
				ans = x;//用x-this计算，答案符号与绝对值较大的数（x）一致，不用管flag
				for (n = 0; n < i; n++) {
					ans.v[n] -= v[n];
				}
				if (count != 0 || x.count != 0) {//同减法的处理
					if (count > x.count) {
						for (int k = 0; k < count - x.count; k++) {
							ans.v2.push_front(0);
						}
						for (int k = 0; k < count; k++) {
							ans.v2[k] -= v2[k];
						}
						for (int k = 0; k < count - 1; k++) {
							if (ans.v2[k] < 0) {
								ans.v2[k] += 10;
								ans.v2[k + 1]--;
							}
						}
						if (ans.v2[count - 1] < 0) {
							ans.v2[count - 1] += 10;
							ans.v[0]--;
						}
					}
					else {
						for (int k = x.count - count, o = 0; k < x.count; k++, o++) {
							ans.v2[k] -= v2[o];
						}
						for (int k = 0; k < x.count - 1; k++) {
							if (ans.v2[k] < 0) {
								ans.v2[k] += 10;
								ans.v2[k + 1]--;
							}
						}
						if (ans.v2[x.count - 1] < 0) {
							ans.v2[x.count - 1] += 10;
							ans.v[0]--;
						}
					}
				}
				for (m = 0; m < j - 1; m++) {
					if (ans.v[m] < 0) {
						ans.v[m] += base;
						ans.v[m + 1]--;
					}
				}
				while (ans.v[m] == 0 && m > 0) {
					ans.v.erase(ans.v.end() - 1);
					m--;
				}
				return ans;//这里两数绝对值是大于，而不是大于等于关系，不必考虑0的情况
			}
		}
		//同号时
		ans.flag = flag;
		if (i >= j) {//绝对值较大的数作为基数，符号位不变
			ans = *this;
			if (count != 0 || x.count != 0) {
				if (x.count == 0) {
					ans.v2.assign(v2.begin(), v2.end());
				}
				else if (count == 0) {
					ans.v2.assign(x.v2.begin(), x.v2.end());
				}
				else {//都有小数的时候
					if (count > x.count) {
						ans.v2.assign(v2.begin(), v2.end());
						for (int k = (count - x.count), o = 0; k < count; k++, o++) {
							ans.v2[k] += x.v2[o];
						}
						for (int k = 0; k < count - 1; k++) {
							ans.v2[k + 1] += ans.v2[k] / 10;
							ans.v2[k] %= 10;
						}
						if (ans.v2[count - 1] >= 10) {
							ans.v[0] += ans.v2[count - 1] / 10;
							ans.v2[count - 1] %= 10;
						}
					}
					else {
						ans.v2.assign(x.v2.begin(), x.v2.end());
						for (int k = (x.count - count), o = 0; k < x.count; k++, o++) {
							ans.v2[k] += v2[o];
						}
						for (int k = 0; k < x.count - 1; k++) {
							ans.v2[k + 1] += ans.v2[k] / 10;
							ans.v2[k] %= 10;
						}if (ans.v2[x.count - 1] >= 10) {
							ans.v[0] += ans.v2[x.count - 1] / 10;
							ans.v2[x.count - 1] %= 10;
						}
					}
				}
			}
			for (n = 0; n < j; n++) {
				ans.v[n] += x.v[n];
			}
			for (m = 0; m < i - 1; m++) {//进位
				ans.v[m + 1] += ans.v[m] / base;
				ans.v[m] %= base;
			}
			while (ans.v[i - 1] >= base) {//最后一位的进位需要重新分配空间，单独讨论
				ans.v.push_back(ans.v[i - 1] / base);
				ans.v[i - 1] %= base;
				i++;
			}
		}
		if (i < j) {
			ans = x;
			if (count != 0 || x.count != 0) {
				if (x.count == 0) {
					ans.v2.assign(v2.begin(), v2.end());
				}
				else if (count == 0) {
					ans.v2.assign(x.v2.begin(), x.v2.end());
				}
				else {//都有小数的时候
					if (count1 > x.count1) {//比较谁的小数位数多
						ans.v2.assign(v2.begin(), v2.end());
						for (int k = (count - x.count), o = 0; k < count; k++, o++) {
							ans.v2[k] += x.v2[o];
						}
						for (int k = 0; k < count - 1; k++) {
							ans.v2[k + 1] += ans.v2[k] / 10;
							ans.v2[k] %= 10;
						}
						if (ans.v2[count - 1] >= 10) {
							ans.v[0] += ans.v2[count - 1] / 10;
							ans.v2[count - 1] %= 10;
						}
					}
					else {
						ans.v2.assign(x.v2.begin(), x.v2.end());
						for (int k = (x.count - count), o = 0; k < x.count; k++, o++) {
							ans.v2[k] += v2[o];
						}
						for (int k = 0; k < x.count - 1; k++) {
							ans.v2[k + 1] += ans.v2[k] / 10;
							ans.v2[k] %= 10;
						}if (ans.v2[x.count - 1] >= 10) {
							ans.v[0] += ans.v2[x.count - 1] / 10;
							ans.v2[x.count - 1] %= 10;
						}
					}
				}
			}
			for (n = 0; n < i; n++) {
				ans.v[n] += v[n];
			}
			for (m = 0; m < j - 1; m++) {//进位
				ans.v[m + 1] += ans.v[m] / base;
				ans.v[m] %= base;
			}
			while (ans.v[j - 1] >= base) {//最后一位的进位需要重新分配空间，单独讨论
				ans.v.push_back(ans.v[j - 1] / base);
				ans.v[j - 1] %= base;
				j++;
			}
		}
		m = ans.v2.size() - 1;
		if (m > -1) {
			while (ans.v2[m] == 0 && m > 0) {
				ans.v2.erase(ans.v2.end() - 1);
				m--;
			}
		}
		return ans;
	}

	//减法运算
	big operator - (const big &x) {
		big ans;
		int i = v.size(), j = x.v.size(), n, m;
		//异号时
		if (flag != x.flag) {//符号不一致时，两数绝对值相加，符号位与被减数一致
			ans = (*this) + x;
			ans.flag = flag;//无论绝对值大小，答案符号位与被减数一致
			return ans;
		}
		//同号时
		if (absolute_larger(*this, x)) {//选取绝对值较大的为被减数
			ans = *this;//符号与新的被减数一致
			for (n = 0; n < j; n++) {
				ans.v[n] -= x.v[n];
			}
			if (count != 0 || x.count != 0) {
				if (count < x.count) {
					for (int k = 0; k < x.count - count; k++) {
						ans.v2.push_front(0);
					}
					for (int k = 0; k < x.count; k++) {
						ans.v2[k] -= x.v2[k];
					}
					for (int k = 0; k < x.count - 1; k++) {
						if (ans.v2[k] < 0) {
							ans.v2[k] += 10;
							ans.v2[k + 1]--;
						}
					}
					if (ans.v2[x.count - 1] < 0) {
						ans.v2[x.count - 1] += 10;
						ans.v[0]--;
					}
				}
				else {
					for (int k = count - x.count, o = 0; k < count; k++, o++) {
						ans.v2[k] -= x.v2[o];
					}
					for (int k = 0; k < count - 1; k++) {
						if (ans.v2[k] < 0) {
							ans.v2[k] += 10;
							ans.v2[k + 1]--;
						}
					}
					if (ans.v2[count - 1] < 0) {
						ans.v2[count - 1] += 10;
						ans.v[0]--;
					}
				}
			}
			for (m = 0; m < i - 1; m++) {
				if (ans.v[m] < 0) {//借位
					ans.v[m] += base;
					ans.v[m + 1]--;
				}
			}
			while (ans.v[m] == 0 && m > 0) {//从最后一位开始检查是否为零，将高位零删去（不检查v[0]是否为0）
				ans.v.erase(ans.v.end() - 1);
				m--;
			}
		}
		else {
			ans = x;//暂定符号与新的被减数一致，但由于顺序与原题相反，最后会改变
			for (n = 0; n < i; n++) {
				ans.v[n] -= v[n];
			}
			if (count != 0 || x.count != 0) {
				if (count > x.count) {
					for (int k = 0; k < count - x.count; k++) {
						ans.v2.push_front(0);
					}
					for (int k = 0; k < count; k++) {
						ans.v2[k] -= v2[k];
					}
					for (int k = 0; k < count - 1; k++) {
						if (ans.v2[k] < 0) {
							ans.v2[k] += 10;
							ans.v2[k + 1]--;
						}
					}
					if (ans.v2[count - 1] < 0) {
						ans.v2[count - 1] += 10;
						ans.v[0]--;
					}
				}
				else {
					for (int k = x.count - count, o = 0; k < x.count; k++, o++) {
						ans.v2[k] -= v2[o];
					}
					for (int k = 0; k < x.count - 1; k++) {
						if (ans.v2[k] < 0) {
							ans.v2[k] += 10;
							ans.v2[k + 1]--;
						}
					}
					if (ans.v2[x.count - 1] < 0) {
						ans.v2[x.count - 1] += 10;
						ans.v[0]--;
					}
				}
			}
			for (m = 0; m < j - 1; m++) {
				if (ans.v[m] < 0) {
					ans.v[m] += base;
					ans.v[m + 1]--;
				}
			}
			while (ans.v[m] == 0 && m > 0) {//擦去零
				ans.v.erase(ans.v.end() - 1);
				m--;
			}
			ans.flag = !ans.flag;//与原数相减顺序不同，改变符号位
		}
		return ans;
	}
	int operator_divide(const big &x, const big &y) {
		big beichushu = x, chushu = y;
		int countnum = 0, countnum1 = 0;
		if ((y.v.size() == 1 && y.v[0] == 0) && (y.count == 0)) {
			return 0;
		}
		beichushu.flag = 1;//将两数绝对值，算出答案后再添加符号位
		chushu.flag = 1;
		while (beichushu >= chushu) {
			countnum++;//记录相减的次数
			beichushu = beichushu - chushu;
		}
		return countnum;
	}

	//除法运算
	big operator / (const big &x) {
		big ans, chushu = x;
		int countnum = 0, countnum1 = 0;
		if ((x.v.size() == 1 && x.v[0] == 0) && (x.count == 0)) {
			ans.v[0] = base;//除数为零，输入不合法，设定为base后输出函数会输出error
			return ans;
		}
		chushu.flag = 1;
		int num4 = v2.size() - 1;
		int num5 = chushu.v2.size();
		for (int i = 0; i < num5; i++) {//把除数的小数位数全部变成0方便处理，即被除数和除数同时进位实现
			if (num4 > -1) {
				v.push_front(v2[v2.size() - 1]);
				v2.erase(v2.end() - 1);
				v2.push_front(0);
			}
			else {
				v.push_front(0);
			}
			num4--;
			chushu.v.push_front(chushu.v2[chushu.v2.size() - 1]);
			chushu.v2.erase(chushu.v2.end() - 1);
			chushu.v2.push_front(0);
		}
		int num8 = v.size() - 1;
		while (num8 > 0 && v[num8] == 0) {//擦去除数和被除数前面多余的0，避免函数在比较大小的时候出现问题。
			v.erase(v.end() - 1);
			num8--;
		}
		int num9 = v2.size() - 1;
		while (num9 > count&&v2[num9] == 0) {
			v2.erase(v2.end() - 1);
			num9--;
		}
		big beichushu = *this;
		beichushu.flag = 1;
		int num7 = chushu.v.size() - 1;
		while (num7 > 0 && chushu.v[num7] == 0) {
			chushu.v.erase(chushu.v.end()-1);
			num7--;
		}
		chushu.count = 0;
		chushu.v2.clear();
		if (beichushu >= chushu) {//如果被除数比除数大，就是有整数部分，先进行整数部分的计算
			int m = v.size() - 1;
			string str0 = to_string(v[m]);
			m--;
			bool T = true;
			if (big(str0) >= chushu)
			{
				T = false;
			}
			while (T)
			{
				str0 += to_string(v[m]);
				if (big(str0) >= chushu)
				{
					T = false;
				}
				m--;
				reverse(str0.begin(), str0.end());
			}
			beichushu = big(str0);
			while (m >-2)
			{
				int num0 = operator_divide(beichushu, chushu);
				ans.v.push_front(num0);
				for (int i = 0; i < num0; i++)
				{
					beichushu = beichushu - chushu;
				}
				if (m < 0) {
					break;
				}
				beichushu.v.push_front(0);
				string str1 = to_string(v[m]);
				beichushu = beichushu + big(str1);
				m--;
			}
		}
		beichushu.v2 = v2;//算完整数部分后进入小数部分的计算，将小数部分整个都交给被除数，然后开始依次计算
		beichushu.count = count;
		beichushu.count1 = count1;
		for (int i = 0; i < 12; i++) {
			int num3 = beichushu.v2.size() - i;
			if (num3 > 0) {
				beichushu.v.push_front(beichushu.v2[beichushu.v2.size() - 1]);
				beichushu.v2.erase(beichushu.v2.end() - 1);
				beichushu.v2.push_front(0);
			}
			else {
				beichushu.v.push_front(0);
			}
			int m = beichushu.v.size() - 1;
			while (m > 0 && beichushu.v[m] == 0)
			{
				beichushu.v.erase(beichushu.v.end() - 1);
				m--;
			}

			int num = operator_divide(beichushu, chushu);
			ans.v2.push_front(operator_divide(beichushu, chushu));
			for (int j = 0; j < num; j++) {
				beichushu = beichushu - chushu;
			}

		}

		if (flag != x.flag)
			ans.flag = 0; //符号不同结果为负
		else
			ans.flag = 1;                                //符号相同结果为正
		if (ans.v.size() == 1 && ans.v[0] == 0) ans.flag = 1;//若结果为0，符号位置1
		return ans;
	}

	//取模运算
	big operator % (const big &x) {
		big ans, chushu = x;
		if ((x.v.size() == 1 && x.v[0] == 0) && (x.count == 0)) {
			ans.v[0] = base;//除数为零，输入不合法，设定为base后输出函数会输出error
			return ans;
		}
		ans = *this;
		ans.flag = 1;//将两数绝对值，求出答案后再添加符号
		chushu.flag = 1;
		while (ans >= chushu) ans = ans - chushu;
		ans.flag = flag;//符号与被除数一致
		return ans;
	}

	//乘法运算
	big operator * (const big &x) {
		big ans;
		int m = v.size(), n = x.v.size(), i, j;
		int num1 = v2.size(), num2 = x.v2.size();
		deque<int> v3;
		deque<int> v4;
		deque<int> v5;
		v3.insert(v3.end(), m + v2.size(), 0);
		v4.insert(v4.end(), n + x.v2.size(), 0);
		v5.insert(v5.end(), m + n + num1 + num2, 0);
		ans.v.insert(ans.v.end(), m + n, 0);
		ans.v2.insert(ans.v2.end(), num1 + num2, 0);
		for (int i = 0; i < v2.size(); i++)
		{
			v3[i] = v2[i];
		}
		for (int i = 0; i < m; i++) {
			v3[i + v2.size()] = v[i];
		}
		for (int i = 0; i < x.v2.size(); i++) {
			v4[i] = x.v2[i];
		}
		for (int i = 0; i < n; i++) {
			v4[i + x.v2.size()] = x.v[i];
		}
		///////ans.v.insert(ans.v.end(), m + n, 0); //先使答案的位数为两个乘数位数和+1，全部置零
		for (j = 0; j < v3.size(); j++) {
			for (i = 0; i < v4.size(); i++) {
				v5[j + i] += v3[j] * v4[i];
			}
		}
		for (j = 0; j < v5.size() - 1; j++) {
			v5[j + 1] += v5[j] / 10;
			v5[j] %= 10;
		}
		for (j = 0; j < ans.v2.size(); j++) {
			ans.v2[j] = v5[j];
		}
		for (j = num1 + num2; j < v5.size(); j++) {
			ans.v[j - num1 - num2] = v5[j];
		}
		n = ans.v.size() - 1;
		while (ans.v[n] == 0 && n > 0) {//从最后一位开始检查是否为零，将高位零删去（不检查v[0]是否为0）
			ans.v.erase(ans.v.end() - 1);
			n--;
		}
		if (flag != x.flag) ans.flag = 0;//符号不同结果为负
		else ans.flag = 1;//符号相同结果为正
		if (ans.v.size() == 1 && ans.v[0] == 0) ans.flag = 1;//若结果为0，符号位置1
		return ans;
	}
};