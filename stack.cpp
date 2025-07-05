#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct node{
    string position;
    node* first;
    node* second;
};

struct org_tree{
    node* root;
    static org_tree* create_tree(const string &position){//트리를 전역적으로 만들어주는 static 객체 사용
        org_tree *tree =  new org_tree();
        tree->root = new node{position,NULL,NULL};
        return tree;
    }

    node* find(node* pre,const string& position){
        node* present = pre;
        if(present==NULL){//마지막 노드에서 search할때,NULL값이라면 NULL을 반환.
            return NULL;
        }

        if(present->position==position){//현재값이랑 같은지
            return pre;
        }
        auto first = find(present->first,position);
        if(first){//왼쪽 자식값이 NULL이 아닌경우
           return  first;
        }
        auto second = find(present->second,position);
        if(second){//오른쪽 자식 값이 NULL이 아닌경우
            return second;
        }

    }
    void addSubordinate(const string& supervisor,const string& subordinate){//상사와 부하직원으로 삽입
        node* root = this->root;
        node* sup;
        sup = find(root,supervisor);
        if(sup->first==NULL){//왼쪽이 비어있다면..
            sup->first = new node{subordinate,NULL,NULL};
            cout << sup->position <<" 왼쪽 밑에 "<< subordinate<<" 노드가 삽입 되었습니다"<<endl; 
        }else if(sup->second==NULL){//오른쪽이 비어있다면..
            sup->second = new node{subordinate,NULL,NULL};
            cout << sup->position <<" 오른쪽 밑에 "<< subordinate<<"노드가 삽입 되었습니다"<<endl; 
        }
    }
    void levelOrder(){
        node* root = this->root;
        queue<node*> q;
        q.push(root);
        while(!q.empty()){
            int qsize = q.size();
            for (int i = 0; i < qsize; i++)
            {
                auto current = q.front();
                q.pop();
                cout << current->position << ",";
                if(current->first != NULL){
                    q.push(current->first);
                }
                if(current->second != NULL){
                    q.push(current->second);
                }
            }
            cout << "\n";
            
        }
    }
};

int main(void){
    auto tree = org_tree::create_tree("CEO");
    tree->addSubordinate("CEO","사장");
    tree->addSubordinate("사장","기획이사");
    tree->addSubordinate("사장","재무이사");
    tree->addSubordinate("기획이사","마케팅팀장");
    tree->addSubordinate("기획이사","홍보팀장");
    tree->addSubordinate("재무이사","감사팀장");
    tree->levelOrder();
    exit(0);
}