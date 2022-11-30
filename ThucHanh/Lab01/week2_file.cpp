#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;

struct Examinee{
    string id;
    float maths, literature, physics, chemistry, biology, history, geography, civic_education, natural_science, social_science, foreign_language;
};

float sumScore(float score1, float score2, float score3){
    return score1 + score2 + score3;
}

Examinee readExaminee(string line_info){
    stringstream ss(line_info);
    vector<string> v;
    Examinee Einfo;
    string buffer;
    for (int i = 0; i < 14; i++){
        getline(ss,buffer ,',');
        if (buffer == "")
            v.push_back("0");
        else
            v.push_back(buffer);
    }
    Einfo.id = v[0];
    Einfo.maths = stof(v[2]);
    Einfo.literature = stof(v[3]);
    Einfo.physics = stof(v[4]);
    Einfo.chemistry = stof(v[5]);
    Einfo.biology = stof(v[6]);
    Einfo.history = stof(v[7]);
    Einfo.geography = stof(v[8]);
    Einfo.civic_education = stof(v[9]);
    Einfo.natural_science = stof(v[10]);
    Einfo.social_science = stof(v[11]);
    Einfo.foreign_language = stof(v[12]);
    return Einfo;
}

vector<Examinee> readExamineeList(string file_name){
    vector<Examinee> results;
    vector<string> lines;
    string line;
    ifstream input_file(file_name);
    if(!input_file.is_open()){
        cout << "Couldn't open file " << file_name << " to read.\n";
        exit(1);
    }
    getline(input_file, line);
    while(getline(input_file, line,'\n')){
        Examinee examinee = readExaminee(line);
        results.push_back(examinee);
    }   
    cout << "Successfully read " << file_name << endl;
    input_file.close();
    return results;
}

void writeScores(vector<Examinee> examinee_list, string out_file_name){
    vector<float> BBsum;
    for (int i = 0; i < examinee_list.size(); i++){
        BBsum.push_back(sumScore(examinee_list[i].maths, examinee_list[i].literature, examinee_list[i].foreign_language));
        examinee_list[i].natural_science = sumScore(examinee_list[i].physics, examinee_list[i].chemistry, examinee_list[i].biology);
        examinee_list[i].social_science = sumScore(examinee_list[i].history, examinee_list[i].geography, examinee_list[i].civic_education);
    }
    ofstream output_file(out_file_name);
    if (!output_file.is_open()){
        cout << "Coudn't open file " << out_file_name << " to write.\n";
        exit(1);
    }
        
    string title = "SBD BB KHTN KHXH T";
    output_file.write(title.data(), title.size());
    for (int i = 0; i < examinee_list.size(); i++){
        output_file << "\n"<< examinee_list[i].id << " " << BBsum[i] << " " <<  examinee_list[i].natural_science << " " << examinee_list[i].social_science << " " << sumScore(BBsum[i], examinee_list[i].natural_science, examinee_list[i].social_science);
    }
    cout << "Successfully wrote data to " << out_file_name << endl;
    output_file.close();
}

int main(){
    //File có 17778 dòng. 1 dòng tiêu đề và 17777 dòng dữ liệu
    system("cls");
    cout << "****************************************************************\n";
    cout << "*                              WEEK2                           *\n";
    cout << "****************************************************************\n";
    cout << "========================== FILE HANDLING =======================\n";
    string input_file("data.txt");
    string output_file("scores.txt");
    vector<Examinee> examineeList = readExamineeList(input_file);
    writeScores(examineeList, output_file);
    cout << "Successfully file handling!\n";
    system("pause"); 
    return 0;
}