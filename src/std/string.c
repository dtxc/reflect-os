#include <math.h>
#include <kheap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void append(char *s, char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

bool startswith(char str[], char c[]) {
    int len = strlen(c);
    for (int i = 0; i < len; i++) {
        if (c[i] != str[i]) {
            return false;
        }
    }
    return true;
}

bool endswith(char *str, char c) {
    if (str[strlen(str) - 1] == c) {
        return true;
    }

    return false;
}

void strncpy(char *dest, char *src, u32 n) {
    int i = 0;
    while (i++ != n && (*dest++ = *src++));
}

char *strdup(char *token) {
    char *str;
    char *ptr;
    int len = 0;

    while (token[len]) {
        len++;
    }
    str = (char *) kmalloc(len + 1);
    ptr = str;
    while (*token) {
        *ptr = *token++;
    }
    *ptr = '\0';

    return str;
}

char *strcat(char *dest, char *src) {
    char *ptr = dest + strlen(dest);

    while (*src != '\0') {
        *ptr++ = *src;
    }
    *ptr = '\0';
    return dest;
}

static int strspn(const char *s1, const char *s2) {
    int count = 0;
    int found = 0;

    while (*s1) {
        found = 0;

        for (const char *c = s2; *c; c++) {
            if (*s1 == *c) {
                found = 1;
                break;
            }
        }

        if (found == 0) {
            return count;
        }

        count++;
        s1++;
    }

    return count;
}

static int strcspn(const char *s1, const char *s2) {
    int count = 0;
    int found = 0;

    while (*s1) {
        found = 0;

        for (const char *c = s2; *c; c++) {
            if (*s1 == *c) {
                found = 1;
                break;
            }
        }

        if (found == 1) {
            return count;
        }

        count++;
        s1++;
    }

    return count;
}

char *strtok(char *s, char *delm, char **saveptr) {
    if (s != nullptr) {
        *saveptr = s;
    } else {
        s = *saveptr;
    }

    s += strspn(s, delm);
    if (*s == '\0') {
        *saveptr = nullptr;
        return nullptr;
    }

    char *token = s;
    s += strcspn(s, delm);

    if (*s != '\0') {
        *s = '\0';
        *saveptr = s + 1;
    } else {
        *saveptr = nullptr;
    }

    return token;
}

int split(char *str, char *delm, char tokens[10][100]) {
    int ntokens = 0;
    char buf[100];

    char *saveptr;
    char *token;

    strncpy(buf, str, 100);

    token = strtok(buf, delm, &saveptr);
    while (token != nullptr && ntokens < 10) {
        strncpy(tokens[ntokens], token, 100);

        ntokens++;
        token = strtok(nullptr, delm, &saveptr);
    }

    return ntokens;
}

// int split(char *str, char delimiter, char ***dest) {
//     int count = 1;
//     int token_len = 1;
//     int i = 0;
//     char *p;
//     char *t;

//     p = str;
//     while (*p != '\0') {
//         if (*p == delimiter) count++;
//         p++;
//     }

//     *dest = (char **) kmalloc(count);
//     if (*dest == 0) return 1;
//     p = str;
//     while (*p != '\0') {
//         if (*p == delimiter) {
//             (*dest)[i] = (char *) kmalloc(token_len);
//             if ((*dest)[i] == 0) return 1;
//             token_len = 0;
//             i++;
//         }
//         p++;
//         token_len++;
//     }
//     (*dest)[i] = (char *) kmalloc(token_len);
//     if ((*dest)[i] == 0) return 1;
//     i = 0;
//     p = str;
//     t = ((*dest)[i]);
//     while (*p != '\0') {
//         if (*p != delimiter && *p != '\0') {
//             *t = *p;
//             t++;
//         } else {
//             *t = '\0';
//             i++;
//             t = ((*dest)[i]);
//         }
//         p++;
//     }

//     return count;
// }

bool isdigit(char c) {
    if (c >= '0' && c <= '9') return true;
    return false;
}

bool isnumber(char *c) {
    for (int i = 0; i < strlen(c); i++) {
        if (!isdigit(c[i])) {
            return false;
        }
    }

    return true;
}

char *trim(char *str) {
    char *end;
    while (*str == ' ') str++;
    if (*str == 0) return str;
    end = str + strlen(str)-1;
    while (end > str && *end == ' ') end--;
    end[1] = '\0';
    return str;
}

void *memset(void *dest, u8 c, int n) {
    int i, m;
    unsigned long  *wdst = dest;  
    long  cc = c + (c<<8) + (c<<16)+ (c<<24); 

    for(i = 0, m = n / sizeof(long); i < m; i++)  
        *(wdst++) = cc;                     

    for(i = 0, m = n % sizeof(long); i < m; i++) 
        *(((unsigned char*)wdst)+i) = c;

    return dest;
}

void memcpy(void *dest, void *src, int num) {
    for (int i = 0; i < num; i++) {
        *((u8 *) (dest + i)) = *((u8 *) (src + i));
    }
}

u16 *memsetw(u16 *dest, u16 val, u32 count) {
    u16 *temp = (u16 *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

int memcmp(void *a, void *b, u32 n) {
    u8 *p = a;
    u8 *q = b;
    int res = 0;
    if (a == b) {
        return res;
    }

    while (n > 0) {
        if (*p != *q) {
            res = (*p > *q) ? 1 : -1;
        }
        n--;
        p++;
        q++;
    }
    return res;
}

int strcpy(char *dest, char *src) {
    int num = 0;
    while (1) {
        char c = *src;
        *dest = c;

        if (c == '\0') {
            break;
        }
        dest++;
        src++;
        num++;
    }

    return num;
}

u32 strlen(char *str) {
    int i = 0;
    char c;

    while ((c = str[i]) != '\0') {
        i++;
    }
    return i;
}

bool strcmp(char *a, char *b) {
    if (strlen(a) != strlen(b)) {
        return false;
    }

    for (u32 i = 0; i < strlen(a); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

void ftoa(char *buff, double f) {
    char *ptr = buff;
    char ch;
    long intp;
    int precision = 10;

    if (f < 0) {
        f = -f;
        *ptr++ = '-';
    }

    f += 0.00000000005;
    intp = f;
    f -= intp;

    char *c;
    itoa(c, intp);
    for (int i = 0; i < strlen(c); i++) {
        *ptr++ = c[i];
    }

    *ptr++ = '.';
    while (precision--) {
        f *= 10.0;
        ch = f;
        *ptr++ = '0' + ch;
        f -= ch;
    }

    for (int i = strlen(ptr) - 1; ptr[i] == '0'; i--) {
        ptr[i] = '\0';
    }

    *ptr = 0;
}

int itoa(char *dest, int num) {
    u32 start = 0;
    if (num < 0) {
        dest[start++] = '-';
        num = -num;
    }

    char buff[16];
    buff[15] = '\0';
    u32 i = 14;
    while (num > 0) {
        u32 rem = num % 10;
        buff[i--] = '0' + rem;
        num /= 10;
    }

    strcpy(dest + start, buff + i + 1);
    return start + 14 - i;
}

int atoi(char *str) {
    int res = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        res = res * 10 + str[i] - '0';
    }
    return res;
}

int int2hex(char *dest, int num) {
    u32 start = 0;
    if (num < 0) {
        dest[start++] = '-';
        num = -num;
    }
    dest[start++] = '0';
    dest[start++] = 'x';

    char buff[16];
    buff[15] = '\0';
    u32 i = 14;
    while (num > 0) {
        u32 rem = num % 16;
        if (rem <= 9) {
            buff[i--] = '0' + rem;
        } else {
            buff[i--] = 'A' + (rem - 10);
        }
        num /= 16;
    }

    strcpy(dest + start, buff + i + 1);
    return start + 14 + i;
}

void add_leading_zero(char *dest, int num) {
    if (num >= 10) {
        itoa(dest, num);
        return;
    }

    dest[0] = '0';
    dest[1] = num + '0';
}