#include "Meow.h" 
#include "Newton.h"
#include <bits/stdc++.h> 
int main() 
{
	auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto t1 = x * y;
	auto t2 = x * t1 + y;
	auto t3 = y * t2 + x;
	auto L = t1 * t2 + t3;
	auto g = L.Grad();
	auto res = g[x] + g[y];         //如果试图用方括号圈出一个常量或无关变量，会有错误信息。
	std::cout << res.Eval({{"x", 2}, {"y", 3}}).Print() << std::endl;
	std::cout << Solve({1,0,3,2,1,1}) <<std::endl;
}
