/**
 * Description: Modular arithmetic.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 */

struct mi {
 	int v; explicit operator int() const { return v; } 
	mi() { v = 0; }
	mi(ll _v):v(_v%MOD) { v += (v<0)*MOD; }
};
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; 
	return a; }
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; 
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
mi& operator*=(mi& a, mi b) { return a = a*b; }
mi pow(mi a, ll p) { assert(p >= 0); // asserts are important! 
	return p==0?1:pow(a*a,p/2)*(p&1?a:1); }
mi inv(mi a) { assert(a.v != 0); return pow(a,MOD-2); }
mi operator/(mi a, mi b) { return a*inv(b); }
/// mi a = MOD+5; ps((int)inv(a));


// source: https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Modular%20Arithmetic/ModIntShort.h
// Usage
mi a = 1e8, b = 1e8, c = 1e8;
// cout << a*b*c << "\n"; // doesn't work
// ^ not silently converted to int
cout << int(a*b*c) << "\n"; // 49000000
