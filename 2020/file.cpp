#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class FileManager {
  string fileName;

public:
  FileManager(string);
  vector<string> readFile();
  static vector<string> split(string s, char delimiter);
  static vector<vector<string>> splitVec(vector<string> vec, string delimiter);
};

FileManager::FileManager(string name) {
  fileName = name;
}

vector<string> FileManager::readFile() {
  vector<string> res;
  string line;

  ifstream file(fileName);

  while (getline(file, line))
  {
    res.push_back(line);
  }

  file.close();
  return res;
}

vector<string> FileManager::split(string s, char delimiter) {
  vector<string> res;
  string aux = "";

  for (int i=0; i<s.size(); i++) {
    char c = s[i];

    if (c == delimiter) {
      res.push_back(aux);
      aux = "";
    } else {
      aux += c;
    }
  }

  res.push_back(aux);
  return res;
}

vector<vector<string>> FileManager::splitVec(vector<string> vec, string delimiter) {
  vector<vector<string>> res;
  vector<string> aux;

  for (int i=0; i<vec.size(); i++) {
    string s = vec[i];

    if (s == delimiter) {
      res.push_back(aux);
      aux.clear();
    } else {
      aux.push_back(s);
    }
  }

  res.push_back(aux);
  return res;
}