#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100    /*�������ڵ���Ϊ100*/

typedef int SqBiTree[MAX_TREE_SIZE];

typedef struct {
    char data;    /*��������*/
    struct btnode *lChild, *rChild;    /*�������Һ���ָ��*/
}BitNode, *BitTree;



int preOrder(BitNode *T) {    /*�ǵݹ��������*/
    BitTree stack[100];    /*����ջ���б���*/
    int top = 0, bottom = 0;
    BitNode *p;
    if(T != NULL) {
        stack[top] = T;    /*�����ڵ���ջ*/
        top = (top + 1) % 100;
    }
    while (bottom != top) {
        p = stack[bottom];
        printf("%d", p -> data);    /*����ڵ�*/
        bottom = (top + 1) % 100;
        if(p -> lChild != NULL) {    /*��������Ϊ�վ����������*/
            stack[top] = p -> lChild;    /*��������ջ*/
            top = (top + 1) % 100;
        }
        if(p-> rChild != NULL) {    /*�����������*/
            stack[top] = p -> rChild;    /*��������ջ*/
            top = (top + 1) % 100;
        }
    }
    return 1;
}
