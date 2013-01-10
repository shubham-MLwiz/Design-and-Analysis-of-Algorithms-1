#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <cstdlib>
#include<cstdio>
#include<string>
#include<fstream>
#include<algorithm>
#include <cstring>

using namespace std;

typedef struct node
{
	vector<int>	forwlist;
	vector<int>	backlist;
} Node;

#define MAX_VERTICES	875715
#define MAX_SCCS_REQ	5

int	f_times[MAX_VERTICES], t;
bool seen[MAX_VERTICES];
Node graph[MAX_VERTICES];

void dfs_reverse(int u)
{
	seen[u] = true;

	vector<int> list = graph[u].backlist;
	for (int i = 0; i < list.size(); i++)
		if (!seen[list[i]])
			dfs_reverse(list[i]);
	t++;
	f_times[t] = u;
}

int dfs_forward(int u)
{
	int		sz = 1;

	seen[u] = false;
	vector<int> list = graph[u].forwlist;
	for (int i = 0; i < list.size(); i++)
		if (seen[list[i]])
			sz += dfs_forward(list[i]);
	return sz;
}

int main()
{
	int	u, v, i;
	list<int>::iterator	it;
	list<int> sccs(5, 0);
	printf("begin\n");
	freopen("SCC.txt","r",stdin);
	int ct=0;
	while (true)
	{
	    scanf("%d",&u);
	    if(u==0) break;
		scanf("%d",&v);
		ct++;
		if(ct%10000==0) cout<<"boom\n";
        //printf("%d %d\n",u,v);
		graph[u].forwlist.push_back(v);	/* indicates the original graph */
		graph[v].backlist.push_back(u); /* indicates the reverse graph */
	}
	printf("done with input\n");
	for (i = 1; i < MAX_VERTICES; i++)
	{
		assert(!seen[i] || f_times[t]);
		if(i%10000==0) cout<<i<<"\n";
		if (!seen[i])
			dfs_reverse(i);
	}
	/* Instead of memset'ing 'seen' array to false for the next dfs, we can consider u as being un-explored
	 * if seen[u] is true.
	 */
	 printf("step 1\n");
	for (i = MAX_VERTICES - 1; i >= 1; i--)
	{
		if (seen[f_times[i]])
		{
			int sz = dfs_forward(f_times[i]);
			for (it = sccs.begin(); it != sccs.end(); it++)
				if (*it > sz)
					break;
			sccs.insert(it, sz);
			sccs.erase(sccs.begin());
		}
	}
	printf("step 2\n");
	for (it = sccs.begin(); it != sccs.end(); it++)
		cout << *it << " ";
	cout << endl;
	while(true){}
	return 0;
}
