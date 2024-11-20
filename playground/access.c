#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char *filepath = "/bin/ls";
    int ret;

    // 0で成功
    // 見つからなかったら-1
    // F_OK が存在確認
    ret = access(filepath, F_OK);
    printf("%d\n", ret);
}
