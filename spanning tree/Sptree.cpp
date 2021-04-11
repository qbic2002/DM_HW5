#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 47;

vector<vector<pair<int, int>>> graph;
vector<bool> used;
vector<int> tree;

int main(){
	ifstream fin ("adj_m.txt");
	ofstream fout ("spantree.txt");
	graph.resize(N);
	used.resize(N);

	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			int w;
			fin >> w;
			graph[i].push_back({j, w});
			graph[j].push_back({i, w});
		}
	}

	fin.close();
	int weight = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    q.push({0, 0});

    while (!q.empty()){
        pair<int, int> curr = q.top();
        q.pop();
        int dst = curr.first;
        int v = curr.second;
        if (used[v]) {
            continue;
        }
        tree.push_back(v);
        used[v] = true;
        weight += dst;

        for (pair<int, int> p: graph[v]){
            int u = p.first;
            int len = p.second;
            if (!used[u] && len != -1){
                q.push({len, u});
            }
        }
    }
	fout << weight << "\n";
    for (int v : tree){
        fout << v << " ";
    }
	fout.close();
}