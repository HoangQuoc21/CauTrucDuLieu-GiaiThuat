#include <iostream>
#include <cmath>
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

//Kiểm tra ký tự là toán hạng chữ
bool isLetterOperand(char character){
    return ((character <= 'z' && character >= 'a')||(character <= 'Z' && character >= 'A'));
}

//Kiểm tra ký tự là toán hạng số
bool isNumberOperand(char character){
    return (character <= '9' && character >= '0');
}

//Kiểm tra ký tự là toán tử
bool isOperator(char character){
    return (character == '*' || character == '/' || character == '+' || character == '-' || character == '&' || character == '^');
}

int getPriority(char c){
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/' || c == '%')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        // phép ^ có ưu tiên thấp hơn tất cả?
        return 0;
}

string infixTopostfix(string infix_notation){
    string postfix_notation;
    Stack stack;
    initStack(stack);
    //Bắt đầu chuyển từ trung tố sang hậu tố: 
    //0.1 Thêm '(' vào stack
    Push(stack, '(');
    //0.2 thêm ')' vào biểu thức trung tố
    infix_notation.push_back(')');
    for (int i = 0; i < infix_notation.size(); i++){
        //1. Duyệt từng ký tự từ trái sang phải
        char x = infix_notation[i];
        //2. Nếu là toán hạng thì Push vào biểu thức hậu tố
        if (isLetterOperand(x) || isNumberOperand(x))
            postfix_notation.push_back(x);
        //3. Nếu là dấu '(' thì Push vào stack
        if (x == '(')
            Push(stack,x);
        //4. Nếu là toán tử thì 
        if (isOperator(x)){
            //4.1 Nếu trên đỉnh stack là toán tử và toán tử đó có độ ưu tiên lớn hơn toán tử đang xét thì
            while(!isEmpty(stack) && (getPriority(stack.pTop->data) >= getPriority(x)) && isOperator(stack.pTop->data)){
                //Push toán tử đó vào biểu thức hậu tố
                char w = Pop(stack);
                postfix_notation.push_back(w);
            }
            //4.2 Push toán tử đang xét vào stack
            Push(stack,x);
        }
        //5. Nếu là dấu ')' thì Pop hết các ký tự trong stack ra đồng thời Push các ký tự đó vào biểu thức hậu tố. Dừng lại khi gặp dấu ')' trong stack 
        if (x == ')'){
            while(!isEmpty(stack) && (stack.pTop->data != '(')){
                char w = Pop(stack);
                postfix_notation.push_back(w);
            }
            //Pop dấu '(' được bỏ vào stack ở bước 0.1 ra
            Pop(stack);
        }
    }
    return postfix_notation;
}

int cToi(char c){
    return (int)(c - 48);
}

char iToc(int i){
   return (char)(i + 48);
}

//Tính giá trị biểu thức hậu tố
int EvaluatePostfix(string infix_notation){
    string postfix_notation = infixTopostfix(infix_notation);
    Stack stack;
    initStack(stack);
    //Duyệt hết qua các phần tử của biểu thức hậu tố từ trái sang phải
    for (int i=0; i< postfix_notation.size(); i++){
        char c = postfix_notation[i];
        //Nếu là toán hạng số thì Push vào stack
        if (isNumberOperand(c))
            Push(stack,c);
        //Nếu là toán tử thì tính giá trị biểu thức tương ứng với 2 toán hạng ở đỉnh stack
        if (isOperator(c)){
            int x = cToi(Pop(stack));
            int y = cToi(Pop(stack));
            switch(c){
                case '+': y = y+x; break;
                case '-': y = y-x; break;
                case '*': y = y*x; break;
                case '/': y = y/x; break;
                case '^': y = pow(y,x); break;
                case '%': y = y%x; break;
            }
        //Sau khi tính xong thì Push kết quả vừa rồi vào stack
            char z = iToc(y);
            Push(stack,z);
        }
    }
    //Sau khi duyệt hết biểu thức hậu tố và tính toán thì kết quả của biểu thức hậu tố chính là toán hạng cuối cùng còn trong stack
    return cToi(Pop(stack));
}


int main(){
    while(1){
        string infix_notation, postfix_notation;
        system("cls");
        cout << "==============================KY PHAP BA LAN=============================\n";
        cout << "Dau tien hay nhap vao bieu thuc trung to: ";
        cin >> infix_notation;
        postfix_notation = infixTopostfix(infix_notation);
        cout << "-Bieu thuc hau to cua no la: ";
        cout << postfix_notation << endl;
        cout << "-Gia tri cua bieu thuc hau to tren la (chi dung khi cac toan hang nhap vao la so): ";
        cout << EvaluatePostfix(infix_notation) << endl;
        system("pause");
    }
    return 0;
}
