#include "../file.cpp"
#include <tuple>

tuple<int, int, char, string> parseVal (string line) {
  string aux = "";
  int part = 0;
  int min, max;
  char val;
  string pass;

  for (int i=0; i < line.size(); i++) {
    char c = line[i];

    switch(c) {
      case '-': {
        min = stoi(aux);
        aux = "";
        break;
      }
      case ' ': {
        if (part == 0) {
          max = stoi(aux);
        } else {
          val = aux[0];
        }
        aux = "";
        part++;
        break;
      }

      default: {
        aux += c;
      }
    }
  }
  pass = aux;
  return make_tuple(min, max, val, pass);
}

vector<tuple<int, int, char, string>> parseInput (vector<string> list) {
  vector<tuple<int, int, char, string>> res;

  for(auto i = list.begin(); i != list.end(); ++i) {
    res.push_back(parseVal(*i));
  }

  return res;
}

bool isValidPassOne (int min, int max, char c, string pass) {
  int occ = 0;

  for (int i=0; i<pass.size(); i++) {
    char n = pass[i];

    if (n == c) {
      occ++;
    }
  }

  return occ >= min && occ <= max;
}

bool isValidPassTwo (int i0, int i1, char c, string pass) {
  int occ = 0;

  if (pass[i0 - 1] == c)
    occ++;

  if (pass[i1 - 1] == c)
    occ++;

  return occ == 1;
}

int countValidPassPartOne (vector<string> list) {
  vector<tuple<int, int, char, string>> tuples = parseInput(list);
  int count = 0;

  for(auto i = tuples.begin(); i != tuples.end(); ++i) {
    tuple<int, int, char, string> t = *i;

    if (isValidPassOne(get<0>(t), get<1>(t), get<2>(t), get<3>(t))) {
      count ++;
    }
  }

  return count;
}

int countValidPassPartTwo (vector<string> list) {
  vector<tuple<int, int, char, string>> tuples = parseInput(list);
  int count = 0;

  for(auto i = tuples.begin(); i != tuples.end(); ++i) {
    tuple<int, int, char, string> t = *i;

    if (isValidPassTwo(get<0>(t), get<1>(t), get<2>(t), get<3>(t))) {
      count ++;
    }
  }

  return count;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << countValidPassPartOne(list) << "\n";
  cout << countValidPassPartTwo(list);
}