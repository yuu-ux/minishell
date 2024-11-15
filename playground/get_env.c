#include <stdio.h>
#include <stdlib.h>

int main() {
    // 環境変数PATHの値を取得
    char *path = getenv("PATH");

    if (path != NULL) {
        printf("PATH: %s\n", path);
    } else {
        printf("PATH environment variable not found.\n");
    }
    return 0;
}
