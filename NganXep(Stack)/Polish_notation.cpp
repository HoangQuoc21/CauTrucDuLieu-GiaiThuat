#include <iostream>
#include <cmath>
using namespace std;

//KÝ PHÁP BALAN CHUYỂN TỪ TRUNG TỐ SANG HẬU TỐ
//VÀ CHUYỂN TỪ TRUNG TỐ SANG TIỀN TỐ

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

//Kiểm tra ký tự là toán tử chữ
bool isOperator(char character){
    return (character == '*' || character == '/' || character == '+' || character == '-' || character == '&' || character == '^');
}

int getPriority(char c){
    if (c == '^')
        return 4;
    else if (c == '*')
        return 3;
    else if (c == '/' || c == '%')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return 0;
}

string infixToPostfix(string infix_notation){
    string postfix_notation;
    Stack stack;
    initStack(stack);
    //Bắt đầu chuyển từ trung tố sang hậu tố: 
    //0.1
    Push(stack, '(');
    //0.2
    infix_notation.push_back(')');
    for (int i = 0; i < infix_notation.size(); i++){
        //1.
        char x = infix_notation[i];
        //2.
        if (isLetterOperand(x) || isNumberOperand(x))
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
    return postfix_notation;
}

//Đảo ngược biểu thức hậu tố sẽ được biểu thức tiền tố
string infixToPrefix(string infix_notation){
    string prefix_notation, postfix_notation, new_infix_notation;
    //Viết lại "Biểu Thức Trung Tố Mới" bằng cách đảo ngược biểu thức trung tố đã cho
    for (int i = infix_notation.size(), j = 0; i >= 0;i--){
        //Chú ý dấu '(' phải đổi thành ')' và ngược lại
        if (infix_notation[i] == '(')
            new_infix_notation.push_back(')');
        else if (infix_notation[i] == ')')
            new_infix_notation.push_back('(');
        else
            new_infix_notation.push_back(infix_notation[i]) ;
    }
    //Tính biểu thức hậu tố của Biểu Thức Trung Tố Mới
    postfix_notation = infixToPostfix(new_infix_notation);
    //Nghịch đảo biểu thức hậu tố mới tính sẽ được biểu thức tiền tố
    for (int i = postfix_notation.size(); i >= 0; i--)
        prefix_notation.push_back(postfix_notation[i]);
    return prefix_notation;
}

int cToi(char c){
    return (int)(c - 48);
}

char iToc(int i){
   return (char)(i + 48);
}

//Tính giá trị biểu thức hậu tố
int EvaluatePostfix(string infix_notation){
    string postfix_notation = infixToPostfix(infix_notation);
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
    system("cls");
    string infix_notation, choice;
    cout << "==============================KY PHAP BA LAN===========================\n";
    cout << "Hay nhap vao Bieu Thuc Trung To cua ban: ";
    cin >> infix_notation;
    while (choice != "0"){
        system("cls");
        cout << "============================== KY PHAP BA LAN ===========================\n";
        cout << "Bieu Thuc Trung To ban da nhap: " << infix_notation << endl;
        cout << "================================== MENU =================================\n";
        cout << "1. Chuyen sang Bieu Thuc Tien To va tinh gia tri cua no.\n";
        cout << "2. Chuyen sang Bieu thuc Hau To va tinh gia tri cua no.\n";
        cout << "3. Nhap lai Bieu Thuc Trung To.\n";
        cout << "0. Thoat chuong trinh.\n";
        cout << "=================================== END =================================\n";
        cout << "Lua chon cua ban la: ";
        cin >> choice;
        cout << "-------------------------------------------------------------------------\n";
        if (choice == "1"){
            string prefix_notation = infixToPrefix(infix_notation);
            cout << "-Bieu Thuc Tien To: " << prefix_notation << endl;
            cout << "-Gia tri cua Bieu Thuc Tien To (Chi dung khi toan hang la so): " << endl;
        }
        else if (choice == "2"){
            string postfix_notation = infixToPostfix(infix_notation);
            int value = EvaluatePostfix(postfix_notation);
            cout << "-Bieu Thuc Tien To: " << postfix_notation << endl;
            cout << "-Gia tri cua Bieu Thuc Tien To (Chi dung khi toan hang la so): " << value << endl;
        }
        else if (choice == "3"){
            cout << "-Hay nhap Bieu Thuc Trung To: ";
            cin >> infix_notation;
        }
        else if (choice == "0"){
            cout << "Thoat chuong trinh.\n";
            exit(0);
        }
        else 
            cout << "Lua chon khong hop le.\n";
        system("pause");
    }
    return 0;
}