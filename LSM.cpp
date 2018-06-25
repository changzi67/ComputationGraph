#include "LSM.h"


std::pair<double, double> LSM(const std::vector<std::pair<double, double> >& points){
	std::vector<Node* > x(points.size());
	std::vector<Node* > y(points.size());
	std::vector<Node* > res(points.size());
	for(int i = 0;i<points.size();++i){
		x[i] = new Constant(points[i].first);
		y[i] = new Constant(points[i].second);
	}
	auto a = Placeholder("a");
	auto b = Placeholder("b");
	for(int i = 0;i<x.size();++i) {
		res[i] = &( *y[i] - ( a * *x[i] + b ) );
	}
	Node * temp = new Constant(0);
	for(int i = 0; i < res.size();++i){
		temp = & (*temp + *res[i] * *res[i]);
	}
	temp = &(*temp / (* new Constant(res.size())));

	double A = 0, B = 0;
	auto g = temp->Grad();
	double cur = temp->Eval({ {"a", A} , {"b",B} });
	double prev;
	double eps = 1e-12;

	//std::cerr<<cur<<std::endl;

	do {
		double cnt = 1;
		double alpha = .01;
		alpha = (double)cnt/(cnt+1) * alpha;
		prev = cur;
	//std::cerr<< static_cast<double>(g[a].Eval({ {"a", A} , {"b",B} }) )<<std::endl;
		double tempA = alpha * static_cast<double>(g[a].Eval({ {"a", A} , {"b",B} }) );
		double tempB = alpha * static_cast<double>( g[b].Eval({{"a",A}, {"b",B}}) );
	//std::cerr<<A<<' '<<B<<std::endl;
		cur = temp->Eval({ {"a", A-tempA} , {"b",B-tempB} });
		if(cur < prev)A-=tempA,B-=tempB;
	std::cerr<<"cur:"<<cur<<std::endl;
		cnt++;
	} while( fabs(cur-prev)>eps );

	return std::make_pair(A,B);
}
