#include<iostream>
#include"json.hpp"
#include"player.h"
#include"sfunc.cpp"
#include<sstream>
#include<stdlib.h>
#include<ctime>
#include<fstream>

using json = nlohmann::json;

string checkForOs()
{
	try{
		if(system("clear")){
			system("cls");
			return "windows";
	}
		else{
			return "linux";
		}
		}catch(...){};
	return "";
	}
string os = checkForOs();
int findRoomNum(json j, string text){
    string word;
    for(int n=0;n<j["rooms"].size();n++){
        word = j["rooms"][n]["id"];
        if (word == text){
            return n;
            break;
            }
    }
    return 0;
}
void clrscr(string os){
    if(os == "linux"){
		system("clear");
	}
	else{
		system("cls");
	}
}
int enemeyExist(json j, string name, string room){
    string word1, word2;
    for(int n=0;n<j["enemies"].size();n++){
        word1 = j["enemies"][n]["initialroom"];
        word2 = j["enemies"][n]["id"];
        if (room==word1){
            if(name=="any"){
                return 1;
            }
            if(word2==name){
            return n;
            }
        }
    }
    return -1;
}
Player p("room1");
int roomindex;

json open(json j, string c){
    string display;
    int health;

    p.player_room = j["rooms"][roomindex][c];
    j["player"]["initialroom"] = p.player_room;
    roomindex = findRoomNum(j, p.player_room);
    cout<<"Entered "<<p.player_room<<"."<<endl;
    //display = j["rooms"][roomindex]["desc"];
    //cout<<display<<endl;
    health = j["rooms"][roomindex]["health"];
    p.change_health(health);
    if (health!=0){
    cout<<"Your health "<<health<<endl;
    }
return j;
}
void printRequired(json j, int index1){
    string word;
    cout<<"You need : ";
    for(int n=0;n<j["enemies"][index1]["killedby"].size();n++){
        word = j["enemies"][index1]["killedby"][n];
        cout<<"\""<<word<<"\" ";
    }
    cout<<"to kill ";
    word = j["enemies"][index1]["id"];
    cout<<word<<endl;
}
json keyRequired(json j, string c){
    bool b;
    item *ptr;
    string display, word;
    //cout<<"1";
    for(int n=0;n<j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"].size();n++){
		word = j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"][n];
		ptr = p.prev_items;
		while(ptr != NULL){
			if(word == ptr->item_name){
				b=true;
				break;
			}
			if(ptr->next == NULL){
				b=false;
				break;
			}
			ptr = ptr->next;
		}
	}
	if(b){
		   for(int n=0;n<j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"].size();n++){
						word = j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"][n];
						ptr = p.prev_items;
						while(ptr != NULL){
							if(word == ptr->item_name){
									if(j["ob"][word][3]=="con"){
										p.remove_item(ptr->item_name, "e");
									}
								break;
							}
							ptr = ptr->next;
						}
				}
			for(int n=0; n<j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"].size(); n++){
				j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"].erase(n);

			}
				j = open(j, c);
		}else{
			cout<<"You need ";
			 for(int n=0;n<j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"].size();n++){
				word = j["rooms"][findRoomNum(j, j["rooms"][roomindex][c])]["key"][n];
				cout<<"\""<<word<<"\" ";
			 }
			 cout<<"to enter."<<endl;
	}
    return j;
}
json changeEnemeyPosition(json j, clock_t time){
    int secounds = j["player"]["time"];
    if(int(clock()-time) >= secounds*1000){
        for(int n=0;n<j["enemies"].size();n++){
            if(j["enemies"][n]["move"]=="true"){
                j["enemies"][n]["initialroom"] = j["rooms"][random1()%j["rooms"].size()]["id"];
            }
        }
        time=clock();
    }
    return j;
}

void game(string introom, json j){
    json a;
    bool b;
    item *ptr;
    p.player_room = introom;
    string mtext, text, display, word, first_word;;
    auto word1 = j["rooms"][findRoomNum(j, j["rooms"][0]["n"])]["key"];
    roomindex = findRoomNum(j, p.player_room);
    int index1, index2, health;
    clock_t time = clock();
    //system("CLS");
    clrscr(os);
    display = j["rooms"][roomindex]["desc"];
    cout<<display<<endl;
    while(true){
        if(p.health<=0){
                cout<<p.health<<endl;
            cout<<"\t YOU DIED! \n";
            cout<<"\tGame  Over \n";
            break;
        }

        if(j["enemies"].size()==0){
            cout<<"congrats you killed all the enemies."<<endl;
            cout<<"\t--YOU WON--"<<endl;
            break;
        }
        if(j["player"]["time"]>0){
            j = changeEnemeyPosition(j, time);
        }

        cout<<">>";
        getline(cin, mtext);
		if (mtext == "")
			continue;
        text = mtext;
        trim(text);
        istringstream iss(text);
        iss >> first_word;
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        if(enemeyExist(j, "any", p.player_room)==1&&text!="save"&&first_word!="kill"&&text!= "quit"&&text !="list items"&&text != "help"){
            if(random1()%2==0 && enemeyExist(j,"any", p.player_room)==1){
                cout<<"enemy present in room attacked you, health -5"<<endl;
                p.change_health(-5);
                cout<<"\""<<text<<"\" command not executed.\n";
                continue;
            }

        }
        if(text == "quit"){
            break;
        }else if(text==""){
            continue;
        }
        else if(text== "help"){
			cout<<"In this game the player need to kill all the enemies in the map to win the game."<<endl;
			cout<<"The player can move to other rooms with the command \"go east\"(similarly for other directions).\n"<<endl;
			cout<<"\t\"describe\" prints the room name and describes about the it.\n\t\"look\" this command is used to know objects in the room."<<endl;
			cout<<"    \"take\" this command is used to pick items.\n\"about\" this is used to know about a object.\n";
			cout<<"\t\"consume\" this is used to consume any item they picked."<<endl;
			cout<<"\t\"list item\" this command lists all the items you picked.\n"<<endl;
			cout<<"Initialy player has 100 health points, when the player lost all the health points he loses the game."<<endl;
			cout<<"Player loses his health on passing through some rooms, or when he try to kill an enemy with out required equipments, or eating some uneatable things.And when you run a command there is a 50% chance that the enemie may attack you if you are in the same room as enemey"<<endl;
			cout<<"And to gain he has to consume food or some drinks.\n\"health\" shows your health."<<endl;
			cout<<"As said there are some enemies in the game,\"kill\"\t is the command used to kill the enemy.\n"<<endl;
			cout<<"Use \"quit\" command to quit the game.\n"<<endl;
			cout<<"At last \"save\" this is the command used to save the game process so that you can resume your game next time when you play."<<endl;

        }
        else if(text=="list items" || text == "ls"){
            cout<<"\n**<>--ITEMS PICKED--<>**"<<endl;
            p.print_items_in_inventory();
        }
        else if(text=="health"){
            cout<<"You health "<<p.health<<endl;
        }
        else if(text=="desc"||text=="describe"){
            cout<<"You are in "<<p.player_room<<endl;
            display = j["rooms"][roomindex]["desc"];
            cout<<display<<endl;
        }
        else if(text == "save"){
                cout<<"If you want to save this game, your previously saved game will be erased. Do you agree to this(y/n)? ";
                cin>>word;
            if(word == "y" || word == "Y"){
                ofstream file("resume.json");
                file << j;
                cout<<"Your game process is saved. Open resume.json to lode the game again."<<endl;
                break;
            }else if(word == "n" || word == "N"){
                continue;
            }else{
                cout<<"Invalid input.\n";
                cout<<"Type y for yes or n for no."<<endl;
            }
        }
        else if(first_word == "about"){
            text = removeWord(text, "about");
            text = trim(text);
            string word;
            for(int n=0;n<j["rooms"][roomindex]["obj"].size();n++){
                word = j["rooms"][roomindex]["obj"][n];
                if (word == text){
                    display = j["ob"][word][0];
                    cout<<display<<endl;
                }
            }
        }
        else if(first_word == "consume"){
            text = removeWord(text, "consume");
            text = trim(text);
            ptr = p.prev_items;
            if(p.health!= 100){
                if(p.prev_items != NULL){
					while(ptr != NULL){
						if(text == ptr->item_name){
							word = j["ob"][text][1];
							index2 = j["ob"][text][2];
							if(word == "eatable"){
								if(p.health+index2<100){
								p.change_health(index2);

								}else{
								p.health=100;
								}
								cout<<"consumed "<<text<<endl;
								cout<<"Your health "<<index2<<endl;
								break;
							}else if(word == "noteatable"){
								p.change_health(index2);
								cout<<"You eat some thing which you should not.\n";
								cout<<"Your health "<<index2<<endl;
							}
							break;
						}
						if(ptr->next == NULL){
							cout<<"You don't have "<<text<<"to eat";
							break;
						}
						ptr = ptr->next;
					}
                }else{
                    cout<<"you don't have "<<text<<"to eat."<<endl;
                }
            }else{
                cout<<"Your health is full."<<endl;
            }
        }
        else if(first_word == "take"){
            index2 = 1;
            text = removeWord(text, "take");
            text = trim(text);
            string word;
            if(text=="all"){
                for(int n=0;n<j["rooms"][roomindex]["obj"].size();n++){
                    word = j["rooms"][roomindex]["obj"][n];
                    p.add_item(word);
                    cout<<" Taken "<<word<<endl;
                }
            }else{
                for(int n=0;n<j["rooms"][roomindex]["obj"].size();n++){
                    word = j["rooms"][roomindex]["obj"][n];
                    if (word == text){
                         p.add_item(word);
                         j["rooms"][roomindex]["obj"].erase(n);
                         cout<<"Taken."<<endl;
                         index2 = 0;
                         break;
                    }
                }
                if(index2){
                    cout<<"There is no object with name \""<<text<<"\"\n";
                }
            }
        }else if(text == "cls"||text == "clear"){
            clrscr(os);
        }
        else if(text=="l"||text=="look"){
                if(j["rooms"][roomindex]["obj"].size()>1){
                    cout<<"Objects in the room are : ";
                    for(int n=0;n<j["rooms"][roomindex]["obj"].size();n++){
                        cout<<"\n>\t"<<j["rooms"][roomindex]["obj"][n]<<endl;
                    }
                }
                else if(j["rooms"][roomindex]["obj"].size()==1){
                    cout<<"Object in the room is : "<<j["rooms"][roomindex]["obj"][0]<<endl;
                }
                else{
                    cout<<"There are no objects found."<<endl;
                }
                 for(int n=0;n<j["enemies"].size();n++){
                     word = j["enemies"][n]["initialroom"];
                     if(p.player_room==word){
                        display = j["enemies"][n]["id"];
                        cout<<"There is a "<<display<< " here. And it is also moving"<<endl;
                     }
                 }

        }
        else if (first_word == "go"){
            text = removeWord(text, "go");
            text = trim(text);
            if(text == "e" || text =="east"){
                    if(j["rooms"][roomindex]["e"]!= ""){
                         word1 = j["rooms"][findRoomNum(j, j["rooms"][roomindex]["e"])]["key"];
                        if(word1.size() == 0){
                            j = open(j, "e");

                        }else{
                                j = keyRequired(j, "e");
                        }
                    }else{
                        cout<<"There is no way ahead"<<endl;
                    }
            }else if(text == "w" || text == "west"){
                if(j["rooms"][roomindex]["w"]!= ""){
                         word1 = j["rooms"][findRoomNum(j, j["rooms"][roomindex]["w"])]["key"];
                        if(word1.size()==0){
                            j = open(j, "w");
                        }else{
                            j = keyRequired(j, "w");
                        }
                }else{
                        cout<<"There is no way ahead"<<endl;
                }
            }else if(text == "n" || text == "north"){
                if(j["rooms"][roomindex]["n"]!= ""){
                    word1 = j["rooms"][findRoomNum(j, j["rooms"][roomindex]["n"])]["key"];
                    if(word1.size()==0){
                        j = open(j, "n");
                    }else{
                        j = keyRequired(j, "n");
                    }
                }else{
                cout<<"There is no way ahead"<<endl;

                    }
                    }else if(text == "s" || text == "south"){
                        if(j["rooms"][roomindex]["s"]!= ""){
                            word1 = j["rooms"][findRoomNum(j, j["rooms"][roomindex]["s"])]["key"];
                            if(word1.size()==0){
                                j = open(j, "s");
                            }else{
                                j = keyRequired(j, "s");
                            }
                        }else{
                        cout<<"There is no way ahead"<<endl;

                    }
                    }else{
                        cout<<text<<" is not a direction to go. Press help to get basic information."<<endl;
                    }
        }else if(first_word == "drop"){
            text = removeWord(text, "drop");
            text = trim(text);
            p.remove_item(text, "");
            a = {text};
            j["rooms"][roomindex]["obj"].insert(j["rooms"][roomindex]["obj"].end(),a.begin(), a.end());
        }
        else if(first_word == "kill"){
            text = removeWord(text, "kill");
            text = trim(text);
            index1 = enemeyExist(j, text, p.player_room);
            if (index1!= -1){
                b = true;
                for(int n=0;n<j["enemies"][index1]["killedby"].size();n++){
                    word = j["enemies"][index1]["killedby"][n];
                    ptr = p.prev_items;
                    if(p.prev_items == NULL){
                        b=false;
                        break;
                    }
                    //cout<<"6";
                    while(ptr != NULL){
                        if(word == ptr->item_name){
                            break;
                        }
                        if(ptr->next == NULL){
                            b=false;
                            break;
                        }
                        ptr = ptr->next;
                    }
                }
                if(b){
                    for(int n=0;n<j["enemies"][index1]["killedby"].size();n++){
                        word = j["enemies"][index1]["killedby"][n];
                        ptr = p.prev_items;
                        while(ptr != NULL){
                            if(word == ptr->item_name){
                                    if(j["ob"][word][3]=="con"){
                                        p.remove_item(ptr->item_name, "e");
                                    }
                                break;
                            }
                            ptr = ptr->next;
                        }
                }
                for(int n=0;n<j["enemies"].size();n++){
                        word = j["enemies"][n]["id"];
                        if (text==word){
                            j["enemies"].erase(n);
                            cout<<"You have killed "<<text<<endl;
                            break;
                        }
                    }

                }else{
                    p.change_health(-50);
                    b=false;
                    printRequired(j, index1);
                    cout<<text<<" attacked you, and you lost 50% of your health."<<endl;
                }
            }else{
                cout<<"There is no enemy with name \""<< text<<"\""<<endl;
            }
        }
        else{
            cout<<"I don't understand that"<<endl;
        }
    }
}
