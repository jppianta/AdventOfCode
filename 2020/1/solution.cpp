#include "../file.cpp"
#include <set>
#include <map>

vector<int> toInt (vector<string> list) {
  vector<int> res;
  for (auto i = list.begin(); i != list.end(); ++i)
    res.push_back(stoi(*i));

  return res;
}

set<int> difSet (vector<int> list, int val) {
  set<int> dif;

  for (auto i = list.begin(); i != list.end(); ++i) {
    dif.insert(val - *i);
  }

  return dif;
}

map<int, int> difMap (vector<int> list, int val) {
  map<int, int> dif;
  set<int> subSet = difSet(list, val);

  for (auto i = list.begin(); i != list.end(); ++i) {
    for (auto j = subSet.begin(); j != subSet.end(); ++j) {
      dif.insert(pair<int, int>(*j - *i, *i));
    }
  }

  return dif;
}

int resultPartOne (vector<string> list) {
  vector<int> intList = toInt(list);

  set<int> dif = difSet(intList, 2020);

  for (auto i = intList.begin(); i != intList.end(); ++i) {
    int val = *i;

    if (dif.count(val)) {
      return val * (2020 - val);
    }
  }

  return -1;
}

int resultPartTwo (vector<string> list) {
  vector<int> intList = toInt(list);

  map<int, int> dif = difMap(intList, 2020);

  for (auto i = intList.begin(); i != intList.end(); ++i) {
    if (dif.find(*i) != dif.end()) {
      int a = *i;
      int b = dif.at(*i);
      int c = 2020 - a - b;
      return a * b * c;
    }
  }

  return -1;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << resultPartOne(list) << "\n";
  cout << resultPartTwo(list);
}