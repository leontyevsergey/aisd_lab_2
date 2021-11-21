#include<iostream>
#include<complex>
#include <iomanip>

using namespace std;

template <class T> class Polynomial
{
	struct Node
	{
		int deg;
		T coef;
		Node* next;
		Node(int deg, T coef, Node* next = nullptr) :deg(deg), coef(coef), next(next) { }
	};

	Node* _head;

public:
	Polynomial() : _head(nullptr) { }

	Polynomial(const Polynomial& v) : _head(nullptr)
	{
		Node* h = v._head;
		while (h)
		{
			setCoef(h->deg, h->coef);
			h = h->next;
		}
	}

	~Polynomial()
	{
		clear();
	}

	Polynomial& operator=(const Polynomial& v)
	{
		this->clear();
		Node* h = v._head;
		while (h)
		{
			setCoef(h->deg, h->coef);
			h = h->next;
		}
		return *this;
	}

	T operator[](int deg) const
	{
		Node* p = _head;
		while (p)
		{
			if (p->deg == deg)
				return p->coef;
			p = p->next;
		}
		return 0;
	}

	void setCoef(int deg, T coef)
	{
		if (deg < 0)
			throw "enter degree >= 0!";
		bool exists = false;
		Node* p = _head;
		while (p) {
			if (p->deg == deg)
			{
				if (coef == (T)0) {
					Node* tmp = _head;
					if (tmp->next != NULL)
					{
						while (tmp->next->deg != deg)
						{
							tmp = tmp->next;
						}
						tmp->next = p->next;
						delete p;
					}
					else
						delete tmp;
				}
				else
					p->coef = coef;
				exists = true;
				break;
			}
			p = p->next;
		}
		if (!exists) {
			if (coef != (T)0) {
				_head = new Node(deg, coef, _head);
			}
		}
	}

	void clear()
	{
		while (_head)
		{
			Node* tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}

	Polynomial operator +(const Polynomial<T>& v)
	{
		Node* l = _head;
		Polynomial<T> res = v;
		while (l)
		{
			int a = 0;
			Node* p = res._head;
			while (p)
			{
				if (p->deg == l->deg)
				{
					res.setCoef(l->deg, p->coef + l->coef);
					a = 1;
					break;
				}
				p = p->next;
			}
			if (a == 0)
				res.setCoef(l->deg, l->coef);
			l = l->next;
		}
		return res;
	}

	Polynomial operator *(const T i)
	{
		Node* l = _head;
		Polynomial res;
		while (l)
		{
			res.setCoef(l->deg, i * (l->coef));
			l = l->next;
		}
		return res;
	}

	T calculate(const double x) const
	{
		T a = 0;
		Node* p = _head;
		while (p)
		{
			a = a + (p->coef) * pow(x, p->deg);
			p = p->next;
		}
		return a;
	}

	ostream& operator <<(ostream& out)
	{
		Node* p = _head;
		cout << "f(x)=";
		while (p)
		{
			if (p->next != NULL)
			{
				if (p->deg == 0)
					out << p->coef << "+";

				if (p->deg == 1)
					out << p->coef << "x" << "+";

				if (p->deg != 0 && p->deg != 1)
					out << p->coef << "x^" << p->deg << "+";
			}
			else
			{
				if (p->deg == 0)
					out << p->coef << endl;

				if (p->deg == 1)
					out << p->coef << "x" << endl;

				if (p->deg != 0 && p->deg != 1)
					out << p->coef << "x^" << p->deg << endl;
			}
			p = p->next;
		}
		return out;
	}

	friend  void operator!=(const Polynomial& v, const Polynomial& u)
	{
		int test = 0;
		Polynomial a = v - u;
		Node* h = a._head;
		while (h)
		{
			if (h->coef != (T)0)
			{
				return false;
				test = 1;
				break;
			}
			h = h->next;
		}
		return true;
	}

	friend Polynomial operator -(const Polynomial& v, const Polynomial& u)
	{
		Node* l = u._head;
		Polynomial res = v;
		while (l) {
			int a = 0;
			Node* p = res._head;
			while (p)
			{
				if (p->deg == l->deg)
				{
					res.setCoef(l->deg, p->coef - l->coef);
					a = 1;
					break;
				}
				p = p->next;
			}
			if (a == 0)
				res.setCoef(l->deg, -(l->coef));
			l = l->next;
		}
		return res;
	}

	friend Polynomial<T> operator *(const T i, const Polynomial<T>& v)
	{
		Node* l = v._head;
		Polynomial res;
		while (l)
		{
			res.setCoef(l->deg, i * (l->coef));
			l = l->next;
		}
		return res;
	}
};

int main()
{
	Polynomial<int> a;
	Polynomial<int> b;
	Polynomial<float> c;
	Polynomial<float> d;
	Polynomial<complex<double>> e;
	Polynomial<complex<double>> f;
	std::complex<double> y(1.345, 1.32);
	std::complex<double> x = 3.24 - 3.56i;
	try
	{
		cout << "class int:" << endl;
		a.setCoef(5, 2);
		a << cout;
		b.setCoef(5, 7);
		b << cout;
		cout << "f1(2) = " << a.calculate(2) << endl;
		cout << "f2(2) = " << b.calculate(2) << endl;
		cout << "sum:";
		a + b << cout;
		cout << "dif:";
		a - b << cout;
		cout << "mul f1 by 3:";
		4 * a << cout;

		cout << endl << "class float:" << endl;
		c.setCoef(5, 3.5555);
		c << cout;
		d.setCoef(5, 8.3245);
		d << cout;
		cout << "f1(2) = " << c.calculate(2) << endl;
		cout << "f2(2) = " << d.calculate(2) << endl;
		cout << "sum:";
		c + d << cout;
		cout << "dif:";
		c - d << cout;
		cout << "mul f1 by 3:";
		4 * c << cout;

		cout << endl << "class complex<double>:" << endl;
		e.setCoef(5, x);
		e << cout;
		f.setCoef(5, y);
		f << cout;
		cout << "f1(2) = " << e.calculate(2) << endl;
		cout << "f2(2) = " << f.calculate(2) << endl;
		cout << "sum:";
		e + f << cout;
		cout << "dif:";
		e - f << cout;
		cout << "mul f1 by 3:";
		4 * e << cout;
	}
	catch (const char* err)
	{
		cout << err;
	}
}
