/*input
12 6
bulldog
dog
dogged
doggedly
doggerel
dogma
dogmatic
dogmatism
dogs
catastroph
catastroph
doctor
cat
dog
dogg
do
doctrinography
dogge

*/
 
/*
                                                    ______________
                                                          |       )
                                                          |   )   /
                                                          |______/
                                                    |     |      \
                                                    |     |   )   \
                                                    |_____|_______)
 
*/
 
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
#include <iomanip>
#include <fstream>

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
#define TRACE
 
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cout << name << " : " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');cout.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
}
#else
#define trace(...)
#endif
 
#define out(container) for (auto it : container) cout << it << " "; cout << endl;
 
 
template < typename T > T GCD(T a, T b)            { ll t; while(a) { t = a; a = b % a; b = t; } return b; }
template < typename T > string toString(T a)       { return to_string(a); }
template < typename T > void toInt(string s, T &x) { stringstream str(s); str >> x;}
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

typedef struct data {
  data* bit[26];
  int cnt = 0;
} trie;

trie *head;

void insert(string str) {
  trie *node = head;
  int n = str.size();
  for (int i = 0; i < n; i++) {
    int curbit = str[i] - 'a';
    if (node -> bit[curbit] == NULL) {
      node -> bit[curbit] = new trie();
    }
    node = node -> bit[curbit];
    node -> cnt++;
  }
}

void remove(string str) {
  trie *node = head;
  int n = str.size();
  for (int i = 0; i < n; i++) {
    int curbit = str[i] - 'a';
    node = node -> bit[curbit];
    node -> cnt--;
  }
}

int search(string str) {
  trie *node = head;
  int n = str.size();
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int curbit = str[i] - 'a';
    if (node -> bit[curbit] == NULL) return 0;
    node = node -> bit[curbit];
    ans = node -> cnt;
  }
  return ans;
}

int main()
{
  ios_base::sync_with_stdio(false); // 🏁 👀 💕
  cin.tie(NULL);
  
  int n, q;
  cin >> n >> q;
  string str;
  head = new trie();
  for (int i = 0; i < n; i++) {
    cin >> str;
    insert(str);
  }
  while (q--) {
    cin >> str;
    int ans = search(str);
    cout << ans << endl;
  }

  return 0;
}
