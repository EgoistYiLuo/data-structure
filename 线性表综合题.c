#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define len 100

typedef struct {    /*˳���ڵ�*/
    int array[len];
    int length;
}List;

typedef struct {    /*����ڵ�*/
    int data;
    struct Node *next;
}Node;

int createList (List *L) {    /*����˳���*/
    if (L -> length != NULL) {
        printf("�ѽ���˳���!");
        return 0;
    }
    int i, num;
    printf("������˳����ȣ�");
    scanf("%d", &num);
    L -> length = num;    /*lengthָ�����Ա���*/
    printf("���������Ա�ڵ�����");
    for (i = 1; i <= num; i++) {
        scanf("%d", &L -> array[i]);
    }
    return 1;
}

int createNode (Node *L) {    /*��������*/
    if (L -> data != NULL) {
        printf("�ѽ�������");
        return 0;
    }
    Node *q;
    int m, n, i;    /*�ڵ����Ϊm���ڵ�����Ϊn*/
    printf("����������ڵ������");
    scanf("%d", &m);
    for (i = 0; i < m; i++) {
        q = (Node*)malloc(sizeof(Node));
        printf("������ڵ����ݣ�");
        scanf("%d", &n);
        q -> data = n;
        L -> next = q;
        L = q;
    }
    L -> next = NULL;    /*β��ʶΪNULL*/
    return 1;
}

int sortList(List *L) {
    int choose, M = 1, N = L -> length, i;
    int r[N+1], r2[N+1];    /*�����鲢������������*/
    for (i = 1; i <= N; i++) {
        r[i] = L -> array[i];
    }
    system("CLS");
    printf("1.ֱ�Ӳ�������\n");
    printf("2.ð������\n");
    printf("3.ֱ��ѡ������\n");
    printf("4.��������\n");
    printf("5.�鲢����\n");
    printf("��������ѡ��:");
    scanf("%d", &choose);
    switch(choose) {
        case 1:insertSort(L);break;
        case 2:bubbleSort(L);break;
        case 3:selectionSort(L);break;
        case 4:quickSort(L, M, N);break;
        case 5:mergeSort(r, r2, M, N);
               for (i = 1; i < N; i++) {
                    L -> array[i] = r [i];
               }break;
    }
    return 1;
}

int insertSort(List *L) {    /*ֱ�Ӳ�������*/
    int i, j;
    for (i = 2; i <= L -> length; i++) {
        if (L -> array[i] < L -> array[i-1]) {    /*��L->array[i]���뵽�����ӱ�*/
            L -> array[0] = L -> array[i];    /*����Ϊ�ڱ�*/
            L -> array[i] = L -> array[i-1];
            for (j = i - 1; L -> array[0] < L -> array[j]; j--) {
                L -> array[j+1] = L -> array[j];    /*��¼����*/
            }
            L -> array[j+1] = L-> array[0];    /*���뵽��ȷλ��*/
        }
    }
    return 1;
}

int bubbleSort(List* L) {    /*ð������*/
    int i, j, temp;
    for (i = 1; i < L -> length; i++) {
        for (j = i; j < L-> length; j++) {
            if (L -> array[j] > L -> array[j+1]) {
                temp = L -> array[j+1];
                L -> array[j+1] = L -> array[j];
                L -> array[j] = temp;
            }
        }
    }
    return 1;
}

int selectionSort(List *L) {    /*ֱ��ѡ������*/
    int i, j, temp, m;
    for (i = 1; i < L -> length; i++) {
        m = i;
        for (j = i; j < L -> length; j++) {    /*�ҵ���С������*/
            if(L -> array[j] < L -> array[m]) {
                m=j;
            }
        if (i != m) {
            temp = L -> array[i];
            L -> array[i] = L -> array[m];
            L -> array[m] = temp;
            }
        }
    }
}

int quickSort(List *L ,int M ,int N) {    /*��������*/
    int i, j, x;
    i = M, j = N;
    x = L -> array[i];
    do {
        while ((L -> array[j] >= x) && (j > i)) {
            j--;
        }
            if (i < j) {
                L -> array[i] = L -> array [j];
                i++;
                while (L -> array[j] <= x && (i < j)) {
                    i++;
                }
                if (i < j) {
                    L -> array[j] = L -> array [i];
                    j--;
                }
            }
    }while (i != j);
    L -> array[i] = x;
    i++;
    j--;
    if (M < j) {
        quickSort(L ,M ,j);
    }
    if (i < N) {
        quickSort(L, i, N);
    }
}
int merge(int r[], int r2[], int S, int M, int N) {
    int i,k,j;
    i = S, k = S, j = M + 1;    /*��S��ʼ*/
    while ((i <= M) && (j <= N)) {    /*��������������δ����ʱ*/
        if (r[i] <= r[j]) {
            r2[k] = r[i];
            i++;
        } else {
            r2[k] = r [j];
            j++;
        }
        k++;
    }
    while (i <= M + 1) {    /*��ʣ�µ�ȫ������*/
        r2[k++] = r[i++];
    }
    while (j <= N + 1) {
        r2[k++] = r[j++];
    }
    for (i = S; i <= N; i++) {
        r[i] = r2[i];
    }
}
int mergeSort(int r[], int r2[], int S, int N) {    /*�鲢����*/
    int M;
    if (S < N) {
        M = (S + N)/2;
        mergeSort(r, r2, S, M);
        mergeSort(r, r2, M + 1, N);
        merge(r, r2, S, M, N);
    }
}

int printList(List *L) {    /*��ӡ˳���*/
    int i;
    for (i = 1; i < L -> length; i++) {   /*��ӡ������*/
    printf("%d ", L -> array[i]);
    }
    return 1;
}

int sortNode(Node *L) {    /*������ڵ�������򣬽���������*/
    int i, j, tempData;
    Node *head, *point;    /*����ָ��point����ָ��head����һ���ڵ�*/
    head = L;
    head = head -> next;
    int length = 0;
    while (head -> next != NULL) {    /*����������*/
        head = head -> next;
        length++;
    }
    for (i = 0; i < length; i++) {    /*ð������*/
        head = L;    /*��head��λ*/
        head = head -> next;
        for(j = i; j < length; j++) {
            point = head -> next;
            if(head -> data >= point -> data) {
                tempData = head -> data;
                head -> data = point -> data;
                point -> data = tempData;
            }
            head = head -> next;
        }
    }
    head = L;    /*ָ��ص���ͷ*/
    head = head -> next;
    while (head != NULL) {    /*�����������Ա���ʾ����*/
        printf("%d ", head -> data);
        head = head -> next;
    }
    return 1;
}

int combine(List *L1, Node *L2) {    /*������ű�*/
    int r[10000], i = 1, point = 0;
    Node *head;
    head = L2;
    head = head -> next;
    while((head != NULL) && (i <= L1 -> length)) {
        if (head -> data <= L1 -> array[i]) {
            r[point] = head -> data;
            point++;
            head = head -> next;
        } else {
            r[point] = L1 -> array[i];
            point++;
            i++;
        }
    }
    while (head != NULL) {    /*��ʣ��Ԫ��ȫ����������*/
        r[point] = head -> data;
        point++;
        head = head -> next;
    }
    while (i <= L1 -> length) {
        r[point] = L1 -> array[i];
        point++;
        i++;
    }
    for (i = 0; i < point; i++) {    /*���Ԫ��*/
        printf("%d ", r[i]);
    }
    return 1;
}

int main() {
    int choose;
    List *L1;
    Node *L2;
    while(1) {
        system("CLS");
        printf("1.����˳���\n");
        printf("2.����\n");
        printf("3.��������\n");
        printf("4.��������\n");
        printf("5.�ϲ�˳���������\n");
        printf("0.�˳�\n");
        printf("��������ѡ��:");
        scanf("%d", &choose);
        switch(choose) {
            case 1:createList(&L1);printList(&L1);break;
            case 2:sortList(&L1);printList(&L1);break;
            case 3:createNode(&L2);break;
            case 4:sortNode(&L2);break;
            case 5:combine(&L1, &L2);break;
            case 0:exit(0);
        }
    }
}
