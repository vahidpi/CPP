#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Note
{
public:
    /*Every note has a title, a text and a set of tags.*/
    string title;
    string text;
    vector<string> tags;
    Note(string titleAssign, string textAssign,vector<string> tagsAssign){
        title=titleAssign;
        text=textAssign;
        tags=tagsAssign;
    }
};

class Storyboard
{
public:
    void addNote(string title,string text,vector<string> tags);
    void deleteNote(string title);
    Note* searchByTitle(string title);
    Note* searchByText(string text);
    Note* searchByTag(string tag);


private:
    vector<Note> noteLists;
    int noteIndex(string title);

};

void Storyboard::addNote(string title, string text, vector<string> tags){
    Note note(title,text,tags);
    noteLists.push_back(note);
    cout<<"Note was created successfully."<<endl;
}

Note* Storyboard::searchByTitle(string title){
    int index=noteIndex(title);

    if(index>-1){
        return &noteLists[static_cast<unsigned long>(index)];
    } else {
        cout<<"Note not found!"<<endl;
        return nullptr;
    }
}

Note* Storyboard::searchByTag(string tag){
    int index=-1;

    for (unsigned int i=0;i<noteLists.size();i++) {
        for (unsigned int j=0;j<noteLists[i].tags.size();j++)
        {
            if(noteLists[i].tags[j]==tag){
                index=static_cast<int>(i);
            }
        }
    }

    if(index>-1)
    {        
        return &noteLists[static_cast<unsigned long>(index)];
    } else {
        cout<<"Note not found!"<<endl;
        return nullptr;
    }
}

Note* Storyboard::searchByText(string text){
    int index=-1;
    for (unsigned int i=0;i<noteLists.size();i++) {
        if(noteLists[i].text==text){
            index=static_cast<int>(i);
        }
    }
    if(index>-1)
    {
        return &noteLists[static_cast<unsigned long>(index)];
    } else {
        cout<<"Note not found!"<<endl;
        return nullptr;
    }
}


void Storyboard::deleteNote(string title){
    int index=noteIndex(title);
    if(index>-1){
        noteLists.erase(noteLists.begin()+index);
        cout<<"Note was deleted successfully."<<endl;
    } else
        cout<<"Note not found";
}

int Storyboard::noteIndex(string title){
    int index=-1;
    for (unsigned int i=0;i<noteLists.size();i++) {
        if(noteLists[i].title==title){
            index=static_cast<int>(i);
        }
    }
    return(index);
}

bool Test_SearchByText(){

    // Make object and assign
    Storyboard sb;
    sb.addNote("title1","text1",{"tag1_1","tag1_2"});
    sb.addNote("title2","text2",{"tag2_1","tag2_2"});
    sb.addNote("title3","text3",{"tag3_1","tag3_2"});
    sb.addNote("title4","text4",{"tag4_1","tag4_2"});



    if (sb.searchByText("blabla"))
        return true;
    else
        return false;
}

int main()
{
    cout << "Start" << endl;

    if(!Test_SearchByText())
            cout<<endl<<"Test_SearchByText passed successfully."<<endl;

    return 0;
}
