#include <iostream>

using namespace std;

struct node{
    int num;
    node* left;
    node* right;
};

struct bin_tree{
    node * root = nullptr;
    public:
    //1.찾는 함수
    node* find (int value){//일부러 public과 private로 구분해서,작성
        return find_impl(root,value);
    }
    //2.트리에 삽입 하는 함수
    void insert(const int value){
        if(root==NULL){
            root = new node{value,NULL,NULL};
            return;
        }
            insert_impl(root,value);
            return;

    }
    void inorder(){ //중위순회
        inorder_impl(root);
    }

    node* delete_value(int value){//노드를 삭제하는 함수
        root = delete_impl(root,value);
    }

    node* succesor(node* start){//선행자(자기보다 큰값 중 가장 작은 값)
        auto current = start->right;
        while(current&&current->left){//자기자신과 자기자신의 오른쪽 값이 둘 다 NULL값이 되지않게 search
            current = current->left;
        }
        return current;
    }
    private:
        node* find_impl(node* node,const int value){

            if(node->num==value){//3.같다면 그때 node의 값을 반환
                return node;
            }
            if(node->num < value){//1.만약 찾으려는 값이 현재 노드 값보다 크다면,오른쪽으로 이동
                return find_impl(node->right,value);
            }else if(node->num >value){//2.만약 찾으려는 값이 현재 노드 값보다 작다면,왼쪽으로 이동
                return find_impl(node->left,value);
            }

            cout <<"찾으시는 값이 노드에 없습니다"<<endl;
            return NULL;//없다면 null값 반환

        }
        void insert_impl(node* current,const int value){

            if(value < current->num){//1.작은경우 왼쪽으로 이동
                if(!current->left){
                    current->left = new node{value,NULL,NULL};
                }else{
                    insert_impl(current->left,value);
                }
                return;
            }
            if(value > current->num){//2.큰경우 오른쪽으로 이동
                if(!current->right){
                    current->right = new node{value,NULL,NULL};
                }else{
                    insert_impl(current->right,value);
                }
                return;
            }
        }
        void inorder_impl(node* current){
            if(!current){
                return;
            }
            inorder_impl(current->left);
            cout << current->num<< ",";
            inorder_impl(current->right);
        }

        node* delete_impl(node* pre,const int value){//삭제함수: 삭제할 노드를 찾고,그노드의 값을 현재 노드의 붙여야 함

            if(pre->num < value){//1.오른쪽에 내가 삭제할 값이 있는 경우
                pre->right = delete_impl(pre->right,value);
            }else if( value<pre->num){//2.왼쪽에 내가 삭제할 값이 있는 경우
                pre -> left = delete_impl(pre->left,value);
            }else{//3.삭제 케이스 삭제할 노드를 만났을때,그 노드에서의 처리
                if(!pre->left){//1.왼쪽 자식이 없는경우나 자식이 없는경우->삭제하고 오른쪽 값을 반환함
                    auto tmp = pre->right;
                    delete pre;
                    return tmp;
                }
                if(!pre->right){//2.오른쪽 자식이 없는경우->삭제하고 왼쪽 값을 반환함
                    auto tmp = pre->left;
                    delete pre;
                    return tmp;
                }
                //3.둘 다 자식이 있는경우? 삭제 하고 어떻게?{선행자의 값을 삭제할 노드에 넣고,서브 트리에서 선행자를 삭제}
                auto tmp = succesor(pre);
                pre->num = tmp->num;
                pre->right = delete_impl(pre->right,tmp->num);
            }
            return pre;
        }
};

int main(void){
    bin_tree tree;
    tree.insert('A');
    tree.insert(10);
    tree.insert(20);
    tree.insert(8);
    tree.insert(11);
    tree.insert(15);
    tree.insert(28);
    tree.insert(4);
    tree.insert(2);
    tree.inorder();
    tree.delete_value(4);
    tree.inorder();
    exit(0);
}