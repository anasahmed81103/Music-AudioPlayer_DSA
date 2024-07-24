#include<iostream>
#include<Windows.h>
#include<mmsystem.h>
#include<conio.h>
#include<fstream>
#include<string>
#include<queue>
#include<stdio.h>
#include <limits>

#pragma comment(lib,"winmm.lib")

using namespace std;


class music {   //music nodes class for all activities (tree,linkedlist,hash etc.)

public:

    string name;
    string artist;
    string sname;
    wstring wname;
    music* next;
    music* left;
    music* right;
    int  height;

    music(string a, string b, string c) {

        name = a;
        artist = b;
        sname = c;
        //wstring is req. for music

        wstring w(name.begin(), name.end());

        wname = w;

        next = NULL;
        left = NULL;
        right = NULL;

    }
    music() {

    }
    string getname() {

        return name;

    }

    wstring getmusic() {

        return wname;

    }


    string getart() {

        return artist;

    }

    string getsearch() {

        return sname;

    }


};

bool play(music*);


///////////////////////HASHING////////////////////////////
class hashname {

public:

    string name;
    hashname* next;
    hashname(string n) {
        name = n;
        next = NULL;
    }

};


class hashinglist {

public:

    hashname* head;

    hashinglist() {

        head = new hashname("Billie Eilish");
        head->next = new hashname("Alan Walker");
        head->next->next = new hashname("Eminem");
        head->next->next->next = new hashname("Aleyna Tilki");
        head->next->next->next->next = new hashname("Ava Max");
        head->next->next->next->next->next = new hashname("Fifth Harmony");
        head->next->next->next->next->next->next = new hashname("NCS Release");
        head->next->next->next->next->next->next->next = new hashname("Disney");
        head->next->next->next->next->next->next->next->next = new hashname("Coke Studios");
        head->next->next->next->next->next->next->next->next->next = new hashname("BTS");

    }
    void insert(string s) {

        hashname* tmp = new hashname(s);
        hashname* tail = head;
        while (tail->next != NULL) {
            tail = tail->next;
        }
        tail->next = tmp;

    }

};


class HashMap {

private:

    music** htable;
    int size;
    int max;

public:

    hashinglist hl;

    HashMap() {
        size = 0;
        max = 100;
        htable = new music * [max];
        for (int i = 0; i < max; i++)
            htable[i] = NULL;
    }


    int getindex(string s) {

        int i = 0;
        hashname* tmp = hl.head;
        while (tmp != NULL) {
            if (s == tmp->name) {
                return i;
            }
            i++;
            tmp = tmp->next;
        }
        hl.insert(s);
        return i;

    }


    void insert(string s, string a, string sn) {

        int i = getindex(a);
        music* tmp = new music(s, a, sn);

        if (htable[i] == NULL) {
            htable[i] = tmp;
        }
        else {
            music* temp = htable[i];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = tmp;
        }

        size++;

    }


    void enter() {

        fstream f;

        f.open("allsongs.txt", ios::in);

        string s;
        string a, b, c;
        int i = 1;

        while (getline(f, s)) {

            if (i == 1) {
                a = s;
            }
            else if (i == 2) {
                b = s;
            }
            else if (i == 3) {
                c = s;
            }

            if (i == 3) {
                insert(a, b, c);
                i = 0;
            }

            i++;
        }

        f.close();

    }


    void searchAndDisplay(string key) {

        int i = getindex(key);

        if (i == -1) {
            cout << "Artist not found in the database." << endl;
            return;
        }

        if (htable[i] == NULL) {
            cout << "No songs exist for such artist" << endl;
        }
        else {

            music* head = NULL;
            music* it=head;
            music* temp = htable[i];
            int k = 1;
            int i = 1;
            while (temp != NULL) {

                if (temp->getart() == key) {

                    cout << "Song Name " << k << ": " << temp->getname() << endl;

                    if (head == NULL) {
                        head = new music (temp->getname(),temp->getart(),temp->getsearch() );
                        it = head;
                    }
                    else {
                        music* tmp = new music(temp->getname(), temp->getart(), temp->getsearch());
                        it->next = tmp;
                        it = it->next;
                        it->next = head;
                    }

                    k++;
                }
                temp = temp->next;
            }

            cout << "choice index : ";
            int j;
            cin >> j;
            j--;

            i = 0;
            it = head;

            while (i != j) {

                it = it->next;
                i++;
            }


            while (true) {

                bool a = play(it);

                if (!a) {
                    break;
                }
                it = it->next;

            }


        }


    }


};



bool play(music* m);
void setVolume(UINT volumeLevel);


class mainlist {      //the main list of songs in which songs are added through file or insert method by writing song name and artist

public:

    music* head;
    music* tail;

    mainlist() {
        head = NULL;
        tail = NULL;
    }

    void insert(string a, string b, string c) {     //inserts song in list (LL) and also file of all songs along with the artist in next line

        music* tmp = new music(a, b, c);

        if (head == NULL) {
            head = tmp;
            tail = tmp;
            tail->next = head;
        }
        else {

            tail->next = tmp;
            tail = tail->next;
            tail->next = head;

        }

        fstream f;

        f.open("allsongs.txt", ios::app);

        f << tmp->getname() << endl << tmp->getart() << endl << tmp->getsearch() << endl;

        f.close();

    }


    void insertsv(string a, string b, string c) {         //insert function used to put data in list from file and not insert it back into file again (used with readfromfile func.)

        music* tmp = new music(a, b, c);

        if (head == NULL) {
            head = tmp;
            tail = tmp;
            tail->next = head;
        }
        else {

            tail->next = tmp;
            tail = tail->next;
            tail->next = head;

        }

    }


    void deletet(string a) {

        music* tmp;

        if (head->getname() == a) {
            tmp = head;
            head = head->next;
            tail->next = head;
            delete tmp;
        }
        else {

            music* it = head;

            while (it->next != head) {

                if (it->next->getname() == a) {

                    tmp = it->next;
                    it->next = tmp->next;
                    delete tmp;
                    break;
                }

                it = it->next;

            }

        }


    }


    void readfromfile() {           //loads list from file of all songs

        fstream f;

        f.open("allsongs.txt", ios::in);

        string s;
        string a, b, c;
        int i = 1;

        while (getline(f, s)) {

            if (i == 1) {
                a = s;
            }
            else if (i == 2) {
                b = s;
            }
            else if (i == 3) {
                c = s;
            }

            if (i == 3) {
                insertsv(a, b, c);
                i = 0;
            }

            i++;
        }

        f.close();

    }


    void selectnplay() {    //displays a list of all songs and gives choice to play any

        int i = 0;

        music* it = head;

        cout << "ALL MUSICS:" << endl << "====================" << endl;

        do {

            cout << i + 1 << " ) " << it->getname() << endl;
            i++;
            it = it->next;

        } while (it != head);


        cout << "choice index : ";
        int j;
        cin >> j;
        j--;

        i = 0;
        it = head;

        while (i != j) {

            it = it->next;
            i++;
        }


        while (true) {

            bool a = play(it);

            if (!a) {
                break;
            }
            it = it->next;

        }


    }

    void playall() {     //plays the whole list 

        music* it = head;

        while (it->next != head) {

            bool a = play(it);

            if (!a) {
                break;
            }

            it = it->next;

        }

    }

    void playnloop() {    //similar to play all but it does not stop when the list ends, instead it starts again from the first

        music* it = head;

        while (true) {

            bool a = play(it);

            if (!a) {
                break;
            }

            it = it->next;


        }

    }

};

class PlayList {

public:

    int maxval(int a, int b) {
        return (a > b) ? a : b;
    }

    int get_height(music* m) {
        if (m == NULL) {                                        // avl supported functions
            return 0;
        }
        return m->height;
    }
    int get_balance(music* m) {

        return get_height(m->left) - get_height(m->right);

    }

    music* Right_Rotate(music* m) {                         // right rotation of avl
        music* x = m->left;
        music* t = x->right;

        x->right = m;
        m->left = t;

        m->height = maxval(get_height(m->left), get_height(m->right)) + 1;

        x->height = maxval(get_height(x->left), get_height(x->right)) + 1;

        return x;
    }

    music* Left_Rotate(music* m) {                       // left rotation of avl
        music* x = m->right;
        music* t = x->left;

        x->left = m;
        m->right = t;

        m->height = maxval(get_height(m->left), get_height(m->right)) + 1;

        x->height = maxval(get_height(x->left), get_height(x->right)) + 1;

        return x;
    }


    music* insert_playlist(music* m, string song, string artist, string sname) {          // song insertion function in AVL
        if (m == NULL) {
            m = new music(song, artist, sname);
            return m;
        }
        if (song < m->getname()) {
            m->left = insert_playlist(m->left, song, artist, sname);

        }
        else if (song > m->getname()) {
            m->right = insert_playlist(m->right, song, artist, sname);

        }
        else {
            return m;
        }

        m->height = maxval(get_height(m->left), get_height(m->right)) + 1;

        int bal = get_balance(m);

        if (bal > 1 && song < m->left->getname()) {
            m = Right_Rotate(m);
            return m;
        }

        if (bal < -1 && song > m->right->getname()) {
            m = Left_Rotate(m);
            return m;
        }

        if (bal > 1 && song > m->left->getname()) {
            m->left = Left_Rotate(m->left);
            m = Right_Rotate(m);
            return m;
        }

        if (bal < -1 && song < m->right->getname()) {
            m->right = Right_Rotate(m->right);
            m = Left_Rotate(m);
            return m;
        }
        return m;
    }

    music* getmin(music* m) {
        music* tmp = m;
        while (tmp != NULL) {
            tmp = tmp->left;
        }
        return tmp;
    }

    music* remove_music(music* m, string song, string artist, string sname) {           //remove music func
        if (m == NULL) {
            return m;
        }
        if (song < m->getname()) {
            m->left = remove_music(m->left, song, artist, sname);
        }

        if (song > m->getname()) {
            m->right = remove_music(m->right, song, artist, sname);
        }
        else {
            if (m->left == NULL && m->right == NULL) {
                delete m;
                return NULL;
            }

            if (m->left == NULL && m->right != NULL) {
                music* tmp = m->right;
                delete m;
                return tmp;
            }

            if (m->left != NULL && m->right == NULL) {
                music* tmp = m->left;
                delete m;
                return tmp;
            }
            if (m->left != NULL && m->right != NULL) {

                string minval = getmin(m->right)->name;
                m->name = minval;

                m->right = remove_music(m->right, minval, artist, sname);
                return m;

            }

        }
        if (m == NULL) {
            return m;
        }
        m->height = 1 + maxval(get_height(m->left), get_height(m->right));

        int bal = get_balance(m);

        if (bal > 1 && get_balance(m->left) >= 0) {

            return Right_Rotate(m);
        }

        if (bal > 1 && get_balance(m->left) < 0) {

            m->left = Left_Rotate(m->left);
            return Right_Rotate(m);
        }

        if (bal < -1 && get_balance(m->right) <= 0) {
            return Left_Rotate(m);

        }

        if (bal < -1 && get_balance(m->right)>0)
        {
            m->right = Right_Rotate(m->right);

            return Left_Rotate(m);


        }
        return m;

    }



    void Sorted_music_player(music* m) {                              //function to play music accroding to song name sorted order

        if (m == NULL) {
            return;
        }

        Sorted_music_player(m->left);
        cout << "\n ____________NOW PLAYING___________  \n   ";
        play(m);
        Sorted_music_player(m->right);
    }


    void shuffled_music_player(music* m) {                             //shuffled play music funtion and it plays music in postorder
        if (m == NULL) {
            return;
        }

        Sorted_music_player(m->left);
        Sorted_music_player(m->right);
        cout << "\n ____________NOW PLAYING___________  \n   ";
        play(m);

    }
};

static int plnum;

void display_playlist(music* m) {                        //global func display the playlist created by AVL

    cout << "\n---------------------------------PLAYLIST NO : " << plnum + 1 << " ------------------------------\n ";
    cout << "\nSONG NAME                                                             Artist NAME \n";
    cout << "-------------------------------------------------------------------------------------\n";

    plnum++;
    queue<music*> q;
    q.push(m);

    while (!q.empty()) {
        music* tmp = q.front();
        q.pop();
        cout << endl << "  " << tmp->name << "                                     " << tmp->artist;


        if (tmp->left) {
            q.push(tmp->left);
        }
        if (tmp->right) {
            q.push(tmp->right);
        }


    }
}

void Create_Smart_PlayList(mainlist a2) {                   //global  function to create playlists using AVL tree of user choice

    music* m = a2.head;

    int i = 0;
    cout << "ALL MUSICS:" << endl << "====================" << endl;

    do {

        cout << i + 1 << "  " << m->getname() << endl;
        i++;
        m = m->next;

    } while (m != a2.head);




    // creating playlist 
    int max = 20;
    int n;
    cout << "\nYou can create upto  " << max << " playlists\n";
    cout << "\n How many number of playlists you want to create ??\n";
    cin >> n;
    if (n <= max) {

        PlayList* pl = new PlayList[max];

        music** mroot = new music * [max];
        for (int i = 0; i < max; i++) {
            mroot[i] = NULL;
        }

        ofstream playlistNamesFile("playlistnames.txt", ios::app);
        if (!playlistNamesFile.is_open()) {
            cerr << "Error opening playlistnames.txt" << endl;
            return;
        }

        int k;
        char chr;
        for (int k = 0; k < n; k++) {
            string fileName;
            cout << "Enter the name of the Playlist you want to create: ";
            cin >> fileName;

            playlistNamesFile << fileName << endl;

            ofstream outFile(fileName.c_str(), ios::app); // Creating the file in write mode

            do {
                cout << "\n==> SELECT SONG To add in playlist  " << k + 1 << " from the given list only";

                cout << "\nselect index  from given options: \n";
                int j;
                cin >> j;
                j--;

                i = 0;
                m = a2.head;

                while (i != j) {

                    m = m->next;
                    i++;
                }



                outFile << m->name << endl;
                outFile << m->artist << endl;
                outFile << m->sname << endl;



                mroot[k] = pl[k].insert_playlist(mroot[k], m->name, m->artist, m->sname);

                cout << "\nYou want to add another song in playlist ?? [PRESS Y or y]\n";
                cin >> chr;
            } while (chr == 'y' || chr == 'Y');
            outFile.close();
        }

        playlistNamesFile.close();

        for (int k = 0; k < n; k++) {
            display_playlist(mroot[k]);                                     //display of all playlist that you create
        }


        // prompting user to play lists in sorted or shuffled order
        char chh;
        do {
            cout << "\nDO you want to play the songs of playlists created ??\n";
            cout << "\n----> PRESS s/S to play in playlist in SORTED order\n ---->PRESS h/H to play playlist in SHUFFLED Order\n";
            char cho2;
            cin >> cho2;
            if (cho2 == 's' || cho2 == 'S') {
                int x;
                cout << "\nEnter playlist num index to play in SORTED ORDER\n";
                cin >> x;
                x--;
                pl->Sorted_music_player(mroot[x]);
            }
            else if (cho2 == 'h' || cho2 == 'H') {
                int y;
                cout << "\nEnter playlist num index to play in SHUFFLED ORDER\n";
                cin >> y;
                y--;
                pl->Sorted_music_player(mroot[y]);
            }
            cout << "\nYou want another playlist to play ??[PRESS Y or y]\n";
            cin >> chh;

        } while (chh == 'y' || chh == 'Y');

        return;
    }
    else {
        cout << "\nLimit of num of playlists exceeded !!";
    }

}


void load_smart_playlist() {

    fstream f;
    f.open("playlistnames.txt", ios::in);

    const int max = 20;
    string arr[max];
    int i = 0;

    while (getline(f, arr[i]) && i < max) {
        cout << i + 1 << ") " << arr[i] << endl;
        i++;
    }
    f.close();

    int k;
    cout << "Enter index number of playlist to play: ";
    cin >> k;

    if (k > i || k < 1) {
        cout << "Invalid entry" << endl;
        return;
    }

    string filename = arr[k - 1];

    PlayList pl;  // Creating a single PlayList object instead of an array
    music* mroot = nullptr;  // Playlist root pointer

    f.open(filename, ios::in);

    string n, a, sn;
    i = 0;  // Resetting index

    while (getline(f, sn)) {
        if (i == 0) {
            n = sn;
        }
        else if (i == 1) {
            a = sn;
        }
        else if (i == 2) {
            mroot = pl.insert_playlist(mroot, n, a, sn);
            i = -1;
        }
        i++;
    }

   
    

    f.close();

    display_playlist(mroot);

    cout <<endl<< "Want to play play list?? (y/n) :";
    char cho; cin >> cho;
    if (cho == 'y' || cho == 'Y') {
        while (cho=='y' || cho=='Y') {
            pl.shuffled_music_player(mroot);
            cout << "keep playing? ";
            cin >> cho;
        }
        
        
    }

}


void search(mainlist m) {

    cout << "Are you confident in your spelling (i.e. writing song name with proper spaces and upper case/lower case) : ";
    char cho; cin >> cho;
    if (cho == 'y' || cho == 'Y') {

        cout << endl << "enter song name : ";
        string a;
        cin >> ws;
        getline(cin, a);
        int i = 0;

        music* it = m.head;
        while (it->next != m.head) {
            if (it->getname() == a) {
                cout << endl << "FOUND!!" <<endl;
                play(it);
                i++;
                break;
            }
            it = it->next;
        }
        if (i == 0) {
            cout << endl<<"Not found!"<<endl;
        }
        

    }
    else {

        cout << endl << "enter song name without any gaps and capital letters : ";
        string a;
        cin >> ws;
        getline(cin, a);
        int i = 0;

        music* it = m.head;
        while (it->next != m.head) {
            if (it->getsearch() == a) {
                cout << endl << "FOUND!!" << endl;
                play(it);
                i++;
                break;
            }
            it = it->next;
        }
        if (i == 0) {
            cout << endl << "Not found!" << endl;
        }

    }


}







void setVolume(UINT volumeLevel) {     //to increase or decrease volume of song by a specific amount
    DWORD volume = ((DWORD)volumeLevel << 16) + (DWORD)volumeLevel;
    waveOutSetVolume(NULL, volume);
}


bool play(music* a) {         //the king play function which takes a music class object pointer as argument and does the magic u want

    PlaySound(a->getmusic().c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    cout << endl << "PLAYING : " << a->getname() << "        "<<a->getart() << endl << "=================================================" << endl << endl;

    cout << "Press 'p' to pause \n 'r' to resume \n 'n' for next \n 'q' for quit \n '+' to increase volume \n '-' to decrease volume" << endl;

    while (true) {
        char ch = _getch();

        switch (ch) {

        case 'p':
            PlaySound(NULL, NULL, 0);
            break;
        case 'r':
            PlaySound(a->getmusic().c_str(), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;
        case 'q':
            PlaySound(NULL, NULL, 0);
            return false;
            break;
        case 'n':
            return true;
            break;
        case '+':
            setVolume(0xFFFF);
            break;
        case '-':
            setVolume(0x8000);
            break;
        default:
            cout << "Invalid choice. Press 'p' to pause, 'r' to resume, or 'q' to quit." << endl;

        }

    }

    return true;

}

int main() {

    cout << "\nWELCOME TO AIZ MUSIC PLAYER !!!\n";
    char opt;


    mainlist a;
    PlayList p;

    a.readfromfile();

    HashMap hm;
    hm.enter();



    do {
        cout << "\nSELECT OPTION FROM GIVEN MENU\n";

        cout << "\n------------------------ MENU ---------------------------\n";

        cout << "\n (O) Press 1 to Play ALL MUSIC in your album";

        cout << "\n (O) Press 2 for select and Play MUSIC from all of your choice";

        cout << "\n (O) Press 3 to Play music album non stop  *(starts again over when album ends)";

        cout << "\n (O) Press 4 to create SMART playlist to store all your songs";

        cout << "\n (O) Press 5 to view created SMART playlist ";

        cout << "\n (O) Press 6 to search an artist and play play his songs";

        cout << "\n (O) Press 7 to search any song and play his songs";

        cout << "\n (O) Press 8 to add new song in mainlist ";

        cout << endl<<"  ";

        int cho;
        cin >> cho;
        if (cho == 1) {
            a.playall();
        }
        else if (cho == 2) {

            a.selectnplay();
        }
        else if (cho == 3) {
            a.playnloop();
        }
        else if (cho == 4) {
            Create_Smart_PlayList(a);
        }
        else if (cho == 5) {
            load_smart_playlist();
        }
        else if (cho == 6) {
            cout << endl << "enter artist name : ";
            string a;
            cin >> ws;
            getline(cin, a);
            hm.searchAndDisplay(a);
        }
        else if (cho == 7) {
            search(a);
        }
        else if (cho == 8) {
            string s, b, c;
            cout << endl << "enter song name : ";
            cin >> ws;
            getline(cin, s);
            cout << endl << "enter artist name : ";
            cin >> ws;
            getline(cin, b);
            cout << endl << "enter a simplified form of song name (without gaps and uppeercase) : ";
            cin >> c;
            a.insert(s, b, c);
        }
        else {
            cout << "\nWRONG OPTION SELECTED\n";
        }

        cout << "\nYou want to perform another action ??  [PRESS y OR Y]\n";
        cin >> opt;
    } while (opt == 'y' || opt == 'Y');


    cout << "\n---------------------------------------THANK YOU-----------------------------------";




}