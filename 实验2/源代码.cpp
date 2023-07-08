#include<iostream>
#include <vector>
#include <algorithm>
#include<cmath>
#include <unordered_set>
#include <random>
struct pi
{
	double x, y;
	pi() {}
	pi(int xx, int yy) :x(xx), y(yy) {}
};
#define INF 1e9
using namespace std;
const int n = 100000;
vector<pi> p(n), p1(n);
pi temp1, temp2;
bool cmpx(const pi& p1, const pi& p2) {
	if (p1.x == p2.x)
		return  p1.y < p2.y;
	return p1.x < p2.x;
}
double dis(const pi& p1, const pi& p2) {
	return sqrt((double)(p1.x - p2.x) * (p1.x - p2.x) + (double)(p1.y - p2.y) * (p1.y - p2.y));
}


struct hashfunc //哈希函数
{
	size_t operator()(const pi& P) const
	{
		return size_t(P.x * 202311 + P.y);
	  //return : 根据点坐标得到的哈希值
	}
};

struct eqfunc //比较函数
{
	bool operator()(const pi& p1, const pi& p2) const
	{
		return ((p1.x == p2.x) && (p1.y == p2.y));
	}
};

void Merge(int left, int mid, int right) {
	int n1 = mid - left + 1;//左侧点集大小
	int n2 = right - mid;//右侧点集大小
	pi* L = new pi[n1];
	pi* R = new pi[n2];
	//完成两侧点集的复制
	for (int i = 0; i < n1; i++)
		L[i] = p[left + i];
	for (int i = 0; i < n2; i++)
		R[i] = p[mid + 1 + i];
	//算法利用分治法，利用类似归并排序的方法将点根据y升序排序
	int i = 0, j = 0, k;
	for (k = left; i < n1 && j < n2; k++) {
		if (L[i].y < R[j].y)//根据y升序来排
			p[k] = L[i++];
		else
			p[k] = R[j++];
	}
	//如果左点集或右点集有剩余元素，就将剩余元素直接放入即可。
	while (i < n1)
		p[k++] = L[i++];
	while (j < n2)
		p[k++] = R[j++];
}
double getmin(int l, int r)
{
	if (l == r)
		return INF;
	if (r - l == 1) {
	    temp1 = p[l];
		temp2 = p[r];
		p[l] = temp1.y < temp2.y ? temp1 : temp2;
		p[r] = temp1.y > temp2.y ? temp1 : temp2;
		return dis(p[l], p[r]);
	}
	int mid = (l + r) >> 1;
	double l_min = getmin(l, mid);
	double r_min = getmin(mid + 1, r);
	double base = min(l_min, r_min);
	Merge(l, mid, r);
	vector<pi> v;
	for (int i = l; i <= r; i++) {
		if (p[mid].x - p[i].x < base || p[i].x - p[mid].x < base) {
			v.push_back(p[i]);
		}
	}
	int size = v.size();
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size && j < i + 6; j++)
		{
			if ((v[j].y - v[i].y) > base)
				break;
			base = min(base, dis(v[i], v[j]));
		}
	}
	return base;
}

double bruteForce(vector<pi>& p1) {
	double ans = INF;
	for (int i = 0; i < p1.size(); i++) {
		for (int j = i + 1; j < p1.size(); j++) {
			ans = min(ans, dis(p1[i], p1[j]));
		}
	}
	return ans;
}


int main()
{
	default_random_engine rd(time(NULL));
	uniform_int_distribution<int> dist(0, (int)sqrt(n) * 5);
	//上面生成随机整数值i,均匀分布于闭区间[0,(int)sqrt(n)*5]，即按照以下离散概率
	//函数分布P(i|a,b) =1 / (b-a+1)
	unordered_set<pi, hashfunc, eqfunc> hash;
	for (int i = 0; i < n; i++)
	{
		p[i].x = dist(rd);
		p[i].y = dist(rd);
		if (hash.find(p[i]) == hash.end())
			hash.insert(p[i]);
		else
			i--;
	}
	p1.assign(p.begin(), p.end());
	double ans1 = 0, ans2 = 0;
	clock_t begin1, end1, begin2, end2;

	sort(p.begin(), p.end(), cmpx);
	begin1 = clock();
	ans1 = getmin(0, p.size() - 1);
	end1 = clock();

	begin2 = clock();
	ans2 = bruteForce(p1);
	end2 = clock();

	cout << "分治：" << endl;
	cout << "最小点对距离为" << ans1 << endl;
	cout << "time = " << double(end1 - begin1) / CLOCKS_PER_SEC << "s" << endl;
	cout << endl;
	cout << "暴力：" << endl;
	cout << "最小点对距离为" << ans2 << endl;
	cout << "time = " << double(end2 - begin2) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}
