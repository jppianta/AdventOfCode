#include "../file.cpp"
#include <set>

set<char> ansSet (string answers) {
  set<char> res;

  for (int i = 0; i<answers.size(); i++) {
    res.insert(answers[i]);
  }

  return res;
}

int groupAnsCount (vector<string> groupAns) {
  set<char> ans;

  for (auto i = groupAns.begin(); i != groupAns.end(); ++i) {
    set<char> group = ansSet(*i);
    ans.insert(group.begin(), group.end());
  }

  return ans.size();
}

set<char> intersection(set<char> setA, set<char> setB) {
  set<char> res;

  for (auto i = setA.begin(); i != setA.end(); ++i) {
    if (setB.count(*i)) {
      res.insert(*i);
    }
  }

  return res;
}

int groupAnsCountTwo (vector<string> groupAns) {
  set<char> ans;
  bool first = true;

  for (auto i = groupAns.begin(); i != groupAns.end(); ++i) {
    if (first) {
      ans = ansSet(*i);
      first = false;
    } else {
      ans = intersection(ans, ansSet(*i));
    }
  }

  return ans.size();
}

int ansSum(vector<string> inp) {
  vector<vector<string>> groups = FileManager::splitVec(inp, "");
  int sum = 0;

  for (auto i = groups.begin(); i != groups.end(); ++i) {
    sum += groupAnsCountTwo(*i);
  }

  return sum;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << ansSum(list);
}