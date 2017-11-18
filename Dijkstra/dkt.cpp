#include "dkt.h"

void initVector(vector<vector<pair<int, int>>> &g) {
	setlocale(LC_ALL, "rus");
	int n = 0;//кол-во вершин
	//vector<vector<pair<int, int>>> g;
	cout << "1 - протестировать граф с 6 вершинами" << endl;
	cout << "2 - протестировать граф с 9 вершинами" << endl;
	cout << "3 - свой граф" << endl;
	cin >> n;
	while (n < 0 && n > 3) {
		cout << "1 - протестировать граф с 9 вершинами" << endl;
		cout << "2 - протестировать граф с 6 вершинами" << endl;
		cout << "3 - свой граф" << endl;
		cin >> n;
	}
	if (n == 1) {
		int n = 6;//кол-во вершин
		g.resize(n);
		for (int i = 0; i < n; i++) {
			g[i].resize(n);
		}
		for (int i = 0; i < n; i++) {
			/*!!!обработчик ошибок*/
			for (int j = 0; j < n; j++) {
				g[i][j].first = j;
				g[i][j].second = INF;
			}
		}
		g[0][1].second = 2;
		g[0][2].second = 1;
		g[0][3].second = 4;

		g[1][3].second = 7;
		g[1][4].second = 3;

		g[2][3].second = 5;
		g[2][4].second = 10;
		g[2][5].second = 4;

		g[3][5].second = 5;

		g[4][5].second = 4;
	} 
	if (n == 2) {
		int n = 9;//кол-во вершин
		g.resize(n);
		for (int i = 0; i < n; i++) {
			g[i].resize(n);
		}
		for (int i = 0; i < n; i++) {
			/*!!!обработчик ошибок*/
			for (int j = 0; j < n; j++) {
				g[i][j].first = j;
				g[i][j].second = INF;
			}
		}
		g[0][1].second = 10;
		g[0][2].second = 6;
		g[0][3].second = 8;

		g[1][3].second = 5;
		g[1][4].second = 13;
		g[1][6].second = 11;

		g[2][4].second = 3;

		g[3][4].second = 5;
		g[3][5].second = 7;
		g[3][6].second = 12;

		g[4][5].second = 9;
		g[4][8].second = 12;

		g[5][7].second = 8;
		g[5][8].second = 10;

		g[6][5].second = 4;
		g[6][7].second = 6;
		g[6][8].second = 16;

		g[7][8].second = 15;
	}
	if (n == 3) {
		cout << "Введите количество вершин";
		cin >> n;
		while (n < 0) {
			cin >> n;
		}
		g.resize(n);
		for (int i = 0; i < n; i++) {
			g[i].resize(n);
		}
		for (int i = 0; i < n; i++) {
			/*!!!обработчик ошибок*/
			for (int j = 0; j < n; j++) {
				g[i][j].first = j;
				cout << "Введите вес ребра, идущего из вершины " << i << "в вершину " << j << "(если ребра нет, то введите 0): ";
				cin >> g[i][j].second;
			}
		}
	}
	return;
}

void findWay(vector<vector<pair<int, int>>> g){
	int s = 0; //стартовая вершина
	vector<int> d(g.size(), INF), p(g.size()); //веса вершин и вес ребер
	d[s] = 0;
	vector<bool> u(g.size(), false); //отметка вершин
	for(unsigned int i = 0; i < g.size(); i++){
		int v = -1;
		/*цикл по вершинам*/
		for (unsigned int j = 0; j < g.size(); j++) {
			if (!u[j] && (v == -1 || d[j] < d[v])) {
				v = j;
			}
			if (v != -1 && d[v] == INF) {
				break;
			}
		}
		u[v] = true;
		if (v == -1) continue;
		/*цикл по ребрам*/
		for(unsigned int j = 0; j < g[v].size(); j++){
			int to = g[v][j].first;
			int len = g[v][j].second;
			//cout << v << ' ' << to << ' ' << len << endl;
			if (d[v] + len < d[to]){
				d[to] = d[v] + len;
				p[to] = v;
			}
		}
	}
	cout << "Min way is " << d[g.size() - 1] << endl;
	//cout << "Min is " << p[1] << p[2] << p[3] << p[4] << p[5] << endl;
	coutWay(p);
	return;
}

void coutWay(vector<int> p) {
	int j = p.size() - 1;
	int way_size = 1;
	while (j != 0) {
		j = p[j];
		way_size++;
	}
	j = p.size() - 1;
	vector <int> way(way_size + 1);
	for (int i = (int) way.size() - 2; i >= 0; i--) {
		way[i] = p[j] + 1;
		j = p[j];
	}
	way[0]--;
	way[way_size] = p.size();
	for (int i = 1; i < (int) way.size(); i++) {
		cout << way[i];
	}
	cout << endl;
	return;
}
