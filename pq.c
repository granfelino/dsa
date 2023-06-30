#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int          key;
    float        value; 
    struct Node  *next;
    struct Node  *prev;
} Node;


typedef struct PQ {
    Node *head;
    Node *tail;
} PQ;

/* PRIVATE FUNCTIONS */
Node*   _Node_malloc();
Node*   _Node_malloc_kv(int k, float v);
Node*   _PQ_find_prev(PQ *pq, Node *node);
Node*   _PQ_search_dupl(PQ *pq, int k);
void    _PQ_update(PQ *pq, Node *dupl, int k, float v);

/* PUBLIC FUNCTIONS */
PQ*     pq();
void    pq_push(PQ *pq, int k, float v);
Node*   pq_pop(PQ *pq);
void    pq_free(PQ *pq);
void    pq_print(PQ *pq);
int     pq_isempty(PQ *pq);


Node* _Node_malloc() {
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        printf("<PQ> Failed to allocate memory for a Node. Exiting...\n");
        exit(1);
    }
    node->next = NULL;
    node->prev = NULL;

    return node;
}


Node* _Node_malloc_kv(int k, float v) {
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        printf("<PQ> Failed to allocate memory for a Node. Exiting...\n");
        exit(1);
    }
    node->next  = NULL;
    node->prev  = NULL;
    node->key   = k;
    node->value = v;

    return node;
}


PQ* pq() {
    PQ *pq = (PQ*) malloc(sizeof(PQ));
    if (pq == NULL) {
        printf("<PQ> Failed to allocate memory for PQ. Exiting...\n");
        exit(1);
    }
    pq->head = NULL;
    pq->tail = NULL;
    return pq;
}


Node* _PQ_find_prev(PQ *pq, Node *node) {
    Node *current_node = pq->head;
    while (current_node != NULL) {
        if (current_node->value > node->value) {
            return current_node->prev;
        }
        current_node = current_node->next;
    }
    return pq->tail;
}


Node* _PQ_search_dupl(PQ *pq, int k) {
    Node *current_node = pq->head;
    while (current_node != NULL) {
        if (current_node->key == k) {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}


void _PQ_update(PQ *pq, Node *dupl, int k, float v) {
    if (dupl == pq->head && dupl == pq->tail) {
        Node *new_node = _Node_malloc_kv(k, v);
        free(dupl);
        pq->head = new_node;
        pq->tail = new_node;
    } else if (dupl == pq->head) {
        Node *new_node = _Node_malloc_kv(k, v);
        new_node->next = pq->head->next;
        pq->head->next->prev = new_node;
        free(pq->head);
        pq->head = new_node;
    } else if (dupl == pq->tail) {
        Node *temp = pq->tail;
        temp->prev->next = NULL;
        pq->tail = temp->prev;
        free(temp);
        pq_push(pq, k, v);
    } else {
        dupl->prev->next = dupl->next;
        dupl->next->prev = dupl->prev;
        free(dupl);
        pq_push(pq, k, v);
    }
}


void pq_push(PQ *pq, int k, float v) {
    if (pq == NULL) {
        printf("<PQ> PQ is NULL. Cannot append. Exiting...\n");
        exit(1);
    }

    Node *dupl = _PQ_search_dupl(pq, k);
    if (dupl != NULL) {
        _PQ_update(pq, dupl, k, v);
        return;
    }

    if (pq->head == NULL && pq->tail == NULL) {
        Node *node = _Node_malloc_kv(k, v);
        pq->head = node;
        pq->tail = node;
    } else if (pq->head && pq->tail) {
        Node *node = _Node_malloc_kv(k, v);
        Node *node_prev = _PQ_find_prev(pq, node);
        if (node_prev == pq->tail) {
            node->prev = node_prev;
            pq->tail->next = node;
            pq->tail = node;
        } else if (node_prev == NULL) {
            node->prev = NULL;
            node->next = pq->head;
            pq->head->prev = node;
            pq->head = node;
        } else if (node_prev != NULL) {
            node->prev = node_prev;
            node->next = node_prev->next;
            node_prev->next->prev = node;
            node_prev->next = node;
        } else {
            printf("<PQ> Previous node cannot be NULL. Exiting...\n");
            exit(1);
        }
    } else {
        printf("<PQ> Head or tail of PQ missing. Exiting...\n");
        exit(1);
    }
}


Node* pq_pop(PQ *pq) {
    Node *popped = pq->head;
    pq->head->next->prev = NULL;
    pq->head = pq->head->next;
    popped->next = NULL;
    popped->prev = NULL;
    return popped;
}


void pq_free(PQ *pq) {
    Node *current_node = pq->head;
    while (current_node != NULL) {
        Node *temp = current_node;
        current_node = current_node->next;
        free(temp);
    }
    free(pq);
}


void pq_print(PQ *pq) {
    Node *current_node = pq->head;
    while (current_node != NULL) {
        printf("K:%d V: %f\n", current_node->key, current_node->value);
        current_node = current_node->next;
    }
}


int pq_isempty(PQ *pq) {
    if (pq->head == NULL && pq->tail == NULL) {
        return 1;
    } else if (pq->head && pq->tail) {
        return 0;
    } else {
        printf("<pq_isempty> Tail or head NULL, but not both. Exiting...\n");
        exit(1);
    }
}


int main() {
    PQ *queue = pq();
    printf("Is the queue empty? %d.\n", pq_isempty(queue));
    pq_push(queue, 1, 15.1);
    pq_push(queue, 2, 14.1);
    pq_push(queue, 3, 13.1);
    pq_push(queue, 4, 12.1);
    pq_push(queue, 5, 11.1);

    printf("Is the queue empty? %d.\n", pq_isempty(queue));
    pq_print(queue);
    printf("\n");

    pq_push(queue, 5, 1.1);
    pq_print(queue);
    printf("\n");
    
    pq_push(queue, 3, 0.1);
    pq_print(queue);
    printf("\n");

    pq_push(queue, 1, 0.01);
    pq_print(queue);
    printf("\n");
    printf("Is the queue empty? %d.\n", pq_isempty(queue));

    pq_free(queue);
    return 0;
}
