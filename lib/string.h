#pragma once

#include <stdint.h>
#include <stdbool.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

int string_length(char *s);
void reverse(char s[]);
void int_to_string(int n, char str[]);
bool backspace(char s[]);
void append(char s[], char n);
int compare_string(char s1[], char s2[]);
bool startswith(char str[], char what[]);
int find_matches(char str[], char what);
void split_string(char str[], char delimiter, int n, char arr[]);
int get_index(char *str, char what);
char *remove(char *str, char *what);
void remove_by_index(char str[], char dest[], int i);
//void split(char *str, char *dest, char delimiter, int n);
int split(char *str, char delimiter, char ***arr);
void remove_item(char *arr, int i, int len);