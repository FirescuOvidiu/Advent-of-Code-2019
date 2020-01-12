#include "../../AOCHeaders/stdafx.h"


void readInput(std::fstream& in, std::vector<std::pair<std::string, long long>>& shuffleProcess)
{
	std::string op;
	long long number = 0;

	while (in >> op)
	{
		if (op == "cut")
		{
			in >> number;
			shuffleProcess.push_back(std::make_pair("cut", number));
		}
		else
		{
			in >> op >> op;
			if (op == "increment")
			{
				in >> number;
				shuffleProcess.push_back(std::make_pair("increment", number));
			}
			else
			{
				in >> op;
				shuffleProcess.push_back(std::make_pair("new", number));
			}
		}
	}
}


// Returns (a * b) % mod
// If b is even then a * b = (2 * a) * (b / 2)
// If b is odd  then a * b = a + (a * (b - 1))
long long moduloMultiplication(long long a, long long b, long long mod)
{
	long long result = 0; 

	a = a % mod;
	while (b)
	{
		// If b is odd, add a with result 
		if (b & 1)
		{
			result = (result + a) % mod;
		}

		// Here we assume that doing 2*a 
		// doesn't cause overflow 
		a = (2 * a) % mod;
		b >>= 1; // b = b / 2 
	}

	return result;
}


// Returns (a ^ b) % mod
// If b is even then a * b = (a * a) ^ (b / 2)
// If b is odd  then a * b = a * (a ^ (b - 1))
long long pow(long long a, long long b, long long mod)
{
	long long result = 1;

	a = a % mod;
	while (b)
	{
		// If b is odd, multiply a with result 
		if (b & 1)
		{
			result = moduloMultiplication(result, a, mod);
		}

		a = moduloMultiplication(a, a, mod);;
		b = b >> 1; // b = b/2 
	}
	return result;
}


// Returns modulo inverse of input with respect 
// to modulo using extended Euclid Algorithm 
// Assumption: input and modulo are coprimes
long long modInverse(long long input, long long modulo)
{
	long long original = modulo;
	long long y = 0, x = 1;
	long long q = 0, t = 0;

	if (modulo == 1)
	{
		return 0;
	}

	while (input > 1)
	{
		// q is quotient 
		q = input / modulo;
		t = modulo;

		// modulo is remainder now 
		// process same as Euclid's algorithm
		modulo = input % modulo;
		input = t;
		t = y;

		// Update y and x
		y = x - q * y;
		x = t;
	}

	if (x < 0)
	{
		x += original;
	}

	return x;
}


long long solveProblem(const std::vector<std::pair<std::string, long long>>& shuffleProcess)
{
	long long a = 1, b = 0, aux = 0;
	long long n = 119315717514047;
	long long times = 101741582076661;

	for (int i = shuffleProcess.size() - 1; i >= 0; i--)
	{
		if (shuffleProcess[i].first == "cut")
		{
			b = b + shuffleProcess[i].second;
		}
		else
		{
			if (shuffleProcess[i].first == "new")
			{
				a *= -1;
				b = -b - 1;
			}
			else
			{
				aux = modInverse(shuffleProcess[i].second, n);

				a = moduloMultiplication(a, aux, n);
				b = moduloMultiplication(b, aux, n);
			}
		}

		a = (a + n) % n;
		b = (b + n) % n;
	}

	// f(x) = a * x + b    x = 2020
	// f(f(f(x))) = a*(a*(a*x+b)+b)+b = a ^ 3 * x + a ^ 2 * b + a * b + b
	// f^n(x) = a^n*x + a^(n-1)*b + a^(n-2)*b + ... + b = a ^ n * x + (a ^ n - 1) / (a - 1) * b
	// f^n(x) = ((pow(a, times, n)*2020 + (pow(a, times, n)-1) * modInverse(a-1, n) * b) % n)
	long long first = moduloMultiplication(pow(a, times, n), 2020, n);
	long long second = (pow(a, times, n) + n - 1) % n;
	long long third = moduloMultiplication(b, second, n);
	long long fourth = pow(a - 1, n - 2, n);
	long long result = (first + moduloMultiplication(third, fourth, n)) % n;

	return  result;
}


int main()
{
	std::fstream in("input.in", std::fstream::in);
	std::fstream out("output.out", std::fstream::out);
	std::vector<std::pair<std::string, long long>> shuffleProcess;

	readInput(in, shuffleProcess);
	out << solveProblem(shuffleProcess);

	in.close();
	out.close();
}