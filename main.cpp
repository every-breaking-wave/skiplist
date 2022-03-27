#include <iostream>

#include "skiplist.h"

// 用于自动测试
void build_SkipList(SkipList *SkipList, string input_file_path)
{
    int searchTime = 0;
    ifstream inputData;
    inputData.open(input_file_path, ios::in);
    if(!inputData) {
        cout << "[error]: file " << input_file_path << " not found." << endl;
        inputData.close();
        return 0;
    }

    string line;
    while (inputData >> line)
    {
        int bracketPos = line.find('(');
        string op = line.substr(0, bracketPos);
        string param = line.substr(bracketPos + 1, line.size() - bracketPos - 2);
        if (op == "Insert")
        {
            int commaPos = param.find(',');
            int key = atoi(param.substr(0, commaPos).c_str());
            int val = atoi(param.substr(commaPos + 1).c_str());
            SkipList->Insert(key, val);
        }
        else if (op == "Search")
        {
            int key = atoi(param.c_str());
            searchTime += SkipList->Search(key);
        }
    }
    inputData.close();
}

int main() {
    srand((unsigned int )time(0));
    SkipList s;

    return 0;
}
