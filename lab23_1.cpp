#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>
using namespace std;
char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}
string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}
void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    string line;
    while(getline(file, line)){
        int colonPos = line.find(':');
        string name = line.substr(0, colonPos);
        string scoresPart = line.substr(colonPos + 2);
        int s1, s2, s3;
        sscanf(scoresPart.c_str(), "%d %d %d", &s1, &s2, &s3);
        int total = s1 + s2 + s3;
        names.push_back(name);
        scores.push_back(total);
        grades.push_back(score2grade(total));
    }
    file.close();
}
void getCommand(string& command, string& key){
    cout << "Please input your command:\n";
    string line;
    getline(cin, line);
    int spacePos = line.find(' ');
    if(spacePos == (int)string::npos){
        command = line;
        key = "";
    } else {
        command = line.substr(0, spacePos);
        key = line.substr(spacePos + 1);
    }
}
void searchName(vector<string>& names, vector<int>& scores, vector<char>& grades, string key){
    for(unsigned i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            cout << "---------------------------------\n";
            cout << names[i] << "'s score = " << scores[i] << "\n";
            cout << names[i] << "'s grade = " << grades[i] << "\n";
            cout << "---------------------------------\n";
            return;
        }
    }
    cout << "---------------------------------\n";
    cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}
void searchGrade(vector<string>& names, vector<int>& scores, vector<char>& grades, string key){
    bool found = false;
    char targetGrade = key[0];
    cout << "---------------------------------\n";
    for(unsigned i = 0; i < names.size(); i++){
        if(toupper(grades[i]) == targetGrade){
            cout << names[i] << " (" << scores[i] << ")\n";
            found = true;
        }
    }
    if(!found){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}
int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
