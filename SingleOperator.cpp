#include "SingleOperator.h"
#include "Constant.h"
#include "DoubleOperator.h"

Node& Gra::operator[](Node &graded) {
	if (grads.find(&graded) == grads.end())
	{
		throw std::domain_error("The Node in the square bracket is constant or not related.");
	}
	else
	{
		return *grads[&graded];
	}
}

Tensor SingleOperator::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		value=calc(A);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

Tensor* Quadratic::calc(const Tensor& A)
{
	if(!(A.Type()))
		throw std::invalid_argument("Error : Quadratic_Cost node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") !");
	return new Tensor(A.Quadratic_Cost());
}

Tensor* Sigmoid::calc(const Tensor& A)
{
	Tensor *tmp=new Tensor(A);
	tmp->Sigmoid();
	return tmp;
}

Tensor* Transpose::calc(const Tensor& A)
{
	if(!A.Type())
		throw std::invalid_argument("Error : Transpose node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") !");
	Tensor *tmp=new Tensor(A.M(),A.N());
	tmp->Transpose(A);
	return tmp;
}

void Ln::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Constant(1);
	grads[a].insert(&(t * (*temp / *a)));
	a->grad(grads, t * (*temp / *a));
}

void Sin::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Cos(*a);
	grads[a].insert(&(t * *temp));
	a->grad(grads, t * *temp);
}

void Cos::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp1 = new Sin(*a);
	Node * temp2 = new Constant(-1);
	grads[a].insert(&(t * *temp1 * *temp2));
	a->grad(grads, t * *temp1 * *temp2);
}

void Exp::grad(std::map<Node *, std::multiset<Node *>> & grads, Node & t) {
	Node * temp = new Exp(*a);
	grads[a].insert(&(t * *temp));
	a->grad(grads, t * *temp);
}