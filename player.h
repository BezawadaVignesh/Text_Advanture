#ifndef PLAYER_H_
#define PLAYER_H_

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<algorithm>

using namespace std;


struct item{
    string item_name;
    item* next;
};
class Player{
public:
    string player_room;
    item* prev_items;
    Player(string room_name){
        health = 100;
        prev_items = NULL;
        player_room = room_name;
    }

    void change_health(int hlt){
        health = health + hlt;
    }

    void add_item(string name_of_item){
        item* new_item = new item;
        new_item->item_name = name_of_item;
        new_item->next = prev_items;
        prev_items = new_item;
    }

    void print_items_in_inventory(){
        item *ptr;
        ptr = prev_items;
        if(prev_items == NULL){
            cout<<"\n\t--Empty--\n"<<endl;
        }
        while(ptr != NULL){
            cout<<"->"<< ptr->item_name<<endl;
            ptr = ptr->next;
        }
        cout<<endl;
    }

    void remove_item(string itm_name, string s){
        if(prev_items != NULL){
            item *ptr, *pre;
            ptr = prev_items;
            while(ptr != NULL){
                if (itm_name == ptr->item_name){
                    if(ptr==prev_items){
                        prev_items = prev_items->next;
                    }else{
                        pre->next = pre->next->next;
                    }
                    if(s==""){
                    cout<<itm_name<<" has been dropped."<<endl;
                    }
                    free(ptr);
                    free(pre);
                    break;
                }
                pre = ptr;
                ptr = ptr->next;
            }
            if(ptr == NULL){
                cout<<"You have no item named "<<itm_name<<" to drop"<<endl;
            }
        }else{
            cout<<"You have no item named "<<itm_name<<" to drop"<<endl;
        }
    }


//private:
    int health;




};
#endif

