#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int applyOp(int a,int b,char op){
    if(op=='+') return a+b;
    if(op=='-') return a-b;
    if(op=='*') return a*b;
    if(op=='/') return a/b;
    return 0;
}

int precedence(char op){ return (op=='+'||op=='-')?1:(op=='*'||op=='/')?2:0; }

int eval(char* exp){
    int values[50],vTop=-1; char ops[50]; int oTop=-1;
    for(int i=0; exp[i]; i++){
        if(exp[i]==' ') continue;
        if(isdigit(exp[i])) values[++vTop]=exp[i]-'0';
        else if(exp[i]=='(') ops[++oTop]='(';
        else if(exp[i]==')'){
            while(oTop!=-1 && ops[oTop]!='('){
                int b=values[vTop--],a=values[vTop--];
                values[++vTop]=applyOp(a,b,ops[oTop--]);
            }
            oTop--; // pop '('
        } else {
            while(oTop!=-1 && precedence(ops[oTop])>=precedence(exp[i])){
                int b=values[vTop--],a=values[vTop--];
                values[++vTop]=applyOp(a,b,ops[oTop--]);
            }
            ops[++oTop]=exp[i];
        }
    }
    while(oTop!=-1){
        int b=values[vTop--],a=values[vTop--];
        values[++vTop]=applyOp(a,b,ops[oTop--]);
    }
    return values[vTop];
}

int main(int argc,char* argv[]){
    if(argc<2){ printf("Usage: %s \"expr\"\n",argv[0]); return 0; }
    printf("%d\n", eval(argv[1]));
    return 0;
}

