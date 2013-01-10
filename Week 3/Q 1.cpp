#include <vector>
#include <utility>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <string>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_VERTICES	40
#define MAX_LINE	128

using namespace std;

int graph[MAX_VERTICES + 1][MAX_VERTICES + 1];
int dev_urandom = -1;
int remove_v;

struct delete_edge : public std::unary_function<pair<int,int> &, bool>
{
	bool operator()(pair<int,int> &edge)
	{
		return edge.first == remove_v || edge.second == remove_v;
	}
};

int get_random(int limit)
{
	int		seed;

	assert(dev_urandom > -1);
	read(dev_urandom, &seed, sizeof(seed));
	srand(seed);
	return rand() % limit;
}

int min_cut(int c_graph[MAX_VERTICES + 1][MAX_VERTICES + 1], vector<pair<int,int> > edges, int n_vertices)
{
	int		u, v, rnd, i, j, edge_cnt;

	edge_cnt = edges.size();
	while (n_vertices > 2)
	{
		rnd = get_random(edges.size());
		assert(rnd >= 0 && rnd < edges.size());
		u = edges[rnd].first;
		v = edges[rnd].second;
		assert(c_graph[u][v] && c_graph[v][u]); /* this should be a valid edge in the current graph */
		/* contraction begins */
		c_graph[u][v] = c_graph[v][u] = 0;	/* u,v is no longer an edge (also eliminates self-loop) */
		for (i = 0; i < edges.size(); i++)
		{
			int other_v = edges[i].first == v ? edges[i].second
						      : edges[i].second == v ? edges[i].first : -1;
			if (-1 != other_v)
			{	
				if (other_v == u)
					continue; /* this case is already taken care of (before the for loop) */
				assert(c_graph[v][other_v] == c_graph[other_v][v]);
				c_graph[u][other_v] += c_graph[v][other_v];
				c_graph[other_v][u] = c_graph[u][other_v];
				/* add parallel edges (if any) */
				for (j = 0; j < c_graph[v][other_v]; j++)
					edges.push_back(make_pair(u, other_v));
				c_graph[v][other_v] = c_graph[other_v][v] = 0; /* v,other_v is no longer an edge in the graph */
			}
		}
		remove_v = v;
		edges.erase(remove_if(edges.begin(), edges.end(), delete_edge()), edges.end());
		n_vertices--;
	}
	return edges.size();
}

int main()
{
	int			u, v, i, n_vertices = MAX_VERTICES, overall_min_cut = 1 << 30, iterations;
	int			c_graph[MAX_VERTICES + 1][MAX_VERTICES + 1];
	char			*p;
	string			s;
	char            *cstr;
	cstr = new char [s.size()+1];
    strcpy (cstr, s.c_str());
	vector<pair<int,int> >	edges, c_edges;

	/* read # of vertices */
	while (getline(cin, s))
	{
          strcpy (cstr, s.c_str());
		p = strtok(cstr, " ");
		u = atoi(p);
		while (1)
		{
			p = strtok(NULL, " ");
			if (!p) break;
			v = atoi(p);
			graph[u][v] = 1;
			if (graph[v][u])
				continue;	/* already added to the edge list */
			graph[v][u] = 1;
			edges.push_back(make_pair(u, v));
		}
	}
	/* for fun, open /dev/urandom for getting seeds */
	dev_urandom = open("/dev/urandom", O_RDONLY);
	/* for a start, run Karger's algorithm O(|V|) times */
	iterations = n_vertices;
	for (i = 0; i < iterations ; i++)
	{
		int	cut;

		c_edges = edges;	/* clone the edges (for reuse) */
		memcpy(c_graph, graph, sizeof(graph)); /* clone the graph (for reuse) */
		cut = min_cut(c_graph, c_edges, n_vertices);
		if (cut < overall_min_cut)
			overall_min_cut = cut;
	}
	close(dev_urandom);
	cout << "Overall Min-Cut after " << iterations << " iterations is = " << overall_min_cut << endl;
	return 0;
}
