#include "Meow.h" 
#include "Newton.h"
#include <bits/stdc++.h> 
int main() 
{
	/*auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto t1 = x * y;
	auto t4 = Ln(x);
	auto t5 = t4 / t1;
	auto t2 = x * t1 + y;
	auto t3 = y * t2 + x;
	auto L = t1 * t2 + t3;
	auto g = t5.Grad();
	auto res = g[x] + g[y];         //如果试图用方括号圈出一个常量或无关变量，会有错误信息。
	std::cout << g[x].Eval({{"x", 3}, {"y", 2}}).Print()<< std::endl;
	//std::cout << Solve({1,0,3,2,1,1}) <<std::endl;*/

	/*auto x = Placeholder("x");
	auto y = Placeholder("y");
	auto z = Sin(x * y);
	auto g = z.Grad();
	std::cout << g[x].Eval({{"x", 3}, {"y", 2}}).Print()<< std::endl;
*/
	auto x = Placeholder("x");
    auto y = Placeholder("y");
    auto z = Constant(3);
    auto z1 = Sin(z);
    auto z2 = Ln(y);
    auto t = z1 + z2;
    auto x2 = Exp(x);
    auto res = t * x2;
    std::cout << res.Eval({{"x", 1}, {"y", 3}}).Print()<< std::endl;
    auto test =Assert( x > z );
    auto test2 = Bind (t, test);
    auto test3 = x>z;
    std::cout << t.Eval({{"x", 1}, {"y", 0.01}}).Print()<< std::endl;
    std::cout << test2.Eval({{"x", 1}, {"y", 0.01}}).Print()<< std::endl;
    return 0;
}
