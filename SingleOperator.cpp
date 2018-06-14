#include "SingleOperator.h"

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

