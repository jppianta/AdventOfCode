#include "../file.cpp"
#include <set>
#include <math.h>

int binarySearch (string inp, char leftChar) {
  int min = 0;
  int max = pow(2, inp.size()) - 1;

  for (int i = 0; i < inp.size(); i++) {
    int half = (min + max) / 2;

    if (inp[i] == leftChar) {
      max = half;
    } else {
      min = half + 1;
    }
  }

  return min;
}

int getSeatId(string inp) {
  string row = inp.substr(0, inp.size() - 3);
  string col = inp.substr(inp.size() - 3, 3);

  int rowNum = binarySearch(row, 'F');
  int colNum = binarySearch(col, 'L');

  return rowNum * 8 + colNum;
}

set<int> getIdSet (vector<string> inp) {
  set<int> ids;

  for(auto i = inp.begin(); i != inp.end(); ++i) {
    int id = getSeatId(*i);

    ids.insert(id);
  }

  return ids;
}

int getHighestSeatId (vector<string> inp) {
  int highest = -1;

  for(auto i = inp.begin(); i != inp.end(); ++i) {
    int id = getSeatId(*i);

    highest = id > highest ? id : highest;
  }

  return highest;
}

int getMySeatId (vector<string> inp) {
  set<int> ids = getIdSet(inp);

  int max = 127 * 8 + 7;

  for (int i = 0; i < max; i++) {
    if (!ids.count(i) && ids.count(i - 1) && ids.count(i + 1)) {
      return i;
    }
  }

  return -1;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << getHighestSeatId(list) << "\n";
  cout << getMySeatId(list);
}