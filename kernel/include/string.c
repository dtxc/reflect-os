/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#include "mem.h"
#include "stdio.h"
#include "types.h"
#include "stdlib.h"

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

bool backspace(char s[]) {
    int len = strlen(s);
    if (len > 0) {
        s[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

bool startswith(char str[], char what[]) {
    int len = strlen(what);
    for (int i = 0; i < len; i++) {
        if (what[i] != str[i]) {
            return false;
        }
    }
    return true;
}

int split(char *str, char delimiter, char ***dest) {
    int count = 1;
    int token_len = 1;
    int i = 0;
    char *p;
    char *t;

    p = str;
    while (*p != '\0') {
        if (*p == delimiter) count++;
        p++;
    }

    *dest = (char **) malloc(count);
    if (*dest == 0) return 1;
    p = str;
    while (*p != '\0') {
        if (*p == delimiter) {
            (*dest)[i] = (char *) malloc(count);
            if ((*dest)[i] == 0) return 1;
            token_len = 0;
            i++;
        }
        p++;
        token_len++;
    }
    (*dest)[i] = (char *) malloc(token_len);
    if ((*dest)[i] == 0) return 1;
    i = 0;
    p = str;
    t = ((*dest)[i]);
    while (*p != '\0') {
        if (*p != delimiter && *p != '\0') {
            *t = *p;
            t++;
        } else {
            *t = '\0';
            i++;
            t = ((*dest)[i]);
        }
        p++;
    }

    return count;
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