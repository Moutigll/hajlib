/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:37:40 by ele-lean          #+#    #+#             */
/*   Updated: 2026/05/19 16:12:07 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#include "../include/hprintf.h"

#define GREEN  "\033[0;32m"
#define RED	"\033[0;31m"
#define RESET  "\033[0m"

static int tests_passed = 0;
static int tests_total  = 0;


static void capture_output(int			*ret,
						   char			**out,
						   int			is_ft,
						   const char	*format,
						   va_list		*args)
{
	va_list args_copy;
	va_copy(args_copy, *args);

	int needed;
	if (is_ft)
		needed = ft_vsnprintf(NULL, 0, format, args_copy);
	else
		needed = vsnprintf(NULL, 0, format, args_copy);
	va_end(args_copy);

	if (needed < 0)
	{
		*ret = -1;
		*out = strdup("");
		return;
	}

	size_t size = needed + 1;
	char *buf = malloc(size);
	if (!buf)
	{
		*ret = -1;
		*out = strdup("");
		return;
	}

	va_copy(args_copy, *args);
	int r;
	if (is_ft)
		r = ft_vsnprintf(buf, size, format, args_copy);
	else
		r = vsnprintf(buf, size, format, args_copy);
	va_end(args_copy);

	*ret = r;
	*out = buf;
}

void test_printf(int num, const char *format, ...)
{
	tests_total++;

	va_list args;
	int ret_printf, ret_ft;
	char *out_printf, *out_ft;

	va_start(args, format);
	capture_output(&ret_printf, &out_printf, 0, format, &args);
	va_end(args);

	va_start(args, format);
	capture_output(&ret_ft, &out_ft, 1, format, &args);
	va_end(args);

	if (ret_printf == ret_ft && strcmp(out_printf, out_ft) == 0)
	{
		printf(GREEN "[  OK  ]" RESET " Test %d: %s\n", num, format);
		tests_passed++;
	}
	else
	{
		printf(RED "[ FAIL ]" RESET " Test %d: %s\n", num, format);
		if (ret_printf != ret_ft)
			printf("	Return values: printf=%d, ft_printf=%d\n",
				   ret_printf, ret_ft);
		if (strcmp(out_printf, out_ft) != 0)
		{
			printf("	Expected output: \"%s\"\n", out_printf);
			printf("	Got output:	  \"%s\"\n", out_ft);
		}
	}

	free(out_printf);
	free(out_ft);
}

int main(void)
{
	/* ----- Tests de base (existants) ----- */
	test_printf(1,  "1: test standard printf\n");
	test_printf(2,  "2: Caractère simple avec printf:	%c\n", 'A');
	test_printf(3,  "3: Chaîne avec printf: %s\n", "Hello, world!");
	test_printf(4,  "4: Plusieurs caractères avec printf:	%c %c\n", 'B', 'C');
	test_printf(5,  "5: Plusieurs chaînes avec printf: %s %s\n", "Hello", "world");
	test_printf(6,  "6: Affichage de %% avec printf:	%%\n");
	int *ptr = NULL;
	int a = 42;
	test_printf(7,  "7: test standard printf\n");
	test_printf(8,  "8: Adresse d'un pointeur NULL avec printf:	%p\n", ptr);
	test_printf(9,  "9: Adresse d'une variable avec printf:	%p\n", &a);
	int num = 1234;
	test_printf(10, "10: Entier décimal avec printf:	%d\n", num);
	test_printf(11, "11: Entier (spécificateur %%i) avec printf:	%i\n", num);
	int neg_num = -5678;
	test_printf(12, "12: Entier négatif avec printf:	%d\n", neg_num);
	test_printf(13, "13: Entier négatif (spécificateur %%i) avec printf:	%i\n", neg_num);
	unsigned int u_num = 123456;
	test_printf(14, "14: Entier non signé avec printf:	%u\n", u_num);
	unsigned int u_zero = 0;
	test_printf(15, "15: Zéro non signé avec printf:	%u\n", u_zero);
	unsigned int u_max = 4294967295;
	test_printf(16, "16: Valeur maximale unsigned avec printf:	%u\n", u_max);

	/* Test combiné (chaîne formatée longue) */
	test_printf(17,
		"%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%",
		'A', "42", 42, 42, 42, 42, 42,
		'B', "-42", -42, -42, -42, -42, 42,
		'C', "0", 0, 0, 0, 0, 42, 0);

	/* ----- Tests des modificateurs de longueur ----- */
	printf("\n--- Modificateurs de longueur ---\n");

	size_t sz = 12345;
	test_printf(18, "18: size_t classique: %zu\n", sz);
	sz = 0;
	test_printf(19, "19: size_t zero: %zu\n", sz);
	sz = SIZE_MAX;
	test_printf(20, "20: size_t max: %zu\n", sz);

	ssize_t ssz = -12345;
	test_printf(21, "21: ssize_t negatif: %zd\n", ssz);
	ssz = 0;
	test_printf(22, "22: ssize_t zero: %zd\n", ssz);

	unsigned long long ull = 123456789012345ULL;
	test_printf(23, "23: unsigned long long: %llu\n", ull);
	ull = 0;
	test_printf(24, "24: unsigned long long zero: %llu\n", ull);
	ull = ULLONG_MAX;
	test_printf(25, "25: unsigned long long max: %llu\n", ull);

	long long ll = -123456789012345LL;
	test_printf(26, "26: long long negatif: %lld\n", ll);
	ll = 0;
	test_printf(27, "27: long long zero: %lld\n", ll);
	ll = LLONG_MAX;
	test_printf(28, "28: long long max: %lld\n", ll);

	long l = -123456L;
	test_printf(29, "29: long negatif: %ld\n", l);

	unsigned long ul = 123456UL;
	test_printf(30, "30: unsigned long: %lu\n", ul);

	intmax_t j = INTMAX_MAX;
	test_printf(31, "31: intmax_t max: %jd\n", j);
	j = INTMAX_MIN;
	test_printf(32, "32: intmax_t min: %jd\n", j);

	uintmax_t ju = UINTMAX_MAX;
	test_printf(33, "33: uintmax_t max: %ju\n", ju);

	signed char hhd = -128;
	test_printf(34, "34: signed char min: %hhd\n", hhd);
	hhd = 127;
	test_printf(35, "35: signed char max: %hhd\n", hhd);

	unsigned char hhu = 255;
	test_printf(36, "36: unsigned char max: %hhu\n", hhu);

	short hd = -32768;
	test_printf(37, "37: short min: %hd\n", hd);

	unsigned short hu = 65535;
	test_printf(38, "38: unsigned short max: %hu\n", hu);

	ptrdiff_t td = -123;
	test_printf(39, "39: ptrdiff_t negatif: %td\n", td);
	test_printf(40, "40: ptrdiff_t (unsigned): %tu\n", (ptrdiff_t)123);

	/* Combinaisons largeur / précision / hexa */
	test_printf(41, "41: size_t avec largeur: %10zu\n", sz);
	test_printf(42, "42: long long précision: %.10lld\n", ll);
	test_printf(43, "43: unsigned long long hex: %llx\n", ull);
	test_printf(44, "44: unsigned long long HEX: %llX\n", ull);

	/* ----- Résumé final ----- */
	printf("\n=== Résumé : %d / %d tests réussis ", tests_passed, tests_total);
	if (tests_passed == tests_total)
		printf(GREEN "✓" RESET);
	else
		printf(RED "✗" RESET);
	printf(" ===\n");

	return (tests_passed == tests_total ? 0 : 1);
}
