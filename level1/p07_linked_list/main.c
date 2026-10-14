#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
}Node;

typedef struct LinkedList{
    struct Node *first;
}LinkedList;

typedef struct Result {
    int index;
    struct Node *node;
}Result;

static Node * create_node(int data, Node *next);
static Node * create_node(const int data, Node *next) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = next;
    return new_node;
}

static LinkedList * create_linked_list();
static LinkedList * create_linked_list() {
    LinkedList *list = malloc(sizeof(LinkedList));
    list->first = NULL;
    return list;
}

static int insert(LinkedList *list, int idx, int data);
static int insert(LinkedList *list, const int idx, const int data) {
    if (idx == 0) {
        list->first = create_node(data, list->first);
        return 0;
    }
    if (list->first == NULL) {
        return -1;
    }
    int current_idx = 1;
    Node * curr_node = list->first->next;
    Node * prev_node = list->first;

    while (1) {
        if (current_idx == idx) {
            Node * new_node = create_node(data, curr_node);
            prev_node->next = new_node;
            return 0;
        }
        prev_node = curr_node;
        if (curr_node == NULL) {
            return -1;
        }
        curr_node = curr_node->next;
        current_idx++;
    }
}

static Result * find_data(const Node *start_node, int start_idx, int data);
static Result * find_data(const Node *start_node, const int start_idx, const int data) {
    Result * result = malloc(sizeof(Result));
    Node * curr_node = (Node *) start_node;
    int curr_idx = start_idx;
    while (curr_node != NULL) {
        if (curr_node->data == data) {
            result->index = curr_idx;
            result->node = curr_node;
            return result;
        }
        curr_node = curr_node->next;
        curr_idx++;
    }
    result->index = -1;
    result->node = NULL;
    return result;
}


int main() {
    LinkedList * my_list = create_linked_list();
    insert(my_list, 0, 1);
    insert(my_list, 1, 2);
    insert(my_list, 2, 3);
    insert(my_list, 3, 4);
    insert(my_list, 4, 5);
    insert(my_list, 5, 6);
    insert(my_list, 6, 7);
    insert(my_list, 7, 8);
    insert(my_list, 8, 5);
    insert(my_list, 9, 6);
    printf("遍历链表:\n");
    const Node * current_node = my_list->first;
    while (current_node != NULL) {
        printf("%d\n", current_node->data);
        current_node = current_node->next;
    }
    printf("第一个值为5的节点索引:\n");
    const Result * result = find_data(my_list->first, 0, 5);
    printf("%d\n", result->index);
    printf("第二个值为5的节点索引:\n");
    Node * next_start = result->node->next;
    const Result * result2 = find_data(next_start, result->index+1, 5);
    printf("%d\n", result2->index);
    return 0;
}