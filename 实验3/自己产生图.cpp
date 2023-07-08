#include <iostream>
#include <ctime>
using namespace std;

#define COLOR 4    //可选颜色总数
#define VERTEX 200     //点数
#define EDGE  300  //边数
int isConnect[VERTEX + 5][VERTEX + 5];

struct Vertex
{
	int color; //该点所选的颜色
	int state[COLOR + 1];  //颜色状态，1为可选，非1为不可选
	int choice;  //可选颜色的数量，即state中1的数量
	int degree;  //相邻点的数量,即该点的度
	Vertex() {
		color = 0; //默认该顶点没颜色
		for (int i = 0; i <= COLOR; ++i)
			state[i] = 1; //默认初始化为全部颜色都可选
		choice = COLOR; //默认初始化为全部颜色都可选
		degree = 0;  //默认初始化度为0
	}
};

int Map[VERTEX + 1][256];  //邻接表,Map[i][0]表示第i个节点相邻节点的数量，Map[i][j]表示第i个节点的第j个相邻节点。
long long sum = 0;   //记录解的个数
clock_t startTime, endTime;//秒级程序计时

bool check(Vertex* S, int current, int i) { //传进节点数组、当前节点序号current和其所选的颜色i
	for (int k = 1; k <= Map[current][0]; ++k) { //遍历当前节点的所有相邻节点
		int j = Map[current][k]; //j是遍历到的相邻节点序号
		if (S[j].color == 0 && S[j].state[i] == 1) { //若顶点j为待填色节点且可以填颜色i
			S[j].state[i] = -current; //就使得顶点j不能选i这个颜色
			S[j].choice--; //顶点j的可选颜色数量-1
			if (!S[j].choice) { //若顶点j的可选颜色数量-1之后变为了0,返回false
				return false;
			}
		}
	}
	return true; //若不会导致出现相邻顶点无色可选的情况则返回true
}

int getNext(Vertex* S) {//优先MRH,其次DH
	auto Min = COLOR;//最小的可选颜色数量,初始化为最大
	int next = 0;
	for (int i = 1; i <= VERTEX; ++i) {
		if (!S[i].color) { //从未填色的点中找到下一个要着色的点
			if (S[i].choice == Min) {
				if (S[i].degree > S[next].degree) {
					Min = S[i].choice; //在可选颜色数最小的节点中选择度最大的作为下一个需要着色的节点
					next = i;
				}
			}
			else if (S[i].choice < Min) {//用于寻找可选颜色数最小的节点
				Min = S[i].choice;
				next = i;
			}
		}
	}
	return next;
}

//核心的回溯函数
int DFS(Vertex* S, int current, int count, int usedColor) { //count是已经着色的点的数量
	if (count == VERTEX) { //到达叶子节点,找到一个着色方案
		sum += S[current].choice;
		return S[current].choice;
	}
	else {
		int s = 0;
		for (int i = 1; i <= COLOR; i++) {
			if (S[current].state[i] == 1) {
				int ss = 0;
				S[current].color = i;
				auto isNewColor = i > usedColor;
				//剪枝
				if (check(S, current, i)) {
					if (isNewColor)
						ss = DFS(S, getNext(S), count + 1, usedColor + 1);
					else
						ss = DFS(S, getNext(S), count + 1, usedColor);
				}
				//回溯
				S[current].color = 0;
				for (int k = 1; k <= Map[current][0]; ++k) {
					int j = Map[current][k];
					if (S[j].state[i] == -current) {
						S[j].choice++;
						S[j].state[i] = 1;
					}
				}
				//关键剪枝
				if (isNewColor) {
					s += ss * (COLOR - usedColor);
					sum += ss * (COLOR - usedColor - 1);
					break;
				}
				s += ss;
			}
		}
		if (sum > 1000000000) {
			endTime = clock();
			printf("sum>10亿后退出，运行时间为：\n");
			cout << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
			exit(1);
		}
		else
			return s;
	}
}

int main() {
	Vertex S[VERTEX + 1];
	int u, v;
	srand((unsigned int)time(NULL));
	for (int i = 1; i <= EDGE; i++) {
		
		u = rand() % VERTEX + 1;
		v = rand() % VERTEX + 1;
		if (u == v || isConnect[u][v]|| isConnect[v][u]) {
			i--;
			continue;
		}
		isConnect[u][v] = 1;
		isConnect[v][u] = 1;
		Map[u][0]++;
		Map[u][Map[u][0]] = v;
		Map[v][0]++;
		Map[v][Map[v][0]] = u;
		S[u].degree++;
		S[v].degree++;
	}

	printf("成功读取了地图数据,进行地图填色~\n" );
	cout << "点数：" << VERTEX << "  边数：" << EDGE << endl;
	startTime = clock();//计时开始
	auto ans = DFS(S, getNext(S), 1, 0);
	endTime = clock();//计时结束
	cout << "运行时间为:" << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	printf("解的个数:%d\n", ans);
	return 0;
}
