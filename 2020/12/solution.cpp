#include "../file.cpp"

vector<pair<char, int>> getCommands (vector<string> inp) {
  vector<pair<char, int>> commands;

  for (auto i = inp.begin(); i != inp.end(); ++i) {
    string val = *i;
    string quant = val.substr(1, val.size() - 1);

    commands.push_back(pair<char, int>(val[0], stoi(quant)));
  }

  return commands;
}

int manhattanDistance (vector<pair<char, int>> commands) {
  enum Direction { East, South, West, North };

  int eastDist = 0;
  int southDist = 0;

  Direction currDir = East;

  for (auto i = commands.begin(); i != commands.end(); ++i) {
    pair<char, int> command = *i;

    if (command.first == 'L' || command.first == 'R') {
      int turn = (command.second / 90) % 4;
      if (command.first == 'L') {
        turn = -turn;
      }

      int next = (currDir + turn) % 4;
      next = next < 0 ? 4 + next : next;

      currDir = static_cast<Direction>(next);
    } else if (command.first == 'F') {
      switch (currDir) {
        case East: {
          eastDist += command.second;
          break;
        }
        case South: {
          southDist += command.second;
          break;
        }
        case West: {
          eastDist -= command.second;
          break;
        }
        case North: {
          southDist -= command.second;
          break;
        }
      }
    } else {
      switch (command.first) {
        case 'E': {
          eastDist += command.second;
          break;
        }
        case 'S': {
          southDist += command.second;
          break;
        }
        case 'W': {
          eastDist -= command.second;
          break;
        }
        case 'N': {
          southDist -= command.second;
          break;
        }
      }
    }
  }

  cout << eastDist << ", " << southDist << "\n";

  return abs(eastDist) + abs(southDist);
}

int manhattanDistanceWaypoint (vector<pair<char, int>> commands) {
  enum Direction { East, South, West, North };

  Direction waypointDir1 = North;
  int waypointVal1 = 1;
  Direction waypointDir2 = East;
  int waypointVal2 = 10;

  int eastDist = 0;
  int southDist = 0;

  Direction currDir = East;

  for (auto i = commands.begin(); i != commands.end(); ++i) {
    pair<char, int> command = *i;

    if (command.first == 'L' || command.first == 'R') {
      int turn = (command.second / 90) % 4;
      int next;
      if (command.first == 'L') {
        next = (waypointDir1 - turn) % 4;
        next = next < 0 ? 4 + next : next;
      } else {
        next = (waypointDir1 + turn) % 4;
        next = next < 0 ? 4 + next : next;
      }
      waypointDir1 = static_cast<Direction>(next);
      waypointDir2 = static_cast<Direction>((next + 1) % 4);
    } else if (command.first == 'F') {
      if (waypointDir1 == East) {
        eastDist += command.second * waypointVal1;
      }
      if (waypointDir1 == West) {
        eastDist -= command.second * waypointVal1;
      }
      if (waypointDir1 == South) {
        southDist += command.second * waypointVal1;
      }
      if (waypointDir1 == North) {
        southDist -= command.second * waypointVal1;
      }
      if (waypointDir2 == East) {
        eastDist += command.second * waypointVal2;
      }
      if (waypointDir2 == West) {
        eastDist -= command.second * waypointVal2;
      }
      if (waypointDir2 == South) {
        southDist += command.second * waypointVal2;
      }
      if (waypointDir2 == North) {
        southDist -= command.second * waypointVal2;
      }
    } else {
      switch (command.first) {
        case 'E': {
          if (waypointDir1 == East) {
            waypointVal1 += command.second;
          } else if (waypointDir1 == West) {
            waypointVal1 -= command.second;
          } else if (waypointDir2 == East) {
            waypointVal2 += command.second;
          } else if (waypointDir2 == West) {
            waypointVal2 -= command.second;
          }
          break;
        }
        case 'S': {
          if (waypointDir1 == South) {
            waypointVal1 += command.second;
          } else if (waypointDir1 == North) {
            waypointVal1 -= command.second;
          } else if (waypointDir2 == South) {
            waypointVal2 += command.second;
          } else if (waypointDir2 == North) {
            waypointVal2 -= command.second;
          }
          break;
        }
        case 'W': {
          if (waypointDir1 == East) {
            waypointVal1 -= command.second;
          } else if (waypointDir1 == West) {
            waypointVal1 += command.second;
          } else if (waypointDir2 == East) {
            waypointVal2 -= command.second;
          } else if (waypointDir2 == West) {
            waypointVal2 += command.second;
          }
          break;
        }
        case 'N': {
          if (waypointDir1 == South) {
            waypointVal1 -= command.second;
          } else if (waypointDir1 == North) {
            waypointVal1 += command.second;
          } else if (waypointDir2 == South) {
            waypointVal2 -= command.second;
          } else if (waypointDir2 == North) {
            waypointVal2 += command.second;
          }
          break;
        }
      }
    }
  }

  cout << eastDist << ", " << southDist << "\n";

  return abs(eastDist) + abs(southDist);
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << manhattanDistance(getCommands(list)) << "\n";
  cout << manhattanDistanceWaypoint(getCommands(list));
}