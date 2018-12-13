#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>

#define M 13131                               //散列所用数组大小

using namespace std;

typedef struct
{
	string ss;
	int ii;
} sa;

typedef struct
{
	sa sas[10000];
	int ie;
} save;

typedef struct haxi
{
	int num;
	sa data[M];
	unsigned int hashit(string &s)
	{
		unsigned int seed = 131;
		unsigned int hash = 0;

		for (int i = 0; i < s.size(); i++)
			hash = hash * seed + s[i];
		return hash%M;
	}
} haxi;

int findhash(haxi &, string);
void crehash(haxi *);
void getsug(haxi &, string, save &);

bool com(const sa &a, const sa &b)
{
	return a.ii < b.ii;
}

int main()
{
	string s;
	haxi *nc = new haxi;
	crehash(nc);
	while (cin >> s&&s != "#")
	{
		cout << s;
		if (findhash(*nc, s))
			cout << " is correct" << endl;
		else
		{
			save *ss = new save;
			cout << ":";
			getsug(*nc, s, *ss);
			sort(ss->sas, ss->sas + ss->ie, com);
			for (int i = 0; i != ss->ie; ++i)
			{
				cout << " " << ss->sas[i].ss;
			}
			cout << endl;
			delete ss;
		}
	}
	delete nc;
}

int findhash(haxi &h, string s)
{
	int key = h.hashit(s);
	while (h.data[key].ss != "")
	{
		if (h.data[key].ss == s)
			return h.data[key].ii;
		++key;
		if (key == M)
			key = 0;
	}
	return 0;
}

void crehash(haxi *th)
{
	int ti, ri = 1;
	string ts;
	th->num = 0;
	while (cin>>ts&&ts != "#")
	{
		ti = th->hashit(ts);
		while (th->data[ti].ss != "")
		{
			ti++;
			if (ti == M)
				ti = 0;
		}
		th->data[ti].ss = ts;
		th->data[ti].ii = ri++;
	}
}

bool afind(save &y, string s)
{
	for (int i = 0; i != y.ie; ++i)
	{
		if (y.sas[i].ss == s)
			return 1;
	}
	return 0;
}

void getsug(haxi &th, string s, save &ss)
{
	string ts;
	int gg = 0;
	ss.ie = 0;
	for (int j = 0; j != s.size(); ++j)                       //删除一个字母
	{
		ts = s;
		ts.erase(j, 1);
		if (afind(ss, ts))
			continue;
		if (gg = findhash(th, ts))
		{
			ss.sas[ss.ie].ss = ts;
			ss.sas[ss.ie++].ii = gg;
		}
	}
	for (int j = 0; j != s.size(); ++j)                      //替换一个字母
	{
		ts = s;
		ts[j] = 'a';
		for (int i = 0; i != 26; ++i)
		{
			if (!afind(ss, ts))
			{
				if (gg = findhash(th, ts))
				{
					ss.sas[ss.ie].ss = ts;
					ss.sas[ss.ie++].ii = gg;
				}
			}
			ts[j]++;
		}
	}
	for (int j = 0; j <= s.size(); j++)
	{
		ts = s;
		ts.insert(j, "a");
		for (int i = 0; i != 26; ++i)                        //插入一个字母
		{
			if (!afind(ss, ts))
			{
				if (gg = findhash(th, ts))
				{
					ss.sas[ss.ie].ss = ts;
					ss.sas[ss.ie++].ii = gg;
				}
			}
			ts[j]++;
		}
	}
}


