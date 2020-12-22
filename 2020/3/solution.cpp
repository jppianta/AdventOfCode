#include "../file.cpp"
#include <tuple>

int countTrees (vector<string> mountain, pair<int, int> pattern) {
  int length = mountain[0].size();
  int patternRight = pattern.first;
  int patternDown = pattern.second;
  int right = 0;
  int down = 0;
  int count = 0;

  for(int i=0; i<mountain.size(); i+=patternDown) {
    string line = mountain[i];
    if (line[right] == '#') {
      count++;
    }

    right = (right + patternRight) % length;
  }

  return count;
}

unsigned int multiplySlopes(vector<string> mountain) {
  unsigned int res = 1;
  
  pair<int, int> slopes[5] = {
    pair<int, int>(1, 1),
    pair<int, int>(3, 1),
    pair<int, int>(5, 1),
    pair<int, int>(7, 1),
    pair<int, int>(1, 2)
  };

  for (int i=0; i < 5; i++) {
    pair<int, int> slope = slopes[i];

    int r = countTrees(mountain, slope);
    res = res * r;
  }

  return res;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << countTrees(list, pair<int, int> (3, 1)) << "\n";
  cout << multiplySlopes(list);
}