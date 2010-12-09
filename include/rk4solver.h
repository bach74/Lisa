#include <functional>
#include <vector>
#include <algorithm>

// add multiplication * by a constant to the std::vector class
template <typename T>
std::vector<T> operator* (std::vector<T>& v1, T k) {
	std::vector<T> res(v1.size(),0);
	std::transform(v1.begin(),v1.end(),res.begin(),std::bind2nd(std::multiplies<T>(),k));
	return res;
}

// add sumation + element by element to the std::vector class
template <typename T>
std::vector<T> operator+ (std::vector<T>& v1, std::vector<T>& v2) {
	assert(v1.size()==v2.size());
	std::vector<T> res(v1.size(),0);
	std::transform(v1.begin(),v1.end(),v2.begin(),res.begin(),std::plus<T>());
	return res;
}

// define function (vector,vector)
struct func : public std::binary_function<std::vector<double>, std::vector<double>& , double>
{
	virtual std::vector<double> operator()(std::vector<double>& x, double t)=0;
};


/// Runge-Kutta 4 solver class
class RK4solver {
public:
	void solve(double stepsize, std::vector<double>& x, double t, func& f)
	{
		std::vector<double> k1=f(x,t);
		std::vector<double> k2=f(x+k1*(stepsize/2),t+stepsize/2);
		std::vector<double> k3=f(x+k2*(stepsize/2),t+stepsize/2);
		std::vector<double> k4=f(x+k3*stepsize,t+stepsize);

		std::vector<double> x_next=x+(k1+k2*2.0+k3*2.0+k4)*(stepsize/6);
		x=x_next;
	}
};
