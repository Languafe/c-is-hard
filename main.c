#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_LENGTH 256

struct node;

struct node
{
    void *value;
    struct node *next;
};

struct list;

struct list
{
    int size;
    struct node *head;
};

struct list *list_create()
{
    struct list *new_list = malloc(sizeof(struct list));
    return new_list;
}

void list_destroy(struct list *l)
{
    struct node *temp, *current = l->head;
    while (current != NULL)
    {
       temp = current;
       current = current->next;
       free (temp); 
    }
    free(l);
}

struct node *node_create(int value)
{
    struct node *new_node = malloc(sizeof(struct node));
    new_node->value = malloc(sizeof(int));
    *((int*)new_node->value) = value;
    new_node->next = NULL;
    return new_node;
}

void list_add(struct list *l, struct node *n)
{
    int index = 0;
    if (l->head == NULL) {
        l->head = n;
    }
    else {
        struct node *cursor = l->head;
        while (cursor->next != NULL) {
            cursor = cursor->next;
        }
        cursor->next = n;
    }
}

void print_list(struct list *l)
{
    int index = 0;
    struct node *cursor = l->head;
    while (cursor != NULL) {
        printf("%2d: %d\n", index++, *((int*)cursor->value));
        cursor = cursor->next;
    }
}

void print_list_sum(struct list *l)
{
    int sum = 0;
    struct node *cursor = l->head;
    while (cursor != NULL) {
        sum += *((int*)cursor->value);
        cursor = cursor->next;
    }
    printf("Sum of all values: %d\n", sum);
}

void print_usage()
{
    printf("cg - Categorical CLI\n");
    printf("help - show available commands\n");
    printf("quit - exit\n");
}

int get_cmd(char *cmd)
{
    fgets(cmd, CMD_LENGTH, stdin);
}

int main(int argc, char *argv[])
{
    char* cmd = malloc(CMD_LENGTH);
    struct list *values = list_create();
    while (1)
    {
        printf("Type a number (or 'quit' to finish): ");
        get_cmd(cmd);
        if (strcmp("quit\n", cmd) == 0)
            break;
        list_add(values, node_create(atoi(cmd)));
    }
    print_list(values);
    print_list_sum(values);
    list_destroy(values);
    free(cmd);
}

