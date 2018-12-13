#include <iostream>
#include <queue>
#include <map>

using namespace std;

int timeto[100];
int marked[100];

typedef struct linkv
{
	int n;
	map<int, int> mii;
} linkv;

typedef struct pic
{
	linkv lv[100];
	int n;
}pict;

struct edge
{
	int f, t, q;
	edge(int a, int b, int c) :f(a), t(b), q(c) {};
};

bool operator <(const edge a, const edge b) { return a.q > b.q; };

int main()
{
	int p;
	while (cin >> p)
	{
		if (p == 1)
		{
			cout << 0 << endl;
			continue;
		}
		pict *pic = new pict;
		for (int i = 0; i != p; ++i)
		{
			marked[i] = 0;
			timeto[i] = -1;
		}
		for (int i = 0; i != p; ++i)
			for (int j = 0; j != i; ++j)
			{
				int ce;
				if (cin >> ce)
				{
					pic->lv[j].mii.insert(make_pair(i, ce));
					pic->lv[i].mii.insert(make_pair(j, ce));
				}
				else
				{
					char c;
					cin.clear();
					cin >> c;
				}
			}
		timeto[0] = 0;
		marked[0] = 1;
		priority_queue<edge> pe;
		int ti = 0;
		while (!pe.empty() || !ti)
		{
			for (map<int, int>::iterator mit = pic->lv[ti].mii.begin(); mit != pic->lv[ti].mii.end(); ++mit)
			{
				if (!marked[mit->first])
					pe.push(edge(ti, mit->first, mit->second + timeto[ti]));
			}
			int tt, tq;
			do
			{
				tt = pe.top().t;
				tq = pe.top().q;
				pe.pop();
			} while (marked[tt]&&!pe.empty());
			if (pe.empty())
				break;
			if (timeto[tt] == -1 || tq < timeto[tt])
				timeto[tt] = tq;
			ti = tt;
			marked[ti] = 1;
		}
		int re = 0;
		for (int i = 0; i != p; ++i)
			if (re < timeto[i])
				re = timeto[i];
		cout << re << endl;
		delete pic;
	}
}
