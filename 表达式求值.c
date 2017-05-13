#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define STACK_INIT_SIZE 100    /*�洢�ռ��ʼ������*/
#define STACKINCREMENT 10    /*�洢�ռ��������*/

typedef struct {
  char *top;
  char *base;
  int stacksize;
}SqStack;

int InitStack (SqStack *S) {   /*����һ����ջ*/
    S -> base = (char*)malloc(STACK_INIT_SIZE*sizeof(char));
    S -> top = S -> base;
    S -> stacksize = STACK_INIT_SIZE;
    return 1;
}

int Push (SqStack *S, char e) {    /*����Ԫ��eΪ�µ�ջ��Ԫ��*/
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

int Pop (SqStack *S, char *e) {    /*��ջ*/
    if (S -> top == S -> base) {    /*ջ��*/
            return 0;
    } else {
        S -> top --;    /*�Ƚ�ָ���1�ڳ�ջ*/
        *e = *(S -> top);
    }
    return 1;
}

char Precede(char a, char b) {    /*�Ƚ���������������ȼ�,a��b�д�Ŵ��Ƚϵ������,
                                   '>'��ʾa>b,'0'��ʾ�����ܳ��ֵıȽ� */
    int i,j;
    char pre[][7]={    /*�����֮������ȼ�������һ�ű��*/
        {'>','>','<','<','<','>','>'},
        {'>','>','<','<','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'>','>','>','>','<','>','>'},
        {'<','<','<','<','<','=','0'},
        {'>','>','>','>','0','>','>'},
        {'<','<','<','<','<','0','='}};
    switch(a) {
        case '+': i=0; break;
        case '-': i=1; break;
        case '*': i=2; break;
        case '/': i=3; break;
        case '(': i=4; break;
        case ')': i=5; break;
        case '#': i=6; break;
    }
    switch(b) {
        case '+': j=0; break;
        case '-': j=1; break;
        case '*': j=2; break;
        case '/': j=3; break;
        case '(': j=4; break;
        case ')': j=5; break;
        case '#': j=6; break;
    }
    return pre[i][j];
}

int InN(char c�� char op[]) {    /*�ж������ĳ���ַ��Ƿ��������*/
    char *p;
    p = op;
    while(*p != '\0'){
        if(c == *p)
            return 1;
        p++;
    }
    return 0;
}

int Operate(int a, char y, int b) {
    int i, j, result;
    i = a;
    j = b;
    switch(y) {
        case '+': result = i + j; break;
        case '-': result = i - j; break;
        case '*': result = i * j; break;
        case '/': result = i / j; break;
    }
    return result;
}

int getNext(int *n) {
    char c;
    *n = 0;
    while((c = getchar()) == ' ');  /*����һ�������ո�*/
    if(!InN(c)) {            /*ͨ�������ж�����ַ��������֣���ôֻ���������*/
        *n = c;
        return 1;
    }
    do {                         /*��ִ�е�������䣬˵���ַ������֣��˴���ѭ���������������*/
        *n = *n * 10 + (c-'0');       /*�������������ַ�ת�������Ӧ������*/
        c = getchar();
    } while(InN(c));         /*�����һ���ַ������֣�������һ��ѭ��*/
    ungetc(c,stdin);            /*�¶�����ַ��������֣������������,Ϊ�˲�Ӱ���´ζ��룬�Ѹ��ַ��Żص����뻺����*/
    return 0;
}

int evaluateExpression(){
    int n;
    int flag;
    int c;
    char x, y;
    int a,b;
    char OP[] = "+-*/()#";
    SqStack* OPTR;
    SqStack* OPND;
    InitStack(&OPTR);
    Push(&OPTR,'#');
    InitStack(&OPND);
    flag = getNext(&c);
    Pop(OPTR, &x);
    while(c !='#' || x != '#') {
        if(flag == 0) {
                  Push(&OPND,c);
                  flag = getNext(&c);
             } else {
            Pop(OPTR, &x);
            switch(Precede(x, c)) {
                case '<':    /*ջ��Ԫ�����ȼ���*/
                    Push(&OPTR, c);
                    flag = getNext(&c);
                    break;
                case '=':    /*�����Ų�������һ�ַ�*/
                    Pop(&OPTR,&x);
                    flag = getNext(&c);
                    break;
                case '>':    /*��ջ������������ջ*/
                    Pop(&OPTR, &y);
                    Pop(&OPND, &b);
                    Pop(&OPND, &a);
                    Push(&OPND, Operate(a, y, b));
                    break;
            }
        }
        Pop(OPTR, &x);
    }
    Pop(OPND, &c);
    return c;
}

void main(){
    int c;
    printf("������һ���ַ�:\n");
    c = evaluateExpression();
    printf("����� = %d\n",c);
    getch();
}
