#include <stdio.h>
#include <string.h>

void solve() {
    char s[1005];
    scanf("%s", s);
    
    int sum = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            sum += (s[i] - '0');
        }
    }
    
    printf("%d\n", sum);
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
