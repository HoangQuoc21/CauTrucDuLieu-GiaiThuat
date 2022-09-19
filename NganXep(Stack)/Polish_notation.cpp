#include <iostream>
using namespace std;

//KÝ PHÁP BALAN CHUYỂN TỪ TRUNG TỐ SANG HẬU TỐ

struct Node{
    char data;
    Node* pNext;
};

typedef Node* ptrNode;

struct Stack{
    ptrNode pTop;
};

void initStack(Stack &stack){
    stack.pTop = NULL;
}

ptrNode createNode(char x){
    ptrNode newNode = new Node;
    newNode->data = x;
    newNode->pNext = NULL;
    return newNode;
}

bool isEmpty(Stack stack){
    return (stack.pTop == NULL);
}

void Push(Stack &stack, char x){
    ptrNode newNode = createNode(x);
    if (isEmpty(stack))
        stack.pTop = newNode;
    else{
        newNode->pNext = stack.pTop;
        stack.pTop = newNode;
    }
}

char Pop(Stack &stack){
    if (isEmpty(stack)) 
        return ' ';
    else{
        char topData = stack.pTop->data;
        ptrNode deleteNode = stack.pTop;
        stack.pTop = deleteNode->pNext;
        delete deleteNode;
        return topData;
    }
}

//Kiểm tra là toán hạng
bool isOperand(char character){
    if (character <= 'Z' && character >= 'A')
        return true;
    return false;
}

//Kiểm tra là toán tử
bool isOperator(char character){
    if (character == '*' || character == '/' || character == '+' || character == '-' || character == '&' || character == '^')
        return true;
    return false;
}

int getPriority(char c){
    if (c == '*' || c == '/' || c == '%')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        // phép ^ có ưu tiên thấp hơn tất cả?
        return 0;
}

int main(){
    while(1){
        system("cls");
        string infix_notation, postfix_notation;
        cout << "Hay nhap vao bieu thuc trung to ban dau: ";
        cin >> infix_notation;

        //Bắt đầu chuyển từ trung tố sang hậu tố: 
        Stack stack;
        initStack(stack);
        
        //0.1
        Push(stack, '(');
        //0.2
        infix_notation.push_back(')');
        for (int i = 0; i < infix_notation.size(); i++){
            //1.
            char x = infix_notation[i];
            //2.
            if (isOperand(x))
                postfix_notation.push_back(x);
            //3.
            if (x == '(')
                Push(stack,x);
            //4.
            if (isOperator(x)){
                while(!isEmpty(stack) && (getPriority(stack.pTop->data) >= getPriority(x)) && isOperator(stack.pTop->data)){
                    char w = Pop(stack);
                    postfix_notation.push_back(w);
                }
                Push(stack,x);
            }
            //5.
            if (x == ')'){
                while(!isEmpty(stack) && (stack.pTop->data != '(')){
                    char w = Pop(stack);
                    postfix_notation.push_back(w);
                }
                Pop(stack);
            }
        }
            cout << "Dang hau to cua trung to " << infix_notation << "la: ";
            cout << postfix_notation << endl;
            system("pause");
        }
   
    return 0;
}
