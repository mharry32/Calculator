#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define right 0
#define left 1
#define push(x) st1.tok_stack[++st1.size]=x
#define pop() st1.tok_stack[st1.size--]
#define get_assoc(c) (c=='^') ? right : left
#define isalpha(c) ( ( (c>=65 && c<=90) || (c>=97 && c<=122)   ) ? 1 : 0)
#define isdigit(c) ((c>=48 && c<=57) ? 1 : 0) 
typedef struct token
{
	char token_str[100];
	char token_type;
	int precedence;
	int assoc;
} token;
typedef struct stack
{
	int size;
	token tok_stack[100];
} stack;
stack st1;
int get_precedence(c){ return (c=='+' || c=='-') ? 2 : (c=='/' || c=='*') ? 3 : 4;}
char check_type(char c)
{ 
return (c==42 || c==43 || c==45 || c==47 || c==94) ? 'o' : isalpha(c) ? 'c' : (isdigit(c) || c=='.') ? 'd' : (c==40 || c==41) ? 'p' : (c==44) ? 's' : 0;
}
int out_length=0;
char output[1000];
char expression[1000];
float answer;
void get_rpn();
void eval_rpn();
void do_op(token temp);


int main()
{
	while(1)
	{
		printf("Type your expression(no spaces):\n");
		scanf("%s",expression);
		get_rpn();
		eval_rpn();
		printf("%f\n",answer);
		memset(st1.tok_stack, 0, sizeof(st1.tok_stack));
		memset(output,0,sizeof(output));
		out_length=0;
	}
}











void get_rpn()
{
	st1.size=0;
	int x,z;
	token o1;
	token o2;
	for(x=0;x<strlen(expression);x++)
	{
	//////////////////////////////////////////////////////////
		if(check_type(expression[x])=='d')
		{
			output[out_length++]=expression[x];
			continue;
		}
	/////////////////////////////////////////////////////////
		if(check_type(expression[x])=='o')
		{
			if(output[out_length-1]!=' ')
				output[out_length++]=' ';
			o1.token_str[0]=expression[x];
			o1.assoc=get_assoc(expression[x]);
			o1.precedence=get_precedence(expression[x]);
			o2=st1.tok_stack[st1.size];
			while(check_type(o2.token_str[0])=='o')
			{
				o2.precedence=get_precedence(o2.token_str[0]);
				if((o1.assoc==left && o1.precedence==o2.precedence) || (o1.precedence<o2.precedence))
				{
					output[out_length++]=pop().token_str[0];
					if(output[out_length-1]!=' ')
						output[out_length++]=' ';
				}
				else 
					break;
				o2=st1.tok_stack[st1.size];
			}
			push(o1);
			continue;
		}
	////////////////////////////////////////////////////////////
		if(expression[x]==40)
		{
			o1.token_str[0]=expression[x];
			o1.assoc=get_assoc(expression[x]);
			o1.precedence=get_precedence(expression[x]);
			o1.token_type='p';
			push(o1);
			continue;
		}
	////////////////////////////////////////////////////////////
		if(expression[x]==41)
		{
			while((st1.tok_stack[st1.size]).token_str[0]!=40 && st1.size>0)
			{
					if(output[out_length-1]!=' ')
						output[out_length++]=' ';
					output[out_length++]=pop().token_str[0];
					if(output[out_length-1]!=' ')
						output[out_length++]=' ';
			}
			if(st1.size==-1)
			{
				printf("Paranthesis mismatch!");
				break;
			}
			pop();
			if((st1.tok_stack[st1.size]).token_type=='c')
			{
				if(output[out_length-1]!=' ')
					output[out_length++]=' ';	
				strcat(output,pop().token_str);
				out_length=strlen(output);
			}
		}
		
	
	///////////////////////////////////////////////////////////
	if(check_type(expression[x])=='c')
	{
		z=0;
		while(check_type(expression[x])=='c')
		{
			o1.token_str[z++]=expression[x++];
		}
		x--;
		o1.token_str[z]='\0';
		o1.token_type='c';
		push(o1);

	}
	///////////////////////////////////////////////////////////
	if(check_type(expression[x])=='s')
	{
		while((st1.tok_stack[st1.size]).token_str[0]!=40 && st1.size>=0)
		{
			if(output[out_length-1]!=' ')
				output[out_length++]=' ';
			output[out_length++]=pop().token_str[0];
			if(output[out_length-1]!=' ')
				output[out_length++]=' ';
		}
		if(st1.size==-1)
			printf("Paranthesis mismatch!");
	}
	//////////////////////////////////////////////////////////
	}

	while(st1.size>0)
	{
		if(output[out_length-1]!=' ')
			output[out_length++]=' ';
		if(check_type(expression[x])=='p')
			printf("Paranthesis mismatch!");
		output[out_length++]=pop().token_str[0];
	}
	output[out_length++]=pop().token_str[0];
	strcpy(expression,output);
}
void do_op(token temp)
{
	char type=check_type(temp.token_str[0]);
	if(type=='d')
		push(temp);
	else
	{
		token tempo;
		if(strcmp(temp.token_str,"+")==0)
		{
			float p1=atof(pop().token_str);
			float p2=atof(pop().token_str);
			float ans=p1+p2;
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"-")==0)
		{
			float p1=atof(pop().token_str);
			float p2=atof(pop().token_str);
			float ans=p2-p1;
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"*")==0)
		{
			float p1=atof(pop().token_str);
			float p2=atof(pop().token_str);
			float ans=p1*p2;
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"/")==0)
		{
			float p1=atof(pop().token_str);
			float p2=atof(pop().token_str);
			float ans=p2/p1;
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"^")==0)
		{
			float p1=atof(pop().token_str);
			float p2=atof(pop().token_str);
			float ans=pow(p2,p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"sin")==0)
		{
			float p1=atof(pop().token_str);
			float ans=sin(p1*M_PI/180);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"cos")==0)
		{
			float p1=atof(pop().token_str);
			float ans=cos(p1*M_PI/180);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"tan")==0)
		{
			float p1=atof(pop().token_str);
			float ans=tan(p1*M_PI/180);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"arcsin")==0)
		{
			float p1=atof(pop().token_str);
			float ans=asin(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"arccos")==0)
		{
			float p1=atof(pop().token_str);
			float ans=acos(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"arctan")==0)
		{
			float p1=atof(pop().token_str);
			float ans=atan(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"sinh")==0)
		{
			float p1=atof(pop().token_str);
			float ans=sinh(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"cosh")==0)
		{
			float p1=atof(pop().token_str);
			float ans=cosh(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"tanh")==0)
		{
			float p1=atof(pop().token_str);
			float ans=tanh(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"exp")==0)
		{
			float p1=atof(pop().token_str);
			float ans=exp(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"ln")==0)
		{
			float p1=atof(pop().token_str);
			float ans=log(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"log")==0)
		{
			float p1=atof(pop().token_str);
			float ans=log10(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		else if(strcmp(temp.token_str,"sqrt")==0)
		{
			float p1=atof(pop().token_str);
			float ans=sqrt(p1);
			sprintf(tempo.token_str,"%f",ans);
		}
		push(tempo);
	}
}
void eval_rpn()
{
	st1.size=0;
	token temp;
	int x,z=0;
	for(x=0;x<strlen(expression);x++)
	{
		if(expression[x]==' ')
		{
			temp.token_str[z]='\0';
			do_op(temp);
			z=0;
		}
		else
		{
			temp.token_str[z++]=expression[x];
			if(x==strlen(expression)-1)
			{
				temp.token_str[z]='\0';
				do_op(temp);
			}
		}
	}
	answer=atof(pop().token_str);
}
