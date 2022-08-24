#include <stdint.h>
#include <stdbool.h>
#include "../kernel/mem.h"
#include "string.h"

int string_length(char *s) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = string_length(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void int_to_string(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len+1] = '\0';
}

bool backspace(char s[]) {
    int len = string_length(s);
    if (len > 0) {
        s[len - 1] = '\0';
        return true;
    } else {
        return false;
    }
}

int compare_string(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

bool startswith(char str[], char what[]) {
    int len = string_length(what);
    for (int i = 0; i < len; i++) {
        if (what[i] != str[i]) {
            return false;
        }
    }
    return true;
}

int find_matches(char str[], char what) {
    int matches = 0;
    for (int i = 0; i < string_length(str); i++) {
        if (str[i] == what) matches++;
    }
    return matches;
}

int get_index(char *str, char what) {
    for (int i = 0; i < string_length(str); i++) {
        if (str[i] == what) return i;
    }
    return string_length(str) + 1;
}

char *remove(char *str, char *what) { }

char *remove_by_index(char str[], int i) {
    str[i] = '\0';
    return str;
}