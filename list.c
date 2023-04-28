/*
 * File: list.c
 * Auth: Oluwatobiloba Light
 *       Princewill Chimdi Samuel
 */

#include "shell.h"

/**
 * shelly_add_alias_end - Adds a node to the end of a sh_alias_t linked list.
 *
 * @head: A pointer to the head of the sh_alias_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: On success, a pointer to the new node. On failure, NULL.
 */
sh_alias_t *shelly_add_alias_end(sh_alias_t **head, char *name, char *value)
{
	sh_alias_t *new_node, *last;

	new_node = malloc(sizeof(sh_alias_t));
	if (!new_node)
		return (NULL);

	new_node->name = malloc((shelly_strlen(name) + 1) * sizeof(char));
	if (!new_node->name)
	{
		free(new_node);
		return (NULL);
	}

	new_node->val = value;
	shelly_strcpy(new_node->name, name);
	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;

		last->next = new_node;
	}
	return (new_node);
}

/**
 * shelly_add_node_end - Adds a node to the end
 *                       of a sh_singly_list_t linked list.
 *
 * @head: A pointer to the head of the sh_singly_list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL. Otherwise - a pointer to the new node.
 */
sh_singly_list_t *shelly_add_node_end(sh_singly_list_t **head, char *dir)
{
	sh_singly_list_t *new_node, *last;

	new_node = malloc(sizeof(sh_singly_list_t));
	if (new_node == NULL)
		return (NULL);

	new_node->dir = dir;
	new_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * shelly_free_alias_list - Frees a sh_alias_t linked list.
 * @head: THe head of the sh_alias_t list.
 *
 * Return: nothing
 */
void shelly_free_alias_list(sh_alias_t *head)
{
	sh_alias_t *next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->val);
		free(head);
		head = next;
	}
}

/**
 * shelly_free_list - Frees a shelly_list_t linked list.
 * @head: The head of the list_t list.
 */
void shelly_free_list(sh_singly_list_t *head)
{
	sh_singly_list_t *next;

	while (head)
	{
		next = head->next;
		free(head->dir);
		free(head);
		head = next;
	}
}
