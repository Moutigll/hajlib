#ifndef HAJLIB_LIST_H
#define HAJLIB_LIST_H

#include <stdlib.h>

/**
 * @brief Represent a node in a singly linked list.
 *	Each node contains a pointer to its content and a pointer to the next node in the list.
 */
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief Free the memory allocated for a linked list and all its nodes.
 * @param list - The head of the list to free.
 */
void	free_list(t_list *list);

/**
 * @brief Add a node to the end of a linked list.
 * @param lst - The address of a pointer to the first node of a list.
 * @param newNode - The node to add to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *newNode);

/**
 * @brief Add a node to the front of a linked list.
 * @param lst - The address of a pointer to the first node of a list.
 * @param newNode - The node to add to the front of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *newNode);

/**
 * @brief Clear a linked list and free the memory allocated for all its nodes and their content.
 * @param lst - The address of a pointer to the first node of a list.
 * @param del - A function pointer to a function that takes a void pointer and frees the memory allocated for it.
 */
void	ft_lstclear(t_list **lst, void (*del)(void*));

/**
 * @brief Free the memory allocated for a single node and its content.
 * @param lst - The node to free.
 * @param del - A function pointer to a function that takes a void pointer and frees the memory allocated for it.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Get the node at a specific index in a linked list.
 * @param list - The head of the list.
 * @param index - The index of the node to retrieve.
 * @return t_list* - The node at the specified index, or NULL if the index is out of bounds.
 */
t_list	*ft_lstget(t_list *list, int index);

/**
 * @brief Insert a new node after a given node in a linked list.
 * @param current - The node after which the new node will be inserted.
 * @param new_node - The new node to insert.
 */
void	ft_lstinsert_after(t_list *current, t_list *new_node);

/**
 * @brief Iterate over a linked list and apply a function to each node's content.
 * @param lst - The head of the list.
 * @param f - A function pointer to a function that takes a void pointer and performs an operation on it.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Get the last node in a linked list.
 * @param lst - The head of the list.
 * @return t_list* - The last node in the list.
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Create a new linked list by applying a function to each node's content.
 * @param lst - The head of the list.
 * @param f - A function pointer to a function that takes a void pointer and returns a new void pointer.
 * @param del - A function pointer to a function that takes a void pointer and frees the memory allocated for it.
 * @return t_list* - The head of the new list.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**
 * @brief Create a new node with the given content.
 * @param content - The content for the new node.
 * @return t_list* - The new node.
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Get the size of a linked list.
 * @param lst - The head of the list.
 * @return int - The number of nodes in the list.
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Remove a node from a linked list and free the memory allocated for it and its content.
 * @param head - The address of a pointer to the first node of the list.
 * @param to_remove - The content of the node to remove.
 * @param del - A function pointer to a function that takes a void pointer and frees the memory allocated for it.
 */
void	ft_removenode(t_list **head, void *to_remove, void (*del)(void *));

#endif
