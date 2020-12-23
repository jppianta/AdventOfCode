#include "../file.cpp"
#include <map>

#define preambleSize 25

vector<unsigned long long> parseInp (vector<string> inp) {
  vector<unsigned long long> res;

  for (auto i = inp.begin(); i != inp.end(); ++i) {
    res.push_back(stoull(*i));
  }

  return res;
}

unsigned long long windowSum (vector<unsigned long long> numbers, int init, int end) {
  unsigned long long min = 0;
  unsigned long long max = 0;

  for (int i=init; i <= end; i++) {
    unsigned long long val = numbers[i];

    max = val > max ? val : max;
    min = min == 0 ? val : val < min ? val : min;
  }

  return max + min;
}

unsigned long long findWindow(vector<unsigned long long> numbers, int limit, unsigned long long target) {
  int begin = 0;
  int windowSize = limit;
  unsigned long long sum = 0;
  for (int i = begin; i < windowSize; i++) {
    sum += numbers[i];
  }

  while (windowSize) {
    int initSum = sum;
    while (true) {
      if (sum == target) {
        cout << windowSum(numbers, begin, begin + windowSize) << "\n";
        return 1;
      }

      if (begin + 1 + windowSize < limit) {
        sum -= numbers[begin];
        sum += numbers[begin + windowSize];
        begin++;
      } else {
        break;
      }
    }
    begin = 0;
    sum = initSum - numbers[windowSize - 1];
    windowSize--;
  }

  return -1;
}

bool hasSum(vector<unsigned long long> numbers, int init) {
  map<unsigned long long, int> dif;
  unsigned long long target = numbers[init + preambleSize];

  for (int i = 0; i < preambleSize; i++) {
    dif.insert(pair<unsigned long long, int>(target - numbers[init + i], i));
  }

  for (int i = 0; i < preambleSize; i++) {
    int pos = init + i;
    if (dif.count(numbers[pos]) && dif.at(numbers[pos]) != i) {
      return true;
    }
  }

  return false;
}

unsigned long long getInvalid (vector<unsigned long long> numbers) {
  int pos = 0;
  while (pos + preambleSize < numbers.size()) {
    if (!hasSum(numbers, pos)) {
      findWindow(numbers, pos + preambleSize * 2, numbers[pos + preambleSize]);
      return numbers[pos + preambleSize];
    }
    pos++;
  }

  return -1;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << getInvalid(parseInp(list)) << "\n";
}