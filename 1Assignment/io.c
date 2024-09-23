
#include <errno.h>
#include <unistd.h>

#include "io.h"

/* Reads next char from stdin. If no more characters, it returns EOF */
int
read_char() {
    char c;
    ssize_t bytesRead = read(0, &c, 1);

    return bytesRead == 1 ? c : EOF;
}

/* Writes c to stdout.  If no errors occur, it returns 0, otherwise EOF */
int
write_char(char c) {
    ssize_t bytesToWrite = write(1, &c, 1);

    return bytesToWrite == 1 ? 0 : EOF;
}

/* Writes a null-terminated string to stdout.  If no errors occur, it returns 0, otherwise EOF */
int
write_string(char* s) {
    while (*s) {
        if (write_char(*s) == EOF) {
            return EOF;
        }
        s++;
    }
    return 0;
}

/* Writes n to stdout (without any formatting).   
 * If no errors occur, it returns 0, otherwise EOF
 */
int
write_int(int n) {
    char stringOfInt[12];
    int numberOfDigits = 0;

    if (n == 0) {
        if (write_char('0') == EOF) {
            return EOF;
        }
        return 0;
    }

    if (n < 0) {
        write_char('-');
        n = -n;
    }

    while (n > 0) {
        stringOfInt[numberOfDigits] = n % 10 + 48;
        n /= 10;
        numberOfDigits++;
    }

    while (numberOfDigits > 0) {
        numberOfDigits--;
        if (write_char(stringOfInt[numberOfDigits]) == EOF) {
            return EOF;
        }
    }

    return 0;
}
