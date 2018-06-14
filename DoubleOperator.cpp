#include "DoubleOperator.h"
#include "Constant.h"
#include "Meow.h"

void Add::Judge(const Tensor& A,const Tensor& B)const
{
	if(A.Type()!=B.Type()||(A.Type()&&(A.N()!=B.N()||A.M()!=B.M())))
		throw std::invalid_argument("Error : Add node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Add::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A+B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Add::grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t)
{
    grads[a].insert(&t);
	grads[b].insert(&t);

    a->grad(grads, t);
    b->grad(grads, t);
}

void Add::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Sub
void Sub::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()!=B.Type()||(A.Type()&&(A.N()!=B.N()||A.M()!=B.M())))
		throw std::invalid_argument("Error : Sub node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Sub::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A-B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}		
	}
	return *value;
}

void Sub::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}

//Mul
void Mul::grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t)
{
    grads[a].insert(&(t * (*b)));
	grads[b].insert(&((*a) * t));
	a->grad(grads, t * (*b));
	b->grad(grads, t * (*a));
}

void Mul::Judge(const Tensor& A,const Tensor& B) 
{
	if(A.Type()&&B.Type()&&A.M()!=B.N())
		throw std::invalid_argument("Error : Mul node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Mul::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A*B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Mul::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//Div
void Div::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Div node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Div::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(A/B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Div::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
//Pow
void Pow::Judge(const Tensor& A,const Tensor& B) 
{
	if(B.Type())
		throw std::invalid_argument("Error : Pow node \""+name+"\" try to get value from "+a->Name()+"("+A.PrintType()+") and "+b->Name()+"("+B.PrintType()+") !");
}

Tensor Pow::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		Judge(A,B);
		value=new Tensor(pow(A,B));
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Pow::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}


Tensor Less::eval(std::map<std::string,Tensor>& Inputs)
{
	if(value==nullptr)
	{
		Tensor A=a->eval(Inputs);
		Tensor B=b->eval(Inputs);
		//Judge(A,B);
		value=new Tensor(A<B);
		if(debug)
		{
			std::cout<<"Print Operator:"<<name<<"("<<value->PrintType()<<")="<<Expr()<<'\n';
			std::cout<<value->Print()<<'\n';
		}	
	}
	return *value;
}

void Less::grad(std::map<Node*, std::multiset<Node*>>& grads, Node& t)
{
	//emmmm……暂时不知道咋整
	//单位冲激是对的然而炼丹的时候也没用
	//就当它是零吧
}

void Less::Release()
{
	a->Release();
	b->Release();
	if(value!=nullptr)
	{
		delete value;
		value=nullptr;
	}
}
