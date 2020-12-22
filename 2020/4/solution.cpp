#include "../file.cpp"
#include <map>
#include <set>
#include <regex>

map<string, string> getPassport (vector<string> info) {
  map<string, string> res;

  for (int i = 0; i < info.size(); i++) {
    string s = info[i];

    vector<string> splitedInfo = FileManager::split(s, ' ');
    
    for (int j = 0; j < splitedInfo.size(); j++) {
      vector<string> p = FileManager::split(splitedInfo[j], ':');
      res.insert(pair<string, string>(p[0], p[1]));
    }
  }

  return res;
}

vector<map<string, string>> parseInp (vector<string> inp) {
  vector<vector<string>> splittedInp = FileManager::splitVec(inp, "");
  vector<map<string, string>> res;

  for (int i = 0; i < splittedInp.size(); i++) {
    res.push_back(getPassport(splittedInp[i]));
  }

  return res;
}

bool isValidPassport (map<string, string> passport) {
  pair<string, bool (*)(string)> fields[] = {
    pair<string, bool (*)(string)>(
      "byr", 
      [](string s) {
        int year = stoi(s);
        return s.size() == 4 && year >= 1920 && year <= 2002;
      }
    ),
    pair<string, bool (*)(string)>(
      "iyr", 
      [](string s) {
        int year = stoi(s);
        return s.size() == 4 && year >= 2010 && year <= 2020;
      }
    ),
    pair<string, bool (*)(string)>(
      "eyr", 
      [](string s) {
        int year = stoi(s);
        return s.size() == 4 && year >= 2020 && year <= 2030;
      }
    ),
    pair<string, bool (*)(string)>(
      "hgt", 
      [](string s) {
        if (s.size() < 3) return false;
        string m = s.substr(s.size() - 2, 2);
        int val = stoi(s.substr(0, s.size() - 2));
        return m == "in" ? val >= 59 && val <= 76 : m == "cm" ? val >= 150 && val <= 193 : false;
      }
    ),
    pair<string, bool (*)(string)>(
      "hcl", 
      [](string s) {
        regex r ("([0-9]|[a-f])*");
        string val = s.substr(1, s.size() - 1);
        return s[0] == '#' && regex_match(val, r);
      }
    ),
    pair<string, bool (*)(string)>(
      "ecl", 
      [](string s) {
        set<string> f = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
        return f.count(s) == 1;
      }
    ),
    pair<string, bool (*)(string)>(
      "pid", 
      [](string s) {
        regex r ("([0-9])*");
        return s.size() == 9 && regex_match(s, r);
      }
    )
  };

  for (int i = 0; i < 7; i++) {
    pair<string, bool (*)(string)> field = fields[i];

    if (passport.find(field.first) == passport.end() || !field.second(passport.at(field.first))) {
      return false;
    }
  }

  return true;
}

int countValidPassports(vector<string> list) {
  vector<map<string, string>> parsedInp = parseInp(list);
  int count = 0;

  for (auto i = parsedInp.begin(); i != parsedInp.end(); ++i) {
    if (isValidPassport(*i))
      count++;
  }

  return count;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << countValidPassports(list);
}