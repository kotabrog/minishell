#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*!
 * @brief     標準出力をファイルに複製する
 * @param[in] filepath  ファイルパス名
 * @return    0:success/-1:failure
 */
static int stdout_to_file(char *filepath)
{
    int rc = 0;
    int fd = 0;

    fd = open(filepath, O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if(fd < 0){
        printf("Error: open() %s: %s\n", strerror(errno), filepath);
        return(-1);
    }

    /* 標準出力をファイルにする。 */
    close(1);
    rc = dup(fd);
    if(rc < 0){
        printf("Error: dup() %s: %d\n", strerror(errno), fd);
        return(-1);
    }
    close(fd);

    /* ファイルに出力する */
    printf("message\n");

    return(0);
}

int main(int argc, char *argv[])
{
    int rc = 0;

    if(argc != 2){
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    rc = stdout_to_file(argv[1]);
    if(rc != 0) exit(EXIT_FAILURE);

    exit(EXIT_SUCCESS);
}