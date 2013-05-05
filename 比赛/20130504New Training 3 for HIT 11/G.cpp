#include <cstdio>
#include <cstring>
char s[55];
int t;

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf(" %s", s);
        bool flag = true;
        for (int i=0; i<strlen(s); i++)
            if (s[i] != '.') { flag = false; break; }
        if (flag) printf("Possible\n");
        else printf("You shall not pass!\n");

    }
    return 0;
}