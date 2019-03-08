#include <vector>
#include <queue>
#include <stdio.h>

struct point {
	int x;
	int y;
	int value;

	point(int xx, int yy, int v) {
		x = xx;
		y = yy;
		value = v;
	}
};

using namespace std;

// Boundary check
int check(int x, int y, int m, int n) {
	if (x < 0 || y < 0 || x > n - 1 || y > m - 1)
		return 0;
	return 1;
}

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) {
	int max_size_of_one_area = 0;
	int number_of_area = 0;

	int idx[] = { 0, 0, 1, -1 };
	int idy[] = { 1, -1, 0, 0 };
	int map[101][101] = { 0, };
	int visited[101][101] = { 0, };

	for (int i = 0; i < picture.size(); i++) {
		for (int j = 0; j < picture[j].size(); j++) {
			map[i][j] = picture[i][j];
			visited[i][j] = 0;
		}
	}

	// BFS로 문제 해결
	// x: j, y: i
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (check(j, i, m, n) && map[i][j] && !visited[i][j]) {
				int area = 1;
				queue<point> q;
				q.push(point(j, i, map[i][j]));
				visited[i][j] = 1;

				while (!q.empty()) {
					point p = q.front();
					int tempX = p.x;
					int tempY = p.y;
					q.pop();

					for (int k = 0; k < 4; k++) {
						int nextX = idx[k] + tempX;
						int nextY = idy[k] + tempY;
						if (check(nextX, nextY, m, n) && !visited[nextY][nextX]) {
							if (map[nextY][nextX] == map[i][j]) {
								area++;
								visited[nextY][nextX] = 1;
								q.push(point(nextX, nextY, map[i][j]));
							}
						}
					}
				}
				if (area)
					number_of_area++;
				if (max_size_of_one_area < area)
					max_size_of_one_area = area;
			}
		}
	}

	vector<int> answer(2);
	answer[0] = number_of_area;
	answer[1] = max_size_of_one_area;
	return answer;
}