#include "../file.cpp"
#include <algorithm>
#include <map>

vector<int> parseInp (vector<string> inp) {
  vector<int> res;

  for (auto i = inp.begin(); i != inp.end(); ++i) {
    res.push_back(stoi(*i));
  }

  sort(res.begin(), res.end());
  return res;
}

unsigned long long possibilities (vector<int>& numbers, int curr, int j, map<int, unsigned long long>& waysMap) {
  if (waysMap.count(j)) {
    return waysMap.at(j);
  }

  if (j == numbers.size()) {
    waysMap.insert(pair<int, unsigned long long>(j, 1));
    return 1;
  }
  
  unsigned long long ways = 0;

  for (int i = j; i < numbers.size(); i++) {
    int dif = numbers[i] - curr;
    if (dif <= 3) {
      ways += possibilities(numbers, numbers[i], i + 1, waysMap);
    } else {
      break;
    }
  }

  waysMap.insert(pair<int, unsigned long long>(j, ways));
  return ways;
}

int findDifs (vector<int> numbers) {
  int oneDifs = 0;
  int threeDifs = 1;
  int curr = numbers.front();

  switch (curr) {
    case 1: {
      oneDifs++;
      break;
    }
    case 3: {
      threeDifs++;
      break;
    }
  }

  for (int i = 1; i < numbers.size(); i++) {
    int dif = numbers[i] - curr;
    curr = numbers[i];

    switch (dif) {
      case 1: {
        oneDifs++;
        break;
      }
      case 3: {
        threeDifs++;
        break;
      }
    }
  }

  return oneDifs * threeDifs;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  vector<int> inp = parseInp(list);
  cout << findDifs(inp) << "\n";
  map<int, unsigned long long> waysMap;
  cout << possibilities(inp, 0, 0, waysMap);
}