#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define STACK_INIT_SIZE 100    /*�洢�ռ��ʼ������*/
#define STACKINCREMENT 10    /*�洢�ռ��������*/

typedef struct {    /*�˿ͽṹ��*/
	char name[100];
	int id;
	int seat;
	char sex[50];
	char goal[20];
	char type;
}Customer;

typedef struct {    /*���˿͹滮Ϊջ*/
	Customer *top;
	Customer *base;
	int stacksize;
}Stack;

typedef struct {    /*�ɻ��ṹ��*/
	int number;
	int input;
    Stack data;
}Plane;

typedef struct {    /*���ɻ��滮Ϊ����*/
    Plane data;
    struct Node *next;
}Node;

int temp1 = 0;    /*�ڵ������*/

int createPlane(Node *L) {    /*�����ɻ�����*/
    int x, y;
    do {
        printf("������ɻ����(0ʱ����)��\n");
        scanf("%d", &x);
        printf("������ǻ��ڣ�\n");
        scanf("%d", &y);
        if (x != 0) {
            Node *q;    /*�����½ڵ�*/
            q = (Node*)malloc(sizeof(Node));
            temp1++;
            q -> data.number = x;
            q -> data.input = y;
            L -> next = q;
            L = q;
        }
    }while(x != 0);    /*�ɻ����Ϊ0ʱ����*/
    return 1;
}

int deleteNode(Node *L) {    /*ɾ���ɻ��ڵ�*/
    int num;
    Node *q;
    q = L;
    q = q -> next;
    printf("������Ҫɾ���ķɻ���ţ�����÷ɻ��µĳ˿�ȫ��ɾ��������\n");
    scanf("%d", &num);
    while(q != NULL) {
        Node *r = q;
        if (r.data.number == num) {
            q -> next = r -> next;
            return 1;
        } else {
            q = q -> next;
        }
    }
    printf("δ�ҵ��÷ɻ���");
    return 0;
}

int initStack (Stack *S) {   /*����һ���˿Ϳ�ջ*/
    S -> base = (Customer*)malloc(STACK_INIT_SIZE*sizeof(Customer));
    S -> top = S -> base;
    S -> stacksize = STACK_INIT_SIZE;
    return 1;
}

int createCustomer(Stack *S) {    /*����ṹ��e���¹˿�Ϊ�µ�ջ��Ԫ��*/
    Customer e;
    if (S -> top - S -> base >= S -> stacksize) {
        S -> base = (Customer*)realloc(S -> base, (S -> stacksize + STACKINCREMENT)*sizeof(Customer));
        if (!S -> base) {    /*ջ���*/
            return -1;
        }
        S -> top = S -> base + S -> stacksize;
        S -> stacksize += STACKINCREMENT;
    }
    printf("������˿����ʶ��ţ�\n");
    scanf("%d", &e.id);
    printf("������˿�������\n");
    scanf("%s", &e.name);
    printf("��������λ�ţ�\n");
    scanf("%d", &e.seat);
    printf("������˿��Ա�\n");
    scanf("%s", &e.sex);
    printf("������Ŀ�ĵأ�\n");
    scanf("%s", &e.goal);
    printf("�������λ����: \n");
    scanf("%s", &e.type);
    *(S -> top) = e;    /*�ȸ�ֵ�ڽ�ָ���1*/
    S -> top ++;
    return 1;
}

int Push (Stack *S, Customer e) {    /*����ṹ��eΪ�µ�ջ��Ԫ��*/
    if (S -> top - S -> base >= S -> stacksize) {
        S -> base = (char*)realloc(S -> base, (S -> stacksize + STACKINCREMENT)*sizeof(char));
        if (!S -> base) {    /*ջ���*/
            return -1;
        }
        S -> top = S -> base + S -> stacksize;
        S -> stacksize += STACKINCREMENT;
    }
    *(S -> top) = e;    /*�ȸ�ֵ�ڽ�ָ���1*/
    S -> top ++;
    return 1;
}

int Pop (Stack *S, Customer *e) {    /*��ջ*/
    if (S -> top == S -> base) {    /*ջ��*/
            return 0;
    } else {
        S -> top --;    /*�Ƚ�ָ���1�ڳ�ջ*/
        *e = *(S -> top);
    }
    return 1;
}

int searchCustomer(Node *L) {    /*��Ѱ�˿�*/
    int x, y;
    char s;
    Node *q;
    q = L;
    q = q -> next;
    printf("������˿����ڷɻ��ţ�\n");
    scanf("%d", &x);
    printf("������˿����ʶ��ţ�\n");
    scanf("%d", &y);
    while(q != NULL) {
        Node *r = q;
        if (r.data.number == x) {
            q = r;
            break;
        } else {
            q = q -> next;
        }
    }
    if (q == NULL) {
        printf("δ�ҵ��÷ɻ�\n");
        return 0;
    }
    while (q.data.data.top != --q.data.data.base) {
        Customer temp = q.data.data.top;
        if (temp.top.id == y) {
            system("cls");
            printf("�ҵ��˿ͣ���ӡ�����ݣ�\n");
            printf("�˿�������%s\n", temp.name);
            printf("�˿����ʶ��ţ�%d\n", temp.id);
            printf("�˿���λ�ţ�%d\n", temp.seat);
            printf("�˿�Ŀ�ĵ�: %s\n", temp.goal);
            printf("��λ���ࣺ%s\n", temp.type);
            break;
       }
       else {
       temp--;
       }
       if (temp < q.data.data.base) {
        printf("δ�ҵ��ó˿ͣ�����")
        return 0;
       }
    }
    printf("�Ƿ�ص���ҳ��y/n��");
    scanf("%s", &s);
    if (s == 'y') {
        return 1;
    }
}

int reserve(Node *L) {
    Node *q = L;
    q = q -> next;
    FILE *fp = NULL;
    int i;
    if ((fp = fopen("Customer.txt", "w")) == NULL) {
        printf("���ܴ��ļ���");
        return 0;
    }
    fprintf(fp, "%d\n", temp1);
    while (i = 0; i < temp1; i++) {
        Customer m = q.data.data.top;
        while (m >= q.data.data.base) {
            fprintf(fp,"%s %d %d %s %s %s\n", m.name, m.id, m.seat, m.sex, m.goal,
                 m.type);
            m--;
        }
        fprintf(fp,"%d %d\n", q.data.number, q.data.number);
        q = q-> next;
    }
    fclose(fp);
    return 1;
}

int read(Node *L) {
    FILE *fp = NULL;
    int i = 0;
    Node *q;
    if ((fp = fopen("Customer.txt", "r")) == NULL) {
        printf("���ܴ��ļ���");
        return 0;
    }
    fscanf(fp, "%d\n", &temp1);
    while(i = 0; i < temp1; i++) {
        q = (Node*)malloc(sizeof(Node));
        Customer m = q.data.data.top;
        while (m != NULL) {
            fscanf(fp,"%s %d %d %s %s %s\n", &m.name, &m.id, &m.seat, &m.sex, &m.goal,
                 &m.type);
            printf("%s %d %d %s %s %s\n", m.name, m.id, m.seat, m.sex, m.goal,
                 m.type);
            m++;
            }
        }
        fscanf(fp,"%d %d\n", &q.data.number, &q.data.number);
        fprintf(fp,"%d %d\n", q.data.number, q.data.number);
        L -> next = q;
        L = q;
    }
    fclose(fp);
    return 1;
}

int main() {
    Node *L;
    int ch:
    while (1) {
        system("cls");
        printf("--------�ɻ�ƱԤ��ϵͳ--------\n");
        printf("        1.��������\n");
        printf("        2.�����˿�\n");
        printf("        3.��ѯ������Ϣ\n");
        printf("        4.��ѯ�˿���Ϣ\n");
        printf("        5.������Ϣ\n");
        printf("        6.��ȡ��Ϣ\n");
        printf("        0.�˳�ϵͳ\n");
        printf("����������ѡ��:\n");
        scanf("%d", &ch);
        switch (ch) {
            case 1:createPlane(&L);break;
            case 2:createCustomer();break;
            case 3:searchCustomer();break;
            case 4:searchCustomer();break;
            case 5:reserve(&L);break;
            case 6:read();break;
            case 0:exit(0);
        }
    }
}
