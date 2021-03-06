#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> PII;
typedef pair<ll , ll> PLL;
typedef long double ld;
 
#define pb push_back
#define all(c) c.begin(),c.end()
#define allr(c) c.rbegin(),c.rend()
int mod = 1000000007;
const int inf = 1034567891;
const ll LL_INF = 1234567890123456789ll;
#define PI 3.14159265
#define endl '\n'
#define F first
#define S second
#define debug(x) cout << #x << " = " << x << endl;

#define out(container) for (auto it : container) cout << it << " "; cout << endl;

inline int add(int x, int y){ x += y; if(x >= mod) x -= mod; return x;}
inline int sub(int x, int y){ x -= y; if(x < 0) x += mod; return x;}
inline int mul(int x, int y){ return (x * 1ll * y) % mod;}
inline int powr(int a, ll b){
  int x = 1 % mod;
  while(b){
    if(b & 1) x = mul(x, a);
    a = mul(a, a);
    b >>= 1;
  }
  return x;
}
inline int inv(int a){ return powr(a, mod - 2);}

// https://en.wikipedia.org/wiki/Shamir%27s_Secret_Sharing

int rand(int a, int b) { // genrate a random number in range a to b
  return a + rand() % (b - a + 1);
}

int _eval_at(vector <int> &poly, int x) { // evaluate a polynomial at value x
  int ans = 0;
  for (int i = poly.size() - 1; i >= 0; i--) {
    ans = mul(ans, x);
    ans = add(ans, poly[i]);
  }
  return ans;
}
void make_random_shares(vector <PII> &points, vector <int> &poly, int shares, int k) { // generate polynomial for Shamir's Algo
  if (k > shares) {
    cout << "Enter correct data" << endl;
    exit(0);
  }
  for (int i = 0; i < k; i++) {
    poly[i] = rand(1, 10000);
  }
  for (int i = 0; i < shares; i++) {
    points[i] = {i + 1, _eval_at(poly, i + 1)};
  }
}

int langrange_interpolation(vector <int> &x_s, vector <int> &y_s) { // It is method to get back the actual polynomial
  vector <int> num, deno;
  int k = x_s.size();
  for (int i = 0; i < k; i++) {
    int x = x_s[i];
    num.pb(1);
    deno.pb(1);
    for (int j = 0; j < k; j++) {
      if (i == j) continue;
      num[i] = mul(num[i], -x_s[j]);
      deno[i] = mul(deno[i], x - x_s[j]);
    }
  }
  int ans = 0;
  for (int i = 0; i < k; i++) {
    ans = add(ans, mul(mul(y_s[i], num[i]), inv(deno[i])));
  }
  return ans;
}

int recover_secret(vector <PII> &shares) {
  if (shares.size() < 2) {
    cout << "need at least 2 points" << endl;
    return 0;
  }
  vector <int> x_s, y_s;
  for (auto it : shares) {
    x_s.pb(it.F);
    y_s.pb(it.S);
  }
  int secret_key = langrange_interpolation(x_s, y_s);
  return secret_key;
}

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  srand(2);

  int shares = 4;
  int k = 2;
  vector <PII> points(shares);
  vector <int> poly(k);
  make_random_shares(points, poly, shares, k);
  cout << poly[0] << endl;
  out(poly);
  for (int i = 0; i < shares; i++) {
    cout << points[i].F << " " << points[i].S << endl;
  }
  vector <int> per = {0, 1, 2, 3};
  random_shuffle(all(per));
  vector <PII> vec;
  for (int i = 0; i < k; i++) {
    vec.pb(points[per[i]]);
  }
  int ans = recover_secret(vec);
  cout << ans << endl;


  return 0;
}
