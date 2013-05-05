// 题意：字符串连起来组成密码才能开门，必须所有的字符串都用到，连接的字母首尾相接。
// 输入：所有的字母。
// 输出：是否可以完成连接。
// 思路：把26个字母看做节点，单词看做边，对于每一个单词，首字母的出度加1，尾字母的入读加1，二者连通，然后判断这个图是否连通，再判断是否有欧拉路或者欧拉回路即可。
// 程序：
#include <cstdio>
#include <cstring>

const int MAX = 26;
const int MAX_LEN = 1024;

int n, in[MAX], out[MAX], cnt;
char word[MAX_LEN];
bool live[MAX], map[MAX][MAX];

void init() {
    cnt = 0;
    memset(in, 0, sizeof(in));
    memset(out, 0, sizeof(out));
    memset(live, false, sizeof(live));
    memset(map, false, sizeof(map));
}

void DFS(int v) {
    live[v] = false;
    cnt--;
    for (int i = 0; i < MAX; i++) {
        if (live[i] && map[v][i]) {
            DFS(i);
        }
    }
}

bool isConnected() {
    int start;
    for (int i = 0; i < MAX; i++) {
        if (live[i]) {
            cnt++;
            start = i;
        }
    }
    DFS(start);
    if (cnt == 0) {
        return true;
    }
    return false;
}

bool isEuler() {
    int start = 0, end = 0;
    for (int i = 0; i < MAX; i++) {
        if (in[i] == out[i] + 1) {
            end++;
        } else if (out[i] == in[i] + 1) {
            start++;
        } else if (in[i] == out[i]) {
            continue;
        } else {
            return false;
        }
    }
    if (start == end) {
        if (start == 0 || start == 1) {
            return true;
        }
    }
    return false;
}

int main() {
    int total;
    scanf("%d", &total);
    while (total--) {
        scanf("%d", &n);
        init();
        while (n--) {
            scanf("%s", word);
            int s = word[0] - 'a', e = word[strlen(word) - 1] - 'a';
            out[s]++, in[e]++;
            live[s] = live[e] = true;
            map[s][e] = map[e][s] = true;
        }
        if (isConnected() && isEuler()) {
            printf("Ordering is possible.\n");
        } else {
            printf("The door cannot be opened.\n");
        }
    }
    return 0;
}