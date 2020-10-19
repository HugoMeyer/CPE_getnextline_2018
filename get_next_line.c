/*
** EPITECH PROJECT, 2018
** get_next_line
** File description:
** get_next_line
*/

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>

int my_strlen(char const *str)
{
    int c = 0;

    if (str == NULL)
        return (0);
    while (str[c] != '\0')
        c++;
    return (c);
}

char *my_strdup(char *src)
{
    char *dest;
    int a = 0;

    if (src == NULL)
        return NULL;
    dest = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (!dest)
        return NULL;
    while (src[a] != '\0') {
        dest[a] = src[a];
        a++;
    }
    dest[a] = '\0';
    return (dest);
}

char *my_strncpy(char *dest, const char *src, int n)
{
    int nb_dest = my_strlen(dest);
    int nb_src = my_strlen(src);
    char *temp;
    int i = 0;

    temp = my_strdup(dest);
    dest = malloc(sizeof(char) * (nb_dest + nb_src + 1));
    if (!dest)
        return NULL;
    for (i = 0; i < n && src[i] != '\0' ; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

char *my_strcat(char *dest, char *src)
{
    int nb_dest = my_strlen(dest);
    int nb_src = my_strlen(src);
    int a = 0;
    int i = 0;
    char *temp;

    if (dest == NULL)
        return src;
    temp = my_strdup(dest);
    dest = malloc(sizeof(char) * (nb_dest + nb_src + 1));
    if (!dest)
        return NULL;
    for (i = 0; temp[i] != '\0'; i++)
        dest[i] = temp[i];
    dest[i] = '\0';
    for (a = 0 ; src[a] != '\0' ; a++)
        dest[nb_dest + a] = src[a];
    dest[nb_dest + a] = '\0';
    return dest;
}

char *get_next_line(int fd)
{
    static char *temp = NULL;
    char *res = NULL;
    static int j = 0;
    char *str = malloc(sizeof(char) * READ_SIZE + 1);
    int fdread = read(fd, str, READ_SIZE);

    if (fdread < 0 || str == NULL)
        return NULL;
    str[fdread] = '\0';
    temp = my_strcat(temp, str);
    if (fdread == 0 && temp[j] == '\0')
        return NULL;
    for (int i = 0; temp[j + i] != '\0'; i++) {
        if (temp[j + i] == '\n') {
            res = my_strncpy(res, temp + j, i);
            j += i + 1;
            return (res);
        }
    }
    return (get_next_line(fd));
}
