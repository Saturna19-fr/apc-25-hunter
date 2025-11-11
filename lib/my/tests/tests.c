#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <stdio.h>
#include "../include/my.h"

char *my_strcat(char *rtval, char *appendstr);

Test(my_strcat, two_words)
{
    char *first = "Hello";
    char *second = "World";
    char *rv = my_strcat(first, second);

    cr_assert_str_eq(rv, "HelloWorld");
}

Test(my_strcat, two_words_with_one_empty_string)
{
    char *first = "";
    char *second = "World";
    char *rv = my_strcat(first, second);

    cr_assert_str_eq(rv, "World");
}

Test(my_str_to_word_array, word_array_empty)
{
    char *string = "";
    char **array_of_char = my_str_to_word_array(string);
    char **result = {
        ""
    };

    cr_assert_eq(array_of_char, result);
}
