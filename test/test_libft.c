/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ele-lean <ele-lean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 17:38:43 by ele-lean          #+#    #+#             */
/*   Updated: 2024/10/17 14:01:51 by ele-lean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>
#include <fcntl.h>

void	test_ft_atoi(void)
{
	printf("\n(1/23)Testing ft_atoi:\n");
	printf("ft_atoi(\"   -123abc\") Expected '-123', got: '%d'\n", ft_atoi("   -123abc"));
	printf("ft_atoi(\"42\") Expected '42', got: '%d'\n", ft_atoi("42"));
	printf("ft_atoi(\"   +42\") Expected '42' got: '%d'\n", ft_atoi("   +42"));
	printf("ft_atoi(\"   0\") Expected '0' got: '%d'\n", ft_atoi("   0"));
}

void	test_ft_bzero(void)
{
	char	str[50] = "Hello, World!";
	char	empty[50] = "This will be zeroed";

	printf("\n(2/23)Testing ft_bzero:\n");
	printf("Before ft_bzero on str (first 6 chars): '%s'\n", str);
	ft_bzero(str, 6);
	printf("After ft_bzero (first 6 chars zeroed): '%s' (Expected: '\\0\\0\\0\\0\\0\\0 World!')\n", str + 6);
	printf("Before ft_bzero on empty (all chars): '%s'\n", empty);
	ft_bzero(empty, sizeof(empty));
	printf("After ft_bzero (all chars zeroed): '%s' (Expected: empty string)\n", empty);
}

void	test_ft_calloc(void)
{
	int	*arr;
	int	i;

	arr = ft_calloc(5, sizeof(int));
	printf("\n(3/23)Testing ft_calloc:\n");
	printf("ft_calloc(5, sizeof(int)) Expected: array of 5 zeroed ints\n");
	for (i = 0; i < 5; i++)
		printf("arr[%d] = %d\n", i, arr[i]);
	free(arr);
}

void	test_ft_isalnum(void)
{
	printf("\n(4/23)Testing ft_isalnum:\n");
	printf("ft_isalnum('1') = %d (Expected: 1)\n", ft_isalnum('1'));
	printf("ft_isalnum('A') = %d (Expected: 1)\n", ft_isalnum('A'));
	printf("ft_isalnum('#') = %d (Expected: 0)\n", ft_isalnum('#'));
}

void	test_ft_isalpha(void)
{
	printf("\n(5/23)Testing ft_isalpha:\n");
	printf("ft_isalpha('A') = %d (Expected: 1)\n", ft_isalpha('A'));
	printf("ft_isalpha('a') = %d (Expected: 1)\n", ft_isalpha('a'));
	printf("ft_isalpha('1') = %d (Expected: 0)\n", ft_isalpha('1'));
	printf("ft_isalpha('#') = %d (Expected: 0)\n", ft_isalpha('#'));
}

void	test_ft_isascii(void)
{
	printf("\n(6/23)Testing ft_isascii:\n");
	printf("ft_isascii(65) = %d (Expected: 1)\n", ft_isascii(65));
	printf("ft_isascii(128) = %d (Expected: 0)\n", ft_isascii(128));
}

void	test_ft_isdigit(void)
{
	printf("\n(7/23)Testing ft_isdigit:\n");
	printf("ft_isdigit('1') = %d (Expected: 1)\n", ft_isdigit('1'));
	printf("ft_isdigit('a') = %d (Expected: 0)\n", ft_isdigit('a'));
}

void	test_ft_isprint(void)
{
	printf("\n(8/23)Testing ft_isprint:\n");
	printf("ft_isprint(32) = %d (Expected: 1)\n", ft_isprint(32));
	printf("ft_isprint(127) = %d (Expected: 0)\n", ft_isprint(127));
}

void	test_ft_memchr(void)
{
	char str[] = "Hello, World!";
	char *result;

	printf("\n(9/23)Testing ft_memchr:\n");
	result = ft_memchr(str, 'W', 13);
	printf("ft_memchr('%s', 'W', 13) = '%s' (Expected: 'World!')\n", str, result);
	result = ft_memchr(str, 'z', 13);
	printf("ft_memchr('%s', 'z', 13) = '%p' (Expected: '(nil)')\n", str, result);
}

void	test_ft_memcmp(void)
{
	char s1[] = "abcdef";
	char s2[] = "abcDef";

	printf("\n(10/23)Testing ft_memcmp:\n");
	printf("ft_memcmp('%s', '%s', 6) = %d (Expected: > 0)\n", s1, s2, ft_memcmp(s1, s2, 6));
	printf("ft_memcmp('%s', '%s', 3) = %d (Expected: 0)\n", s1, s2, ft_memcmp(s1, s2, 3));
}

void	test_ft_memcpy(void)
{
	char src[] = "Hello, World!";
	char dest[50];

	printf("\n(11/23)Testing ft_memcpy:\n");
	ft_memcpy(dest, src, 13);
	printf("ft_memcpy(dest, src, 13) = %s (Expected: Hello, World!)\n", dest);
}

void	test_ft_memmove(void)
{
	char dest[50] = "Hello, World!";
	char src[] = "Beautiful ";

	printf("\n(12/23)Testing ft_memmove:\n");
	printf("Before memmove: %s\n", dest);
	ft_memmove(dest + 7, src, 10);
	printf("After memmove, expected 'Hello, Beautiful ', got: '%s'\n", dest);
	char overlap[20] = "123456789";
	printf("Before overlapping memmove: %s\n", overlap);
	ft_memmove(overlap + 2, overlap, 9);
	printf("After overlapping memmove, expected '12123456789', got: '%s'\n", overlap);
}

void	test_ft_memset(void)
{
	char	str[50] = "Hello, world!";

	printf("\n(13/23)Testing ft_memset:\n");
	printf("Before memset: %s\n", str);
	ft_memset(str, 'x', 5);
	printf("After memset: %s (Expected: 'xxxxx, world!')\n", str);
}

void	test_ft_strchr(void)
{
	const char *str = "Hello, World!";
	char ch = 'o';
	char *result;

	printf("\n(14/23)Testing ft_strchr:\n");
	result = ft_strchr(str, ch);
	printf("ft_strchr('%s', '%c') = '%s' (Expected: 'o, World!')\n", str, ch, result);
}

void	test_ft_strdup(void)
{
	const char *s = "Hello, World!";
	char *dup;

	printf("\n(15/23)Testing ft_strdup:\n");
	dup = ft_strdup(s);
	printf("ft_strdup('%s') = '%s' (Expected: '%s')\n", s, dup, s);
	free(dup);
}

void	test_ft_strlcat(void)
{
	char dest[50] = "Hello, ";
	char src[] = "World!";
	size_t size = 50;
	size_t result;

	printf("\n(16/23)Testing ft_strlcat:\n");
	result = ft_strlcat(dest, src, size);
	printf("ft_strlcat(dest, src, 50) = %zu, dest = '%s' (Expected: 13, 'Hello, World!')\n", result, dest);
}

void	test_ft_strlcpy(void)
{
	char dest[50];
	char src[] = "Hello, World!";
	size_t result;

	printf("\n(17/23)Testing ft_strlcpy:\n");
	result = ft_strlcpy(dest, src, 50);
	printf("ft_strlcpy(dest, src, 50) = %zu, dest = '%s' (Expected: 13, 'Hello, World!')\n", result, dest);
}

void	test_ft_strlen(void)
{
	printf("\n(18/23)Testing ft_strlen:\n");
	printf("ft_strlen(\"Hello\") = %zu (Expected: 5)\n", ft_strlen("Hello"));
	printf("ft_strlen(\"\") = %zu (Expected: 0)\n", ft_strlen(""));
}

void	test_ft_strncmp(void)
{
	const char *s1 = "Hello";
	const char *s2 = "Helium";

	printf("\n(19/23)Testing ft_strncmp:\n");
	printf("ft_strncmp('%s', '%s', 3) = %d (Expected: 0)\n", s1, s2, ft_strncmp(s1, s2, 3));
	printf("ft_strncmp('%s', '%s', 5) = %d (Expected: > 0)\n", s1, s2, ft_strncmp(s1, s2, 5));
}

void	test_ft_strnstr(void)
{
	const char *big = "Hello, World!";
	const char *little = "World";

	printf("\n(20/23)Testing ft_strnstr:\n");
	printf("ft_strnstr('%s', '%s', 13) = '%s' (Expected: 'World!')\n", big, little, ft_strnstr(big, little, 13));
}

void	test_ft_strrchr(void)
{
	const char *str = "Hello, World!";
	char ch = 'o';
	char *result;

	printf("\n(21/23)esting ft_strrchr:\n");
	result = ft_strrchr(str, ch);
	printf("ft_strrchr('%s', '%c') = '%s' (Expected: 'orld!')\n", str, ch, result);
}

void	test_ft_tolower(void)
{
	printf("\n(22/23)Testing ft_tolower:\n");
	printf("ft_tolower('A') = '%c' (Expected: 'a')\n", ft_tolower('A'));
	printf("ft_tolower('Z') = '%c' (Expected: 'z')\n", ft_tolower('Z'));
	printf("ft_tolower('a') = '%c' (Expected: 'a')\n", ft_tolower('a'));
	printf("ft_tolower('1') = '%c' (Expected: '1')\n", ft_tolower('1'));
}

void	test_ft_toupper(void)
{
	printf("\n(23/23)Testing ft_toupper:\n");
	printf("ft_toupper('a') = '%c' (Expected: 'A')\n", ft_toupper('a'));
	printf("ft_toupper('z') = '%c' (Expected: 'Z')\n", ft_toupper('z'));
	printf("ft_toupper('A') = '%c' (Expected: 'A')\n", ft_toupper('A'));
}
//Test of the Part2
void	test_ft_substr(void)
{
	const char *chain = "Hello world!";

	printf("\n(1/11)Testing ft_substr\n");
	printf("ft_substr(%s, 3, 5) = '%s' (Expected: 'lo wo')\n", chain, ft_substr(chain, 3, 5));
	printf("ft_substr(%s, 3, 100) = '%s' (Expected: 'lo world!')\n", chain, ft_substr(chain, 3, 100));
	printf("ft_substr(\"\", 3, 5) = '%s' (Expected: '')\n", ft_substr("", 3, 5));
	printf("ft_substr(%s, 100, 5) = '%s' (Expected: '')\n", chain, ft_substr(chain, 100, 5));
}

void	test_ft_strjoin(void)
{
	printf("\n(2/11)Testing ft_strjoin\n");
	printf("ft_strjoin(\"Hello \", \"world!\") = '%s' (Expected: 'Hello world!')\n", ft_strjoin("Hello ", "world!"));
	printf("ft_strjoin(\"\", \"world!\") = '%s' (Expected: 'world!')\n", ft_strjoin("", "world!"));
	printf("ft_strjoin(\"Hello \", \"\") = '%s' (Expected: 'Hello ')\n", ft_strjoin("Hello ", ""));
	printf("ft_strjoin(\"\", \"\") = '%s' (Expected: '')\n", ft_strjoin("", ""));
}

void	test_ft_strtrim(void)
{
	printf("\n(3/11)Testing ft_strtrim\n");
	printf("ft_strtrim(\"**Hello World*-*\", \"*-\"): '%s' (Expected: 'Hello World')\n", ft_strtrim("**Hello World*-*", "*-"));
	printf("ft_strtrim(\"Hello\", \"\") '%s' (Expected: 'Hello')\n", ft_strtrim("Hello", ""));
	printf("ft_strtrim(\"\", \" \") '%s' (Expected: '')\n", ft_strtrim("", " "));

}
void	ft_free_split(char **split, int words)
{
	int	i;

	i = 0;
	while (i < words)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	test_ft_split(void)
{
	char	**result;
	int		i;

	printf("\n(4/11)Testing ft_split\n");
	result = ft_split("Hello world this is a test", ' ');
	printf("ft_split(\"Hello world this is a test\", ' ') Expected: ['Hello', 'world', 'this', 'is', 'a', 'test', NULL]\n");
	i = 0;
	while (result[i])
	{
		printf("result[%d] = '%s'\n", i, result[i]);
		i++;
	}
	printf("result[%d] = '%s'\n", i, result[i]);
	ft_free_split(result, i);
	result = ft_split("  Hello  world  this  is  a  test  ", ' ');
	printf("\nft_split(\"  Hello  world  this  is  a  test  \", ' ') Expected: ['Hello', 'world', 'this', 'is', 'a', 'test', NULL]\n");
	i = 0;
	while (result[i])
	{
		printf("result[%d] = '%s'\n", i, result[i]);
		i++;
	}
	printf("result[%d] = '%s'\n", i, result[i]);
	ft_free_split(result, i);
	result = ft_split("NoDelimiterHere", ' ');
	printf("\nft_split(\"NoDelimiterHere\", ' ') Expected: ['NoDelimiterHere', NULL]\n");
	i = 0;
	while (result[i])
	{
		printf("result[%d] = '%s'\n", i, result[i]);
		i++;
	}
	printf("result[%d] = '%s'\n", i, result[i]);
	ft_free_split(result, i);
	result = ft_split("", ' ');
	printf("\nft_split(\"\", ' ') Expected: [NULL]\n");
	if (result[0] == NULL)
		printf("Result is NULL as expected\n");
	else
		printf("Unexpected result\n");
	ft_free_split(result, i);
	result = ft_split("   ", ' ');
	printf("\nft_split(\"   \", ' ') Expected: [NULL]\n");
	if (result[0] == NULL)
		printf("Result is NULL as expected\n");
	else
		printf("Unexpected result\n");
	ft_free_split(result, i);
}

void	test_ft_itoa(void)
{
	printf("\n(5/11)Testing ft_itoa:\n");
	printf("ft_itoa(42) = '%s' (Expected: '42')\n", ft_itoa(42));
	printf("ft_itoa(-42) = '%s' (Expected: '-42')\n", ft_itoa(-42));
	printf("ft_itoa(-0) = '%s' (Expected: '0')\n", ft_itoa(-0));
	printf("ft_itoa(-2147483648) = '%s' (Expected: '-2147483648')\n", ft_itoa(-2147483648));
	printf("ft_itoa(2147483647) = '%s' (Expected: '2147483647')\n", ft_itoa(2147483647));
}
char	fttoupper(unsigned int index, char c)
{
	(void)index;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
void	test_ft_strmapi(void)
{
	printf("\n(6/11)Testing ft_strmapi:\n");
	char	*result1 = ft_strmapi("hello", fttoupper);
	printf("ft_strmapi(\"hello\", ft_toupper) = \"%s\" (Expected: \"HELLO\")\n", result1);
	free(result1);
	char	*result3 = ft_strmapi("", fttoupper);
	printf("ft_strmapi(\"\", ft_toupper) = \"%s\" (Expected: \"\")\n", result3);
	free(result3);
	char	*result4 = ft_strmapi("a!@#$%", fttoupper);
	printf("ft_strmapi(\"a!@#$\", ft_toupper) = \"%s\" (Expected: \"A!@#$\")\n", result4);
	free(result4);
	char	*result5 = ft_strmapi(NULL, fttoupper);
	printf("ft_strmapi(NULL, ft_toupper) = \"%s\" (Expected: NULL)\n", result5);
	free(result5);
	char	*result6 = ft_strmapi("test", NULL);
	printf("ft_strmapi(\"test\", NULL) = \"%s\" (Expected: NULL)\n", result6);
	free(result6);
}
#include <fcntl.h> // Pour O_RDWR
#include <unistd.h>

void	ftttoupper(unsigned int index, char *c)
{
	(void)index;
	if (*c >= 'a' && *c <= 'z')
	{
		*c = *c - 32;
	}
}

void test_ft_striteri(void)
{
	char	str1[] = "hello";
	char	str2[] = "world";

	printf("\n(7/11)Testing ft_striteri:\n");
	ft_striteri(str1, ftttoupper);
	printf("After ft_striteri on \"hello\": \"%s\" (Expected: \"HELLO\")\n", str1);
	ft_striteri(str2, ftttoupper);
	printf("After ft_striteri on \"world\": \"%s\" (Expected: \"WORLD\")\n", str2);
	char	str3[] = "Hello World!";
	ft_striteri(str3, ftttoupper);
	printf("After ft_striteri on \"Hello World!\": \"%s\" (Expected: \"HELLO WORLD!\")\n", str3);
	char	str4[] = "";
	ft_striteri(str4, ftttoupper);
	printf("After ft_striteri on empty string: \"%s\" (Expected: \"\")\n", str4);
}

void	test_ft_putchar_fd(void)
{
	printf("\n(8/11) Testing ft_putchar_fd:\n");
	ft_putchar_fd('A', STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	int	fd = open("test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open file");
		return ;
	}
	ft_putchar_fd('B', fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	printf("Character 'B' written to 'test_output.txt'.\n");
}

void test_ft_putstr_fd(void)
{
	printf("\n(9/11) Testing ft_putstr_fd:\n");
	ft_putstr_fd("Hello, World!", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	int	fd = open("test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open file");
		return ;
	}
	ft_putstr_fd("Hello, file!", fd);
	ft_putstr_fd("\n", fd);
	close(fd);
	printf("String 'Hello, file!' written to 'test_output.txt'.\n");
}

void	test_ft_putendl_fd(void)
{
	printf("\n(10/11) Testing ft_putendl_fd:\n");
	ft_putendl_fd("Hello, World!", STDOUT_FILENO);
	int fd = open("test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open file");
		return ;
	}
	ft_putendl_fd("Hello, file!", fd);
	close(fd);
	printf("String 'Hello, file!' written to 'test_output.txt' with a newline.\n");
}

void test_ft_putnbr_fd(void)
{
	printf("\n(11/11) Testing ft_putnbr_fd:\n");
	printf("Output to STDOUT: ");
	ft_putnbr_fd(42, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	int fd = open("test_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Failed to open file");
		return ;
	}
	ft_putnbr_fd(12345, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(-9876, fd);
	ft_putchar_fd('\n', fd);
	ft_putnbr_fd(0, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
	printf("Numbers '12345', '-9876', and '0' written to 'test_output.txt'.\n");
	unlink("test_output.txt");
}

void	test_ft_lstnew(void)
{
	printf("\n(1/9) Testing ft_lstnew:\n");
	char	*content1 = "Hello, world!";
	t_list *node1 = ft_lstnew(content1);
	if (node1 && node1->content == content1 && node1->next == NULL)
		printf("Test 1 passed: content = '%s', next = %p\n", (char *)node1->content, node1->next);
	else
		printf("Test 1 failed\n");
	int	content2 = 42;
	t_list *node2 = ft_lstnew(&content2);
	if (node2 && *(int *)(node2->content) == content2 && node2->next == NULL)
		printf("Test 2 passed: content = %d, next = %p\n", *(int *)(node2->content), node2->next);
	else
		printf("Test 2 failed\n");
	t_list *node3 = ft_lstnew(NULL);
	if (node3 && node3->content == NULL && node3->next == NULL)
		printf("Test 3 passed: content = NULL, next = %p\n", node3->next);
	else
		printf("Test 3 failed\n");
	free(node1);
	free(node2);
	free(node3);
}

void	test_ft_lstadd_front(void)
{
	printf("\n(2/9) Testing ft_lstadd_front:\n");
	t_list	*head = NULL;
	char	*content1 = "First node";
	t_list	*node1 = ft_lstnew(content1);
	printf("Test 1: Adding to an empty list\n");
	ft_lstadd_front(&head, node1);
	if (head == node1 && head->content == content1 && head->next == NULL)
		printf("Test 1 passed: content = '%s', next = %p\n", (char *)head->content, head->next);
	else
		printf("Test 1 failed\n");
	char	*content2 = "New first node";
	t_list	*node2 = ft_lstnew(content2);
	printf("Test 2: Adding to a non-empty list\n");
	ft_lstadd_front(&head, node2);
	if (head == node2 && head->content == content2 && head->next == node1)
		printf("Test 2 passed: content = '%s', next content = '%s'\n", (char *)head->content, (char *)head->next->content);
	else
		printf("Test 2 failed\n");
	free(node1);
	free(node2);
}

void	free_list(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = lst->next;
		free(lst);
		lst = temp;
	}
}

void	test_ft_lstsize(void)
{
	printf("\n(3/9) Testing ft_lstsize:\n");
	t_list	*elem1 = ft_lstnew("Element 1");
	t_list	*elem2 = ft_lstnew("Element 2");
	t_list	*elem3 = ft_lstnew("Element 3");

	ft_lstadd_front(&elem1, elem2);
	ft_lstadd_front(&elem1, elem3);
	int size = ft_lstsize(elem1);
	printf("List size: %d (Expected: 3)\n", size);
	t_list	*empty_list = NULL;
	size = ft_lstsize(empty_list);
	printf("Empty list size: %d (Expected: 0)\n", size);
	free_list(elem1);
}
void test_ft_lstlast(void)
{
	printf("\n(4/9) Testing ft_lstlast:\n");
	t_list	*elem1 = ft_lstnew("First");
	t_list	*elem2 = ft_lstnew("Second");
	t_list	*elem3 = ft_lstnew("Third");

	elem1->next = elem2;
	elem2->next = elem3;
	elem3->next = NULL;
	t_list	*last = ft_lstlast(elem1);
	if (last)
		printf("Last element content: %s (Expected: 'Third')\n", (char *)last->content);
	else
		printf("List is empty (Expected: 'Third')\n");
	free(elem1);
	free(elem2);
	free(elem3);
}
void test_ft_lstadd_back(void)
{
	printf("\n(5/9) Testing ft_lstadd_back:\n");
	t_list	*list = NULL;
	t_list	*elem1 = ft_lstnew("First");
	t_list	*elem2 = ft_lstnew("Second");

	ft_lstadd_back(&list, elem1);
	printf("Added: %s\n", (char *)list->content);
	ft_lstadd_back(&list, elem2);
	printf("Added: %s\n", (char *)list->next->content);
	free_list(list);
}

void	del_content(void *content)
{
	free(content);
}

void	test_ft_lstdelone(void)
{
	printf("\n(6/9) Testing ft_lstdelone:\n");
	char	*content = malloc(20 * sizeof(char));
	ft_strlcpy(content, "Hello, world!", 13);
	t_list	*node = ft_lstnew(content);
	ft_lstdelone(node, del_content);
	printf("Node deleted successfully.\n");
}

void	test_ft_lstclear(void)
{
	printf("\n(7/9) Testing ft_lstclear:\n");
	t_list	*node1 = ft_lstnew(malloc(20));
	ft_strlcpy(node1->content, "Node 1", 20);
	t_list	*node2 = ft_lstnew(malloc(20));
	ft_strlcpy(node2->content, "Node 2", 20);
	t_list	*node3 = ft_lstnew(malloc(20));
	ft_strlcpy(node3->content, "Node 3", 20);
	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;
	ft_lstclear(&node1, del_content);
	if (node1 == NULL)
		printf("List cleared successfully.\n");
	else
		printf("List not cleared: first node still exists.\n");
}

void to_uppercase(void *content)
{
	char	*str = (char *)content;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
	}
}

void test_ft_lstiter(void)
{
	printf("\n(8/9) Testing ft_lstiter:\n");
	t_list *node1 = ft_lstnew(malloc(20));
	ft_strlcpy(node1->content, "hello", 20);
	t_list *node2 = ft_lstnew(malloc(20));
	ft_strlcpy(node2->content, "world", 20);
	node1->next = node2;
	node2->next = NULL;
	ft_lstiter(node1, to_uppercase);
	printf("First node content: %s (Expected: HELLO)\n", (char *)node1->content);
	printf("Second node content: %s (Expected: WORLD)\n", (char *)node2->content);
	free(node1->content);
	free(node1);
	free(node2->content);
	free(node2);
}

void *double_value(void *content)
{
	int *new_content = malloc(sizeof(int));
	if (new_content)
		*new_content = (*(int *)content) * 2; // Double la valeur
	return new_content;
}

void	test_ft_lstmap(void)
{
	printf("\n(9/9) Testing ft_lstmap:\n");
	t_list *node1 = ft_lstnew(malloc(sizeof(int)));
	*(int *)(node1->content) = 1;
	t_list *node2 = ft_lstnew(malloc(sizeof(int)));
	*(int *)(node2->content) = 2;
	node1->next = node2;
	node2->next = NULL;
	t_list *new_list = ft_lstmap(node1, double_value, del_content);
	printf("First new node content: %d (Expected: 2)\n", *(int *)(new_list->content));
	printf("Second new node content: %d (Expected: 4)\n", *(int *)(new_list->next->content));
	ft_lstclear(&new_list, del_content);
	free(node1->content);
	free(node1);
	free(node2->content);
	free(node2);
}

int	main(void)
{
	printf("##############################TEST PART1##############################\n");
	test_ft_atoi();
	test_ft_bzero();
	test_ft_calloc();
	test_ft_isalnum();
	test_ft_isalpha();
	test_ft_isascii();
	test_ft_isdigit();
	test_ft_isprint();
	test_ft_memchr();
	test_ft_memcmp();
	test_ft_memcpy();
	test_ft_memmove();
	test_ft_memset();
	test_ft_strchr();
	test_ft_strdup();
	test_ft_strlcat();
	test_ft_strlcpy();
	test_ft_strlen();
	test_ft_strncmp();
	test_ft_strnstr();
	test_ft_strrchr();
	test_ft_tolower();
	test_ft_toupper();
	printf("\n##############################TEST PART2##############################\n");
	test_ft_substr();
	test_ft_strjoin();
	test_ft_strtrim();
	test_ft_split();
	test_ft_itoa();
	test_ft_strmapi();
	test_ft_striteri();
	test_ft_putchar_fd();
	test_ft_putstr_fd();
	test_ft_putendl_fd();
	test_ft_putnbr_fd();
	printf("\n##############################TEST BONUS##############################\n");
	test_ft_lstnew();
	test_ft_lstadd_front();
	test_ft_lstsize();
	test_ft_lstlast();
	test_ft_lstadd_back();
	test_ft_lstdelone();
	test_ft_lstclear();
	test_ft_lstiter();
	test_ft_lstmap();
	return (0);
}
