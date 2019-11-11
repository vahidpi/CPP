#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User
{
    /* We have users which have a name, an age, a height (in cm), a set of hobbies,
     * an entry whether they are male or female, an internal ID and a set of friends.*/
public:
    string name;
    short int age;
    short int height;
    bool gender;
    long id;
    vector<User*>friends;
    vector<string>hobbies;
    User(string newName,short int newAge,short int newHeight,bool newGender,long newId,vector<User*>newFriends,vector<string>newHobbies){
        name=newName;
        age=newAge;
        height=newHeight;
        gender=newGender;
        id=newId;
        friends=newFriends;
        hobbies=newHobbies;
    }
    User(){
        name="\0";
        age=0;
        height=0;
        gender=0;
        id=0;
        friends={nullptr};
        hobbies={""};
    }
};

class SocialNetwork
{
public:
    void addUser(string name,short int age,short int height,bool gender,vector<User*>friends,vector<string>hobbies);
    void deleteUser(long id);
    void addFriend(long id,long friendId);
    User* searchUserById(long id);
    vector<User*> searchUserByName(string name);
    vector<User*> searchUserByAge(short int age);
    vector<User*> searchUserByHobbies(string hobbie);
    vector<User*> getFriendsOfUser(long id);

private:
    vector<User> usersList;
    int userIndex(long id);
    int userIndex(string name);
    long getMaxId();
};


void SocialNetwork::addFriend(long id,long friendId){
    int index=userIndex(id);
    int friendIndex=userIndex(friendId);
    if(index>-1)
    {
        usersList[static_cast<unsigned long>(index)].friends.push_back(&usersList[static_cast<unsigned long>(friendIndex)]);
    }
}

User* SocialNetwork::searchUserById(long id){
    int index=userIndex(id);
    if(index>-1)
    {
        return &usersList[static_cast<unsigned long>(index)];
    }else{
        cout<<"User not found!"<<endl;
        return nullptr;
    }
}


vector<User*> SocialNetwork::searchUserByName(string name){
    vector<User*> namelist;

    for (unsigned int i=0;i<usersList.size();i++) {
        if(usersList[i].name==name){
            namelist.push_back(&usersList[i]);
        }
    }

    if(!namelist.empty())
    {
        return namelist;
    }else{
        cout<<"User with '"<<name<<"' name not found!"<<endl;
        return namelist;
    }
}

vector<User*> SocialNetwork::getFriendsOfUser(long id){
    int index=userIndex(id);
    if(!usersList[static_cast<unsigned long>(index)].friends.empty())
    {
        return usersList[static_cast<unsigned long>(index)].friends;
    }else{
        cout<<"User with '"<<id<<"' id doesn't have friend!"<<endl;
        return {nullptr};
    }
}

vector<User*> SocialNetwork::searchUserByAge(short int age){
    vector<User*> namelist;

    for (unsigned int i=0;i<usersList.size();i++) {
        if(usersList[i].age==age){
            namelist.push_back(&usersList[i]);
        }
    }

    if(!namelist.empty())
    {
        return namelist;
    }else{
        cout<<"User with '"<<age<<"' age not found!"<<endl;
        return namelist;
    }
}

vector<User*> SocialNetwork::searchUserByHobbies(string hobbie){
    vector<User*> namelist;

    for (unsigned int i=0;i<usersList.size();i++) {
        for (unsigned int j=0;j<usersList.size();j++) {
            if(usersList[i].hobbies[j]==hobbie){
                namelist.push_back(&usersList[i]);
            }
        }
    }

    if(!namelist.empty())
    {
        return namelist;
    }else{
        cout<<"User with '"<<hobbie<<"' hobbie not found!"<<endl;
        return namelist;
    }
}

void SocialNetwork::deleteUser(long id){
    int index=userIndex(id);
    if(index>-1)
    {
        usersList.erase(usersList.begin()+index);
        cout<<"User was deleted successfully."<<endl;
    }else
        cout<<"User not found!"<<endl;
}

long SocialNetwork::getMaxId(){
    long t1=0;
    if(!usersList.empty()){
        t1=usersList[0].id;
        for (unsigned int i=0;i<usersList.size();i++)
            if (usersList[i].id>t1)
                t1=usersList[i].id;
    }
    return t1;
}
int SocialNetwork::userIndex(string name){
    int index=-1;
    for (unsigned int i=0;i<usersList.size();i++) {
        if(usersList[i].name==name){
            index=static_cast<int>(i);
        }
    }
    return(index);
}


int SocialNetwork::userIndex(long id){
    int index=-1;
    for (unsigned int i=0;i<usersList.size();i++) {
        if(usersList[i].id==id){
            index=static_cast<int>(i);
        }
    }
    return(index);
}


void SocialNetwork::addUser(string name,short int age,short int height,bool gender,vector<User*>friends,vector<string>hobbies){
    long id=getMaxId()+1;

    if (!name.empty()){
        User user(name,age,height,gender,id,friends,hobbies);
        usersList.push_back(user);
        cout<<"User was created successfully."<<endl;
    } else {
        cout<<"Name can not be empty!"<<endl;
    }
}


bool Test_SearchUserByName(){

    // Make object and assign
    SocialNetwork sn;
    sn.addUser("Vahid",36,170,1,{nullptr},{"reading","photography"});
    sn.addUser("Lauri",40,170,1,{nullptr},{"ski","reading"});

    sn.addFriend(1,2);

    if (sn.searchUserByName("Reza").empty())
        return true;
    else
        return false;
}

int main()
{
    cout << "Start!" <<endl;


    if(Test_SearchUserByName())
        cout<<endl<<"Test_SearchUserByName passed successfully."<<endl;
    return 0;
}
