#include <stdio.h>
#include <ctype.h>

char stack[50]; int top=-1;

int prec(char op){ return (op=='+'||op=='-')?1:(op=='*'||op=='/')?2:0; }
void push(char c){ stack[++top]=c; }
char pop(){ return stack[top--]; }
char peek(){ return stack[top]; }

void infixToPostfix(char exp[]){
    for(int i=0; exp[i]; i++){
        char c=exp[i];
        if(isdigit(c)) printf("%c",c);
        else if(c=='(') push(c);
        else if(c==')'){
            while(top!=-1 && peek()!='(') printf("%c",pop());
            pop();
        } else {
            while(top!=-1 && prec(peek())>=prec(c)) printf("%c",pop());
            push(c);
        }
    }
    while(top!=-1) printf("%c",pop());
}

int main(){
    char exp[]="(2+3)*4-5/2";
    infixToPostfix(exp);
    return 0;
}

