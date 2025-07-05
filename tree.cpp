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
    void inorder(){
        inorder_imptl(root);
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
        void inorder_imptl(node* current){
            if(!current){
                return;
            }
            inorder_imptl(current->left);
            cout << current->num<< ",";
            inorder_imptl(current->right);
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
    exit(0);
}