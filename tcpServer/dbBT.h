//
// Created by ncc on 26/01/2023.
//

#ifndef XBANKV1_DBBT_H
#define XBANKV1_DBBT_H


#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#define MAX 5
#define MIN 2


struct trans{

    char note[200];

};
struct data{

    unsigned int id;
    char name[30];
    char email[50];
    char password[50];
    char status[1];
    unsigned int amount;
    //unsigned int phNumber;
    char address[200];

    struct trans rc[100];

};
struct BTreeNode{
    register_t keys[MAX];
    struct data db[MAX];
    int count;
    bool leaf;
    struct BTreeNode* child[MAX+1];
};
struct BTreeNode* root;






int total_data_count=0;
int checkingpos(struct BTreeNode* prevnode,int newkey,int flag,struct BTreeNode* node);
void shifttoleft(int pos,struct BTreeNode* prevnode);
void shifttoright(int pos,struct BTreeNode* shiftnode);
void update(int currentKey,int newKey,struct BTreeNode* y);
void arrange(int key,struct BTreeNode* y);
void childMove(int index ,struct BTreeNode* y,int key);
void marge(struct BTreeNode* prevnode,int pos){
    prevnode->child[pos]->keys[prevnode->child[pos]->count]=prevnode->keys[pos];
    prevnode->child[pos]->keys[3]=prevnode->child[pos+1]->keys[0];
    prevnode->child[pos]->keys[4]=prevnode->child[pos+1]->keys[1];
    prevnode->child[pos]->count=5;
    shifttoleft(pos,prevnode);
    prevnode->count--;
}
int swapkey_right_to_left(struct BTreeNode* parent,int leftpos,int rightpos){
    if(leftpos==rightpos || rightpos<0){
        return 0;
    }
    parent->child[rightpos-1]->keys[parent->child[rightpos-1]->count]=parent->keys[rightpos-1];
    parent->child[rightpos-1]->count++;
    parent->keys[rightpos-1]=parent->child[rightpos]->keys[0];
    parent->child[rightpos]->count--;
    shifttoleft(0,parent->child[rightpos]);
    parent->child[rightpos]->keys[parent->child[rightpos]->count]=0;
    swapkey_right_to_left(parent,leftpos,rightpos-1);
    return 0;
}
int swapkey_left_to_right(struct BTreeNode* parent,int leftpos,int rightpos){
    if(leftpos==rightpos || rightpos<0){
        return 0;
    }
    shifttoright(0,parent->child[leftpos+1]);
    parent->child[leftpos+1]->keys[0]=parent->keys[leftpos];
    parent->child[leftpos+1]->count++;

    parent->keys[leftpos]=parent->child[leftpos]->keys[parent->child[leftpos]->count-1];
    parent->child[leftpos]->keys[parent->child[leftpos]->count-1]=0;
    parent->child[leftpos]->count--;
    swapkey_left_to_right(parent,leftpos+1,rightpos);
    return 0;
}
int check_num_of_key(struct BTreeNode* node){

    if(node->child[0]==NULL || node==NULL){
        return 0;
    } else{
        int index=node->count;
        int arr[index+1];
        for(int i=0;i<index+1;i++){
            arr[i]=node->child[i]->count;
        }

        for(int i=0;i<index+1;i++){
            for(int j=i+1;j<index+1;j++){
                int diff=arr[i]-arr[j];
                if(diff==2 || diff==-2){
                    if(diff>0){//2 condition
                        swapkey_left_to_right(node,i,j);
                        return 0;
                    } else {//-2 condition
                        swapkey_right_to_left(node, i, j);
                        return 0;
                    }
                }
            }
        }
    }
}
void shifttoleft(int pos,struct BTreeNode* node){
    for(int j=pos;j<node->count;j++){
        node->keys[j]=node->keys[j+1];
        node->child[j+1]=node->child[j+2];
    }
}
void shifttoright(int pos,struct BTreeNode* shiftnode){
    int index=shiftnode->count-1;
    for(int i=index;i>=pos;i--){
        shiftnode->keys[i+1]=shiftnode->keys[i];
        shiftnode->child[i+2]=shiftnode->child[i+1];
        if(i<=0){
            break;
        }
    }
}
void cnull(struct BTreeNode* node){
    for(int i=0;i<6;i++){
        node->child[i]=NULL;
    }
}
int insertnonfull(int pos,struct BTreeNode* node,int newkey){
//    for(int i=0;i<node->count;i++){
//        if(node->keys[i]==newkey){
//
//        } else{
    shifttoright(pos,node);
    node->keys[pos]=newkey;
    node->count++;
//        }
//    }

}
int sp(struct BTreeNode* prevnode,struct BTreeNode* splitNode,int newkey){
    struct BTreeNode* rightchild= malloc(sizeof (struct BTreeNode));
    if(splitNode->leaf==true){
        cnull(splitNode);
        cnull(rightchild);
    } else{
        rightchild->child[0]=splitNode->child[MAX-2];
        rightchild->child[1]=splitNode->child[MAX-1];
        rightchild->child[2]=splitNode->child[MAX];

        splitNode->child[MAX]=NULL;
        splitNode->child[MAX-1]=NULL;
        splitNode->child[MAX-2]=NULL;
    }//this condition for child
    rightchild->keys[0]=splitNode->keys[MAX-2];
    rightchild->keys[1]=splitNode->keys[MAX-1];
    rightchild->count=2;//copy key to right

    struct BTreeNode* troot= malloc(sizeof (struct BTreeNode));
    troot->keys[0]=splitNode->keys[MAX-3];
    troot->count=1;//copy key to troot
    troot->leaf=false;

    splitNode->count=2;//clean split node
    splitNode->keys[MAX-1]=0;
    splitNode->keys[MAX-2]=0;
    splitNode->keys[MAX-3]=0;

    if(prevnode==NULL){//root
        //level++;
        if(splitNode->child[0]==NULL){
            rightchild->leaf=true;
        } else{
            rightchild->leaf=false;
        }
        troot->child[0]=splitNode;
        troot->child[1]=rightchild;
        root=troot;
        checkingpos(prevnode,newkey,0,root);
    } else{//internal
        if(rightchild->child[0]==NULL){
            rightchild->leaf=true;
        } else{
            rightchild->leaf=false;
        }
        int pos=checkingpos(prevnode,troot->keys[0],1,prevnode);
        prevnode->child[pos]=rightchild;
        prevnode=NULL;
        checkingpos(prevnode,newkey,0,root);
    }
}
int checkingpos(struct BTreeNode* prevnode,int newkey,int flag,struct BTreeNode* node){
    int f=0;
    if(node->count>=MAX){
        sp(prevnode,node,newkey);
        return 0;
    }
    for(int pos=0;pos<node->count;pos++){
        if(newkey>node->keys[node->count-1]){
            if(flag==0){
                if(node->leaf==false) {
                    prevnode=node;
                    checkingpos(prevnode,newkey,0,node->child[node->count]);
                    return pos;
                }else{
                    node->keys[node->count]=newkey;
                    node->count++;
                    return pos;
                }
            } else{
                node->keys[node->count]=newkey;
                node->count++;
                return node->count;
            }
        }
        if(newkey<node->keys[pos]){
            if(flag==0){
                if(node->leaf==false){
                    prevnode=node;
                    checkingpos(prevnode,newkey,0,node->child[pos]);////
                    return pos;
                } else{
                    insertnonfull(pos,node,newkey);
                    return pos;
                }
            } else{
                insertnonfull(pos,node,newkey);
                return pos+1;
            }
        }
    }
}
void insert(int key){



    if(root==NULL){
        struct BTreeNode* newnode=malloc(sizeof (struct BTreeNode));
        newnode->keys[0]=key;

        newnode->count=1;
        newnode->leaf=true;
        cnull(newnode);
        root=newnode;
    } else {
        struct BTreeNode* prevnode=NULL;
        checkingpos(prevnode, key, 0, root);
    }
}
struct BTreeNode*search(int search_key,struct BTreeNode* node) {
    int index=node->count;
    if(search_key<node->keys[0] && node->child[0]!=NULL){
        search(search_key,node->child[0]);
    }else if(search_key>node->keys[index-1] && node->child[0]!=NULL){
        search(search_key,node->child[index]);
    }
    for(int i=0;i<index;i++){
        if(search_key==node->keys[i]){
            return node;
        }
    }

}

int delete(int removekey,int prevpos,struct BTreeNode* prevnode,struct BTreeNode* currentnode) {
    if (currentnode == NULL) {
        return 0;
    }
    if (removekey > currentnode->keys[currentnode->count - 1] && currentnode->child[0] != NULL) {
        prevnode = currentnode;
        delete(removekey,currentnode->count, prevnode, currentnode->child[currentnode->count]);
        return 0;
    } else {
        int index = currentnode->count;
        for (int i = 0; i < index; i++) {
            if (removekey == currentnode->keys[i]) {//equal yin tan phyat p mha sorting pyan loat
                if(prevnode==NULL && currentnode->child[0]==NULL){//root only
                    currentnode->count--;
                    shifttoleft(i,currentnode);
                    currentnode->keys[currentnode->count] = 0;
                    return 0;
                } else if(prevnode==NULL && currentnode->child[0]!=NULL){//root nae child(child yae aout mhr child twy shi oo mhr)
                    if(currentnode->child[i]->count>MIN){
                        currentnode->keys[i]=currentnode->child[i]->keys[currentnode->child[i]->count-1];
                        currentnode->child[i]->keys[currentnode->child[i]->count-1]=0;
                        currentnode->child[i]->count--;
                        return 0;
                    } else if(currentnode->child[i+1]->count>MIN){
                        currentnode->keys[i]=currentnode->child[i+1]->keys[currentnode->child[i+1]->count-1];
                        currentnode->child[i+1]->count--;
                        return 0;
                    } else{
                        if (prevpos!=0) {
                            marge(prevnode,prevpos-1);
                            delete(removekey,prevpos,NULL,prevnode);
                            return 0;
                        } else {
                            marge(prevnode,prevpos);
                            delete(removekey,prevpos,NULL,prevnode);
                            return 0;
                        }
                    }
                } else if(prevnode!=NULL && currentnode->leaf){//pure leaf
                    if ( currentnode->count > MIN) {
                        currentnode->count--;
                        shifttoleft(i,currentnode);
                        currentnode->keys[currentnode->count] = 0;
                        return 0;
                    } else if ( currentnode->count < MIN+1) {
                        if (prevpos > 0 && prevnode->child[prevpos - 1]->count > MIN) {
                            swapkey_left_to_right(prevnode, prevpos + 1, prevpos);
                            shifttoright(i, currentnode);
                            currentnode->count--;
                            return 0;
                        } else if (prevnode->child[prevpos + 1]->count > MIN) {
                            swapkey_right_to_left(prevnode, prevpos, prevpos + 1);
                            shifttoleft(0, currentnode);
                            currentnode->count--;
                            return 0;
                        } else if (prevpos!=0) {
                            marge(prevnode,prevpos-1);
                            delete(removekey,prevpos,NULL,prevnode);
                        } else {
                            marge(prevnode,prevpos);
                            delete(removekey,prevpos,NULL,prevnode);
                        }
                        return 0;
                    }
                }else if(prevnode!=NULL && !currentnode->leaf){//pure internal node//root yal child yal pal shi mal
                    if(currentnode->child[i-1]->count>MIN){
                        currentnode->keys[i]=currentnode->child[i-1]->keys[currentnode->child[i-1]->count-1];
                        currentnode->child[i-1]->count--;
                        return 0;
                    }else if(currentnode->child[i+1]->count>MIN){
                        currentnode->keys[i]=currentnode->child[i+1]->keys[0];
                        shifttoleft(0,currentnode->child[i+1]);
                        currentnode->child[i+1]->count--;
                        return 0;
                    } else{
                        marge(currentnode,i);
                        delete(removekey,i,NULL,currentnode);
                        return 0;
                    }
                }
            } else if (removekey < currentnode->keys[i]) {
                prevnode = currentnode;
                delete(removekey,i, prevnode, currentnode->child[i]);
                return 0;
            }
        }
        return 0;
    }
}
void traversal(struct BTreeNode *myNode) {
    int i;
    if (myNode) {

        for (i = 0; i < myNode->count; i++) {
            traversal(myNode->child[i]);
            printf("%d ", myNode->keys[i]);
        }

        traversal(myNode->child[i]);
    }
}
void update(int currentKey,int newKey,struct BTreeNode* y){
    search(currentKey,y);
    for(int j=0 ;j < y->count ;j++){
        if(y->keys[j]==currentKey){
            currentKey = newKey;
            y->keys[j] = newKey;
        }
    }
    int index = y->count;
    if (currentKey < y->keys[0] && y->child[0] != NULL) {
        for(int i=0;i<index;i++) {
            if (currentKey == y->child[0]->keys[i]) {
                for(int j=0 ;j < y->count ;j++){
                    if(y->keys[j]==currentKey){
                        currentKey = newKey;
                        y->keys[j] = newKey;
                    }
                }
            }
        }
    } else {
        if (currentKey > y->keys[index - 1] && y->child[0] != NULL) {
            y = y->child[index];
            index = y->count;
            for(int i=0;i<index;i++){
                if(currentKey==y->keys[i]) {
                    for(int j=0 ;j < y->count ;j++){

                        if(y->keys[j]==currentKey){
                            currentKey = newKey;
                            y->keys[j] = newKey;

                        }
                    }

                }
            }
        }

    }

    arrange(newKey,y);
}
void arrange(int key,struct BTreeNode* y){
    int i = y->count-1;
    int temp = key;
    if(key > y->keys[i]){
        for(int j=i; j <= 0 ; j++){
            y->keys[j-1] = y->keys[j];
            y->keys[i] = temp;
            childMove(i,y,key);
        }
    }else{
        if(key < y->keys[0]){
            for(int j=0 ; j<= i ;j++){

                if( temp == y->keys[j]){
                    int k = j;

                    for(int l = 1 ; l<=j ;l++){

                        y->keys[k] = y->keys[j-l];

                        k--;
                    } y->keys[0] = temp;
                    childMove(j,y,y->keys[j-1]);

                }

            }

        }else{
            if(i>=0 && y->keys[i-1]<key && y->keys[i]>key){
                y->keys[0] = y->keys[i-1];
                y->keys[i-1] = temp;
            }childMove(i-1,y,key);
        }
    }
}
void childMove(int index ,struct BTreeNode* y,int key){
    int t = y->count-1;
    if(y->leaf == false) {
        if (index > 0) {
            for(int ii = 1;ii <= index ;ii++){
                int temp = y->keys[ii];

                int k = y->child[ii]->count - 1;

                int temp1 = y->child[ii]->keys[k];
                while (k >= 0) {
                    if(y->child[ii]->keys[0] > y->keys[ii]  ){
                        y->child[ii]->keys[k] = y->child[ii]->keys[k - 1];
                        k--;

                    } else{
                        return;
                    }

                }  y->child[ii]->keys[0] = temp;
                temp = temp1;
                y->keys[ii] = temp;
            }
            childMove(0,y,y->keys[0]);

        }
        else {
            if(y->child[index]->keys[0] < y->keys[0]){
                int temp = key;
                int k = y->child[index]->count - 1;
                int temp1 = y->child[index]->keys[k];
                y->child[index]->keys[k] = temp;
                temp = temp1;
                y->keys[index] = temp;
            }else{
                return;
            }

        }
    }


}
//int main() {
//
//
////    insert(100);
////    insert(67);
////    insert(96);
////    insert(32);
////    insert(45);
////    insert(88);
////    insert(102);
////    insert(64);
////    insert(99);
////    insert(87);
////    insert(56);
////    insert(300);
////    insert(43);
////    insert(89);
////    insert(90);
////    insert(20);
////    insert(60);
////    insert(57);
////    insert(62);
////    insert(76);
////    update(100,150,root);
////    update(67,50,root);
////    update(89,40,root);
//
//
////    delete(100,0, NULL, root);
//
//
//    while (true){
//        int option;
//        int key;
//        printf("Enter your option\n1. insert data\n2. to delete data\n3. to exit:");
//        scanf("%d",&option);
//        switch(option){
//            case 1:
//                printf("enter data to insert=>");
//                scanf("%d",&key);
//                insert(key);
//                traversal(root);
//                printf("\n");
//                break;
//            case 2:
//                printf("enter data to delete=>");
//                scanf("%d",&key);
//                delete(key,0,NULL,root);
//                traversal(root);
//                printf("\n");
//                break;
//
//            case 3:
//                exit(00);
//        }
//    }
//}



#endif //XBANKV1_DBBT_H
