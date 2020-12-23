#include "../file.cpp"
#include <set>

pair<string, int> parseLine (string line) {
  vector<string> splitted = FileManager::split(line, ' ');

  return pair<string, int>(splitted[0], stoi(splitted[1]));
}

vector<pair<string, int>> getCommands (vector<string> inp) {
  vector<pair<string, int>> commands;

  for (auto i = inp.begin(); i != inp.end(); ++i) {
    commands.push_back(parseLine(*i));
  }

  return commands;
}

int runCommands (vector<pair<string, int>>& commands, set<int> visited, int opLine, int acc) {
  while (true) {
    if (opLine == commands.size()) {
      return acc;
    }

    if (visited.count(opLine)) {
      return -1;
    }

    visited.insert(opLine);

    pair<string, int> command = commands[opLine];

    if (command.first == "nop") {
      opLine++;
    } else if (command.first == "jmp") {
      opLine += command.second;
    } else if (command.first == "acc") {
      acc += command.second;
      opLine++;
    }
  }
}

int runCommands (vector<pair<string, int>>& commands) {
  int acc = 0;
  int opLine = 0;
  set<int> visited;

  while (true) {
    if (visited.count(opLine)) {
      return acc;
    }

    visited.insert(opLine);

    pair<string, int> command = commands[opLine];

    if (command.first == "nop") {
      opLine++;
    } else if (command.first == "jmp") {
      opLine += command.second;
    } else if (command.first == "acc") {
      acc += command.second;
      opLine++;
    }
  }
}

int runCommands2 (vector<pair<string, int>> commands) {
  set<int> visited;
  int opLine = 0;
  int acc = 0;

  while (true) {
  if (opLine == commands.size()) {
    return acc;
  }

  if (visited.count(opLine)) {
    return -1;
  }

  visited.insert(opLine);

  pair<string, int> command = commands[opLine];

  if (command.first == "nop") {
    int jmp = runCommands(commands, visited, opLine + command.second, acc);
    if (jmp != -1) {
      return jmp;
    }
    opLine++;
  } else if (command.first == "jmp") {
    int nop = runCommands(commands, visited, opLine + 1, acc);
    if (nop != -1) {
      return nop;
    }
    opLine += command.second;
  } else if (command.first == "acc") {
    acc += command.second;
    opLine++;
  }
}
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << runCommands2(getCommands(list));
}