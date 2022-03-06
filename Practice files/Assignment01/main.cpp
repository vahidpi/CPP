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
    Note searchByTitle(/*fill in*/);
    Note searchByText(/*fill in*/);
    Note searchByTag(/*fill in*/);

private:
//    std::map<string,Note *> TitalMap;
//    std::map<string,Note *> TextMap;
//    std::map<string,std::vector<Note *> > TagsMap;
    /*fill in*/
    vector<Note> noteLists;
    int noteIndex(string title);
};


void Storyboard::addNote(string title, string text, vector<string> tags){
    //Note *note = new Note(title,text,tags);
    Note note(title,text,tags);
    noteLists.push_back(note);

//   TitalMap[note->Tital] = note;
//   TextMap[note->Text] = note;

//   for (auto it = note->vec.begin(); it != note->vec.end(); ++it){
//       //check that is tags already
//       auto it_v = TagsMap.find(*it);
//       if (it_v != TagsMap.end()){
//           it_v->second. push_back(note);
//       } else {
//           vector<Note *> &v = TagsMap[*it];
//           v.push_back(note);
//       }
//    }
}

void Storyboard::deleteNote(string title){
    //noteLists[1].title
    int index=noteIndex(title);
    cout<<index;
//    if(index)
//        noteLists.erase()
//    esle
//        cout<<"Not found";
}

int Storyboard::noteIndex(string title){
    int index=0;
    for (unsigned int i=0;i<noteLists.size();i++) {
        if(noteLists[i].title==title){
            index=0;
        }
    }
    return index;
}


int main()
{
    cout << "Start" << endl;

    return 0;
}
