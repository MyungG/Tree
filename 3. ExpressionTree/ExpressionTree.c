#include "ExpressionTree.h"

ETNode* ET_CreateNode(ElementType NewData)
{
	ETNode* NewNode = (ETNode*)malloc(sizeof(ETNode));
	NewNode->Left = NULL;
	NewNode->Right = NULL;
	NewNode->Data = NewData;

	return NewNode;
}

void ET_DestroyNode(ETNode* Node)
{
	free(Node);
}

void ET_DestroyTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	ET_DestroyTree(Node->Left);				// ���� ���� Ʈ�� �Ҹ�
	ET_DestroyTree(Node->Right);			// ������ ���� Ʈ�� �Ҹ�
	ET_DestroyNode(Node);					// ��Ʈ ��� �Ҹ�
}

void ET_PreorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	printf("  %c", Node->Data);				// ��Ʈ ��� ���
	ET_PreorderPrintTree(Node->Left);		// ���� ���� Ʈ�� ���
	ET_PreorderPrintTree(Node->Right);		// ������ ���� Ʈ�� ���
}

void ET_InorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	printf("(");
	ET_InorderPrintTree(Node->Left);		// ���� ���� Ʈ�� ���

	printf("  %c", Node->Data);				// ��Ʈ ��� ���

	ET_InorderPrintTree(Node->Right);		// ������ ���� Ʈ�� ���
	printf(")");
}

void ET_PostorderPrintTree(ETNode* Node)
{
	if (Node == NULL)
		return;

	ET_PostorderPrintTree(Node->Left);		// ���� ���� Ʈ�� ���
	ET_PostorderPrintTree(Node->Right);		// ������ ���� Ʈ�� ���
	printf("  %c", Node->Data);				// ��Ʈ ��� ���
}

void ET_BuildExpressionTree(char* PostfixExpression, ETNode** Node)
{
	int  len	= strlen(PostfixExpression);
	char Token	= PostfixExpression[len - 1];
	PostfixExpression[len - 1] = '\0';

	switch (Token)
	{
		// �������� ���
	case '+': case '-': case '*': case '/':
		(*Node) = ET_CreateNode(Token);
		ET_BuildExpressionTree(PostfixExpression, &(*Node)->Right);
		ET_BuildExpressionTree(PostfixExpression, &(*Node)->Left);
		break;

		// �ǿ������� ���
	default:
		(*Node) = ET_CreateNode(Token);
		break;
	}
}

double ET_Evaluate(ETNode* Tree)
{
	char Temp[2];

	double Left	  = 0;
	double Right  = 0;
	double Result = 0;

	if (Tree == NULL)
		return 0;

	switch (Tree->Data)
	{
		// �������� ���
	case '+': case '-': case '*': case '/':
		Left = ET_Evaluate(Tree->Left);
		Right = ET_Evaluate(Tree->Right);

		if		(Tree->Data == '+') Result = Left + Right;
		else if (Tree->Data == '-') Result = Left - Right;
		else if (Tree->Data == '*') Result = Left * Right;
		else if (Tree->Data == '/') Result = Left / Right;
		break;

		// �ǿ������� ���
	default:
		memset(Temp, 0, sizeof(Temp));
		Temp[0] = Tree->Data;
		Result  = atof(Temp);
		break;
	}

	return Result;
}