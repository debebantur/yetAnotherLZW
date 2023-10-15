#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

void encode(string in_name, string out_name){
    char a;
    vector<char> phrase;
    unordered_map<string,int> table;
    int counter = 0;
    for(; counter<256; ++counter){
        string tem(1,char(counter));
        table[tem] = counter;
    }


    ofstream out;
       out.open(out_name, ios::out | ios::binary);
    ifstream in;
        in.open(in_name, ios::in | ios::binary);
        if(!in.eof()){
            in>>a;
            phrase.push_back(a);
        }
        else{
            cout<<"th! file is empty!!!"<<endl;
        }

        while(in.read((char *) &a, sizeof (a))){
            string cur(phrase.begin(), phrase.end());
            phrase.push_back(a);
            string tem(phrase.begin(), phrase.end());
            if(table.find(tem) == table.end()){
                out.write((char *) &table[cur], sizeof (table[cur]));
                table[tem] = counter;
                ++counter;
                phrase.clear();
                phrase.push_back(a);
            }
        }
        string tem(phrase.begin(), phrase.end());
        out.write((char *) &table[tem], sizeof (table[tem]));

    in.close();
    out.close();
}

void decode(string in_name, string out_name){
    vector<string> table;
    unordered_map<string, int> exists;
    for(int i=0; i<256; ++i){
        string tem(1,char(i));
        table.push_back(tem);
    }

    ifstream in;
    ofstream out;
       out.open(out_name);
    string phrase;
    int h;
        in.open(in_name, ios::in | ios::binary);

        if(in){
            in.read((char *) &h, sizeof (h));
            out<<table[h];
            phrase = table[h];
        }
        else{
            cout<<"th! file is empty!!!"<<endl;
        }

        while(in.read((char *) &h, sizeof (h))){
            if(table.size()<=h){
                phrase+= phrase[0];
                //out.write((char *) &phrase, sizeof (phrase));
                out<<phrase;
                if(exists.find(phrase) == exists.end()){
                    ++exists[phrase];
                    table.push_back(phrase);
                }
                //phrase = phrase[0];
            }
            else{
                //out.write((char *) &table[h], sizeof (table[h]));
                out<<table[h];
                phrase+= table[h][0];
                if(exists.find(phrase) == exists.end()){
                    ++exists[phrase];
                    table.push_back(phrase);
                }
                phrase = table[h];
            }
        }

    in.close();
    out.close();
}

int main()
{
    string in_name = "input.txt", out_name = "output.txt";
    encode(in_name, out_name);

    cout<<"encoded"<<endl;

    decode(out_name, "newout.txt");

    cout<<"ping"<<endl;
    cout<<sizeof(char)<<endl;
    return 0;
}
