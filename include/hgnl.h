/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hgnl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moutig <moutig-tan@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:26:13 by ele-lean          #+#    #+#             */
/*   Updated: 2026/02/11 17:07:04 by moutig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "hlist.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 4096
#endif

#define CONTENT(list) ((char *)(list->content))

typedef struct s_newline
{
	int	size;
	int	buffers;
}		t_newline;

/**
 * @brief Get the Next Line object
 * @param fd - The file descriptor to read from.
 * @return The next line read from the file descriptor, or NULL if there is an error or if the end of the file has been reached.
 */
char	*getNextLine(int fd);

/**
 * @brief Add a new node to the end of the list for the specified file descriptor.
 * @param list - The array of lists, where each index corresponds to a file descriptor.
 * @param buffer - The buffer containing the data to be added to the list.
 * @param fd - The file descriptor for which the buffer is being added.
 */
void	gnlLstaddBack(t_list **list, char *buffer, int fd);

/**
 * @brief Free the list for the specified file descriptor, optionally preserving a clean node.
 * @param list - The array of lists, where each index corresponds to a file descriptor.
 * @param clean_node - A node to preserve if it contains remaining data.
 * @param buf - A buffer associated with the clean node.
 */
void	freeGnlList(t_list **list, t_list *clean_node, char *buf);
