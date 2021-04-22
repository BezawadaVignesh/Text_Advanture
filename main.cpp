#include <dirent.h>
#include <cstring>
#include <iostream>
#include <vector>
#include <memory>
#include<stdlib.h>
#include"game.cpp"
#include"json.hpp"


string checkForJson(const std::string &s)
{
    string word ="";
    for (char const &c: s) {
        if(c == '.' || word!=""){
            word = word + c;
        }
    }
    return word;
}

namespace {
std::vector<std::string> GetDirectoryFiles(const std::string& dir) {
  std::vector<std::string> files;
  std::shared_ptr<DIR> directory_ptr(opendir(dir.c_str()), [](DIR* dir){ dir && closedir(dir); });
  struct dirent *dirent_ptr;
  std::string ext;
  if (!directory_ptr) {
    std::cout << "Error opening : " << std::strerror(errno) << dir << std::endl;
    return files;

  }

  while ((dirent_ptr = readdir(directory_ptr.get())) != nullptr) {
        ext = std::string(dirent_ptr->d_name);
        ext = checkForJson(std::string(dirent_ptr->d_name));
        if(ext==".json" && std::string(dirent_ptr->d_name) != "resume.json"){
            files.push_back(std::string(dirent_ptr->d_name));
        }
  }

  return files;
}
}
int main() {
    std::string input, ext, introom, os;
    json j;
	os = checkForOs();
    while(1){
        try{
            std::ifstream fle1("resume.json");
            fle1>>j;
            cout<<"You have a resumed game do you want to continue or a new game (n/r)? ";
            std::cin>>input;
            if(input=="n"){
                throw -1;
            }else if(input =="r"){
                ext = "resume.json";
            }else{
                cout<<"Type n to new and r to resume.";
                continue;
            }
        }catch(...){
                int num=0;
                cout<<"\t\t    Welcome to"<<endl;
                cout<<"\t\tText Adventure Game\n"<<endl;

                cout<<"Maps in you directory are: "<<endl;
                const auto& directory_path = std::string(".");
                const auto& files = GetDirectoryFiles(directory_path);
                for (const auto& file : files) {
                    ++num;
                    std::cout<<num<<". ";
                    std::cout << file << std::endl;
                    }
                try{
                    std::cin>>num;
                    ext = files.at(num-1);
                }
                catch(const std::out_of_range &ex){
                    std::cout<<"Invalid input."<<endl;
                    continue;
                    }
        }
            try{
                ifstream fle(ext);
                fle>>j;
            }catch(...){
                std::cout<<"Error while opening the file."<<endl;
            }
            clrscr(os);
            introom = j["player"]["initialroom"];
            std::cout<<"You are playing "<<ext<<endl;
            system("pause");
            game(introom, j);
            std::cout<<"Do you want to play again(y/n)?"<<endl;
            std::cin>>ext;
            if(ext=="y"||ext=="Y"){
                continue;
            }else{
                break;
            }
        }

  return 0;
}

