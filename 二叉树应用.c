#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_TREE_SIZE 100    /*�������ڵ���Ϊ100*/

typedef int SqBiTree[MAX_TREE_SIZE];    /*������ڵ�*/

typedef struct {
    int data;    /*��������*/
    struct btnode *lChild, *rChild;    /*�������Һ���ָ��*/
}BitNode, *BitTree;

int createTree(BitNode *T) {    /*����������*/
    int ch;
    printf("������ڵ�����,0��ʾ����:");
    scanf("%d", &ch);
    if (ch == 0) {    /*0��ʾ����*/
        T = NULL;
    } else {
        T = (BitNode*)malloc(sizeof(BitNode));
        if (!T) {
            exit(-1);
        }
        T -> data = ch;    /*���ɸ��ڵ�*/
        createTree(T -> lChild);    /*����������*/
        createTree(T -> rChild);    /*����������*/
    }
    return 1;
}

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

int inOrder(BitNode* T) {    /*�ǵݹ��������*/
    BitTree stack[100];    /*����ջ���б���*/
    int top = 0;
    BitNode *p;
    p = T;
    while(p != NULL || top > 0) {
        while(p != NULL) {    /*����������˵Ľڵ�*/
            stack[top++] = p;
            p = p -> lChild;
        }
        if(top > 0) {    /*��ջ��ѡ��ǰ�ڵ��������*/
            p = stack[--top];
            printf("%d", p -> data);
            p = p -> rChild;
        }
    }
    return 1;
}

int levelPrint(BitNode *T){    /*�ǵݹ��α���*/
    BitTree queue[100];
    BitNode *p;
    int front = -1, rear = 0;
    queue[rear] = T;
    while(front != rear) {
        p = queue[front];
        front = (front + 1) % 10000;
        printf("%d", p -> data);
        if(p -> lChild != NULL) {
            queue[rear] = p -> lChild;
            rear = (rear + 1) % 10000;
        }
        if(p -> rChild != NULL) {
            queue[rear] = p -> rChild;
            rear = (rear + 1) % 10000;
        }
    }
    return 1;
}

int judgePrint(BitNode *T) {    /*�ж��Ƿ�Ϊ����������*/
    if(!T) {    /*����1�����Ƕ���������*/
        return 1;
    }
    else if(!(T -> lChild)&&!(T -> rChild)) {     /*����������û��*/
        return 1;    /*����1�����Ƕ���������*/
    }
    else if((T->lChild)&&!(T->rChild)) {   /*ֻ��������*/
        if(((T -> lChild) -> data)>(T -> data)) {
            return 0;    /*����0�����޶�����*/
        } else {
            return (judgePrint(T -> lChild));   /*����Ѱ���ӽڵ�*/
        }

    }
    else if (!(T -> lChild)&&(T -> rChild)) {   /*ֻ��������*/
        if(((T -> rChild) -> data) < (T -> data)) {
            return 0;
        } else {
            return (judgePrint(T -> rChild));
        }
    }
    else {    /*�����������������*/
        if((T -> lChild -> data) > (T -> data) || (T -> rChild -> data) < (T -> data)) {
            return 0;
        }
        else {
        return (judgePrint(T -> lChild) && judgePrint(T -> rChild));
        }
    }
}

int insertBst(BitNode *T, int key) { /*��������������*/
    BitTree P, N;
    if(searchBst(T, NULL, key, &p)) {    /*�����ʺ�λ�ò���*/
        return 0;
    } else {
        N = (BitNode*)malloc(sizeof(BitNode));    /*�����½ڵ�*/
        N -> data = key;
        N -> lChild = NULL;
        N -> rChild = NULL;
        if(!P) {    /*�жϲ���*/
            T = N;
        } else if(key < P -> data) {
            P -> lChild = N;
        }
        else {
            P -> rChild = N;
        }
    }
    return 1;
}

int searchBst(BitNode *T, BitNode *U int key, BitNode *P) {    /*���ҽڵ�*/

    if(!T) {    /*�ж�ԭ���Ƿ����*/
        P = NULL;
        return 0;
    } else if(key == T -> data) {
        P = T;
        return 1;
    }
    else if(key < T -> data) {
        return searchBst(T -> lchild, T, key, P);
    }
    else {
        return searchBst(T->rChild, T, key, P);
    }
    return 1;
}

int deleteBst(BitNode *T, int key) {    /*����������ɾ��*/
    if(!T) {
        return 0;
    }
    else {
        if(key == T -> data) {    /*�ҵ�ָ���ڵ㣬ɾ��*/
            delete(T);
        }
        else if(key < T -> data) {
            return deleteBst(&T -> lChild, key);
        } else {
            return deleteBst(&T -> rChild, key);
        }
    }
    return 1;
}

int delete(BitNode *P) {    /*ɾ���ڵ�*/

    BitNode *N, *Q;
    if(!(P -> lChild) && !(P -> rChild)) {
         P = NULL;
    }

    else if(!(p->lchild)) {
        Q = P;
        free(Q);
    }
    else if(!(p -> rChild)) {
        Q = p;
        free(Q);
    }
    else {
        Q = P;
        N = P -> lChild;
        while(N -> rChild) {
            Q = N;
            N = N -> rChild;
        }
        P -> data = N -> data;
        if(Q != P) {
            Q -> rChild = N -> rChild;
        }
        else {
            Q -> lChild = N -> lChild;
        }
        free(N);
    }
    return 1;
}

int main() {
    int ch = 0,flag = 0, key;
    BitNode *T;
    while(1)
    {
        printf("1.����������\n");
        printf("2.����ǵݹ����\n");
        printf("3.����ǵݹ����\n");
        printf("4.��ηǵݹ����\n");
        printf("5.�ж϶������Ƿ�Ϊ����������\n");
        printf("6.������������������\n");
        printf("7.����������ɾ������\n");
        printf("0.�˳�\n");
        printf("��������ѡ��");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:createTree(&T);break;
            case 2:printf("�ǵݹ��������Ϊ��\n");
                   preOrder(&T);
                   printf("\n");break;
            case 3:printf("�ǵݹ��������Ϊ��\n");
                   inOrder(&T);
                   printf("\n");break;
            case 4:printf("�ǵݹ��α���Ϊ��\n");
                   levelPrint(&T);
                   printf("\n");break;
            case 5:flag = judgePrint(&T);
                   if(flag) {
                       printf("�����Ƕ���������\n");
                   }
                   else {
                       printf("�������Ƕ���������\n");
                   }
                   printf("\n");break;
            case 6:printf("���������ݣ�");
                   scanf("%d", &key);
                   insertBst(&T, key);break;
            case 7:printf("���������ݣ�");
                   scanf("%d", &key);
                   deleteBst(&T, key);break;
            case 0:exit(0);
        }
        printf("\n");
    }
}
