#include "calculator.h"
#include "stack.h"
#include <assert.h>		
#include <stdio.h>

typedef double (*calculate_t)(double num1, double num2);
typedef const char *(*act_func_t)(const char *str);
typedef struct op_data op_data_t;

	
static Stack_t *num_stack;
static Stack_t *op_stack;

struct op_data
{
    int precedence;
	act_func_t handler_func;
    calculate_t calculate_func;
};

static double Add(double num1, double num2);
static double Substract(double num1, double num2);
static double Multiply(double num1, double num2);
static double Divide(double num1, double num2);
static const char *SpaceHandler(const char *str);
static const char *NumHandler(const char *str);
static const char *OpHandler(const char *str);
static const char *OpenParHandler(const char *str);
static const char * CloseParHandler(const char *str);
static const char *UnaryHandler(const char *str);
static void CalcOneOp();
static void LUTValues(int index ,int precedence, act_func_t handler_func, calculate_t calculate_func);
static void LUTInit(void);


static op_data_t lut[128];
static act_func_t lut_unary[2] = {OpHandler,NumHandler};
static int unary_status = 1;




static void LUTInit(void)
{
	int i;

	for (i = 48; i < 58; ++i)  /*for numbers 0-9*/
	{
		LUTValues(i,0,NumHandler,NULL);
	}

	LUTValues('(',2,OpenParHandler ,NULL);
	LUTValues(')',3,CloseParHandler ,NULL);

	LUTValues('+',4,UnaryHandler ,Add);
	LUTValues('-',4,UnaryHandler ,Substract);
	LUTValues('*',5,OpHandler ,Multiply);
	LUTValues('/',5,OpHandler ,Divide);
	LUTValues(' ',0,SpaceHandler ,NULL);

	
}

static void LUTValues(int index ,int precedence, act_func_t handler_func, calculate_t calculate_func)
{
	lut[index].calculate_func = calculate_func;
	lut[index].handler_func = handler_func;
	lut[index].precedence = precedence;

}


static const char *NumHandler(const char *str)
{
    double *num = NULL;
	char *end;
	assert(str);

	num = (double *)malloc(sizeof(double));
	if(NULL == num)
	{
		exit(1);
	}

    *num = strtod(str, &end);  
 
    StackPush(num_stack, num);

	unary_status = 0;
    return end;
}


static const char *OpHandler(const char *str)
{
	char *op = NULL;		/* operator we want to push */

	assert(str);
	op = (char *)malloc(sizeof(char));
	if(NULL == op)
	{
		exit(1);
	}

	*op = *str;
	

	while (!StackIsEmpty(op_stack) && lut[(int)(*(int *) StackPeek(op_stack))].precedence >= lut[(int)(*op)].precedence)
	{
		CalcOneOp();
	}
	unary_status = 1;
	StackPush(op_stack, op);

	str += 1;

    return str;
}

/* calculate one operator and push result to num_stack */
static void CalcOneOp()
{
	double *num1 = NULL;
	double *num2 = NULL;
	double *num = NULL;
	char  *op = NULL;

	num = (double *)malloc(sizeof(double));
	if(NULL == num)
	{
		exit(1);
	}

	num2 = (double *) StackPeek(num_stack);
	StackPop(num_stack);

	num1 = (double *) StackPeek(num_stack);
	StackPop(num_stack);
	
	op = (char *) StackPeek(op_stack);
	StackPop(op_stack);

	
	*num = lut[(int)*op].calculate_func(*num1, *num2);
	
	free(num1);
	free(num2);
	free(op);

	StackPush(num_stack, num);
}


double Calculator(const char *expression)
{
	double *last_num = NULL;
	double result = 0;
	num_stack = StackCreate(50);
	op_stack = StackCreate(50);

	LUTInit();
	unary_status = 1;
	
    while (*expression)
    {
		expression = lut[(int)*expression].handler_func(expression);
    }

	while (!StackIsEmpty(op_stack))
	{
		CalcOneOp();
	}
	
    last_num = (double *) StackPeek(num_stack);
	result = *last_num;

	StackPop(num_stack);
	free(last_num);

    StackDestroy(num_stack);
    StackDestroy(op_stack);

    return result;	
}


static double Add(double num1, double num2)
{
    return (num1 + num2);
}

static double Substract(double num1, double num2)
{
    return (num1 - num2);
}

static double Multiply(double num1, double num2)
{
    return (num1 * num2);
}

static double Divide(double num1, double num2)
{
    assert(num2);
	return (num1 / num2);
}

static const char *SpaceHandler(const char *str)
{
	return (++str);
}

static const char *OpenParHandler(const char *str)
{
	char *op = NULL;		/* operator we want to push */

	assert(str);
	op = (char *)malloc(sizeof(char));
	if(NULL == op)
	{
		exit(1);
	}

	*op = *str;
	unary_status = 1;
	StackPush(op_stack, op);
    return (++str);
}



static const char * CloseParHandler(const char *str)
{

	char *op = NULL;
	while ((StackSize(op_stack) > 1) &&
	('(' != *(char *) StackPeek(op_stack)))
	{
		CalcOneOp();
	}

	op = StackPeek(op_stack);
	StackPop(op_stack);	/* pop the '(' */
	free(op);
	
	unary_status = 0;
    return (++str);
}


static const char *UnaryHandler(const char *str)
{
	return lut_unary[unary_status](str);
}


