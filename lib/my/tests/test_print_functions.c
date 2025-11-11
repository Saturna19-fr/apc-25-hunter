/*
** EPITECH PROJECT, 2025
** G-CPE-101-PAR-1-1-myprintf-24
** File description:
** Test file
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <criterion/logging.h>
#include "../include/my.h"
#include <limits.h>

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(write_to_stderr, error_character, .init = redirect_all_std)
{
    write_to_stderr('c');
    cr_assert_stderr_eq_str("c");
}

Test(string_to_stderr, error_string, .init = redirect_all_std)
{
    string_to_stderr("This is an error");
    cr_assert_stderr_eq_str("This is an error");
}

Test(print_char, out_character, .init = redirect_all_std)
{
    print_char('X');
    cr_assert_stdout_eq_str("X");

}

Test(print_char, out_character_lowercase, .init = redirect_all_std)
{
    print_char('x');
    cr_assert_stdout_eq_str("x");

}

Test(print_string, out_string, .init = redirect_all_std)
{
    print_string("This is your last warning");
    cr_assert_stdout_eq_str("This is your last warning");

}

Test(print_string, out_string_lowercase, .init = redirect_all_std)
{
    print_string("this is your last warning");
    cr_assert_stdout_eq_str("this is your last warning");

}

Test(print_nb, print_number_base10, .init = redirect_all_std)
{
    print_nb(651144, 10);
    cr_assert_stdout_eq_str("651144");
}

Test(print_nb, print_number_maxint, .init = redirect_all_std)
{
    print_nb(INT_MAX, 10);
    cr_assert_stdout_eq_str("2147483647");
}

Test(print_nb, print_number_minint, .init = redirect_all_std)
{
    print_nb(INT_MIN, 10);
    cr_assert_stdout_eq_str("-2147483648");
}

Test(print_nb, print_number_negative, .init = redirect_all_std)
{
    print_nb(-20, 10);
    cr_assert_stdout_eq_str("-20");
}
