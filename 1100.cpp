#include <iostream>
using namespace std;
#define BETWEEN 1
#define END 2
class Node{
public:
    Node(){
        next = NULL;
    }
    
    Node* next;
    char alph;
};
int main(){
    Node* head = new Node;
    Node* tail = head;
    Node* current = head;
    char input;
    Node* beforeHead = new Node;
    Node* newline = beforeHead;
    beforeHead->next = head;
    beforeHead->alph = '0';
    
    int status = END;
    while((input = getchar())!=EOF){
        //[
        //]
        if(input=='\n'){
            tail->next = new Node;
            tail = tail->next;
            tail->alph = input;
            newline = tail;
            status = END;
            continue;
        }
        if(input == '['){
            status = BETWEEN;
            //cout<<"no"<<endl;
            if(newline == beforeHead){
                current = beforeHead;
                if(beforeHead->alph == '0'){
                    beforeHead->alph = '1';
                    beforeHead->next = head->next;
                    head = beforeHead->next;
                }
            }
            else{
                current = newline;
            }
            if(current == tail) status = END;
            
            continue;
        }
        if(input == ']'){
            status = END;
            continue;
        }

        if(status == END){
            //cout << "END" <<endl;
            tail->next = new Node;
            tail = tail->next;
            tail->alph = input;
            
        }
        else{
            //cout << "BETWEEN" <<endl;
            Node* temp = current->next;
            current->next = new Node;
            current = current->next;
            current->alph = input;
            current->next = temp;
        }
    }
    if(beforeHead->alph=='1'){
        //cout << "Hi" << endl;
        head = beforeHead->next;
    }
    Node* printCur = head;

    while(printCur != NULL){
        putchar(printCur->alph);
        printCur = printCur->next;
    }
    
}

