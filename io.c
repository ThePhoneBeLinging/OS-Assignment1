
#include <errno.h>
#include <unistd.h>

#include "io.h"

/* Reads next char from stdin. If no more characters, it returns EOF */
int
read_char() {
    int c;
    read(0, &c, 1);
    return c;
}

/* Writes c to stdout.  If no errors occur, it returns 0, otherwise EOF */
int
write_char(char c) {
    write(1, &c, 1);
    return 0;
}

/* Writes a null-terminated string to stdout.  If no errors occur, it returns 0, otherwise EOF */
int
write_string(char* s) {
    while (*s) {
        write_char(*s);
        s++;
    }
    return 0;
}

/* Writes n to stdout (without any formatting).   
 * If no errors occur, it returns 0, otherwise EOF
 */
int
write_int(int n) {
    write_char(n - 48);
    return 0;
}
