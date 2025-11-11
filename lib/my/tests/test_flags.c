/*
** EPITECH PROJECT, 2025
** G-CPE-101-PAR-1-1-myprintf-24
** File description:
** Test file
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/my.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(my_printf, classic_string, .init = redirect_all_std)
{
    my_printf("Hello World !");
    cr_assert_stdout_eq_str("Hello World !");
}

Test(my_printf, test_c, .init = redirect_all_std)
{
    my_printf("%c", 'k');
    cr_assert_stdout_eq_str("k");
}
Test(my_printf, test_c_string, .init = redirect_all_std)
{
    my_printf("Hello W%crld !", 'o');
    cr_assert_stdout_eq_str("Hello World !");
}

Test(my_printf, test_s, .init = redirect_all_std)
{
    my_printf("%s", "Lorem ipsum dolor sit amet");
    cr_assert_stdout_eq_str("Lorem ipsum dolor sit amet");
}
Test(my_pritnf, test_s_multiple, .init = redirect_all_std)
{
    my_printf("%s %s", "Hello", "World");
    cr_assert_stdout_eq_str("Hello World");
}

Test(my_printf, test_simple_string, .init = redirect_all_std)
{
    my_printf("Il est écrit: aide %s, le ciel %c'aidera !", "toi", 't');
    cr_assert_stdout_eq_str("Il est écrit: aide toi, le ciel t'aidera !");
}

Test(my_printf, test_percentage, .init = redirect_all_std)
{
    my_printf("%%");
    cr_assert_stdout_eq_str("%");
}
Test(my_printf, test_percentage_in_string, .init = redirect_all_std)
{
    my_printf("Pourcentage de 90%% de succès");
    cr_assert_stdout_eq_str("Pourcentage de 90% de succès");
}

Test(my_printf, non_existant_flag, .init = redirect_all_std)
{
    int x = my_printf("%w");
    cr_assert_eq(x, -1);
}

Test(my_printf, test_simple_hexadecimal_lower, .init = redirect_all_std)
{
    my_printf("%x", 4000);
    cr_assert_stdout_eq_str("fa0");
}

Test(my_printf, test_string_hexadecimal_lower, .init = redirect_all_std)
{
    my_printf("L'hexadecimal de 4000 est %x", 4000);
    cr_assert_stdout_eq_str("L'hexadecimal de 4000 est fa0");
}

Test(my_printf, test_simple_hexadecimal_upper, .init = redirect_all_std)
{
    my_printf("%X", 4000);
    cr_assert_stdout_eq_str("FA0");
}

Test(my_printf, test_string_hexadecimal_upper, .init = redirect_all_std)
{
    my_printf("L'hexadecimal de 4000 est %X", 4000);
    cr_assert_stdout_eq_str("L'hexadecimal de 4000 est FA0");
}

Test(my_printf, test_simple_octal_upper, .init = redirect_all_std)
{
    my_printf("%o", 4000);
    cr_assert_stdout_eq_str("7640");
}
Test(my_printf, test_string_octal_upper, .init = redirect_all_std)
{
    my_printf("L'octal de 4000 est %o", 4000);
    cr_assert_stdout_eq_str("L'octal de 4000 est 7640");
}

Test(my_printf, test_simple_u, .init = redirect_all_std)
{
    my_printf("%u", 4000);
    cr_assert_stdout_eq_str("4000");
}

Test(my_printf, test_string_u_upper, .init = redirect_all_std)
{
    my_printf("J'ai %u bananes (ca fait beaucoup)", 4000);
    cr_assert_stdout_eq_str("J'ai 4000 bananes (ca fait beaucoup)");
}

Test(my_printf, test_string_u_upper_with_negative_parameter, .init = redirect_all_std)
{
    my_printf("Test flag u de 4000 est %u", -4000);
    cr_assert_stdout_eq_str("Test flag u de 4000 est 4000");
}

Test(my_printf, test_simple_integer, .init = redirect_all_std)
{
    my_printf("%i", 4000);
    cr_assert_stdout_eq_str("4000");
}

Test(my_printf, test_string_integer, .init = redirect_all_std)
{
    my_printf("Test flag i de 4000 est %i", 4000);
    cr_assert_stdout_eq_str("Test flag i de 4000 est 4000");
}
