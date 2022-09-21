/*
    Copyright (c) 2022 thatOneArchUser
    All rights reserverd
*/

#pragma once

#include "types.h"

#define low_16(address) (u16)((address) & 0xFFFF)
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF)

int string_length(char *s);
void reverse(char s[]);
void int_to_string(int n, char str[]);
bool backspace(char s[]);
bool qq(char s[]);
void append(char s[], char n);
bool compare_string(char s1[], char s2[]);
bool startswith(char str[], char what[]);
int find_matches(char str[], char what);
void split_string(char str[], char delimiter, int n, char arr[]);
int get_index(char *str, char what);
char *remove(char *str, char *what);
void remove_by_index(char str[], char dest[], int i);
int split(char *str, char delimiter, char ***dest);
void remove_item(char *arr, int i, int len);
char *to_lowercase(char *str);
int string_to_int(char *str);
int arr_len(char **arr);
char *trim(char *str);