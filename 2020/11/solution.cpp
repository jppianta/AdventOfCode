#include "../file.cpp"

vector<string> copyVector (vector<string> v) {
  vector<string> copy;

  for (auto i = v.begin(); i != v.end(); ++i) {
    copy.push_back(*i);
  }

  return copy;
}

char getNewValTwo (vector<string> plane, int x, int y) {
  char seat = plane[x][y];
  int occ = 0;

  pair<int, int> directions[8] = {
    pair<int, int>(-1, -1),
    pair<int, int>(-1, 0),
    pair<int, int>(-1, 1),
    pair<int, int>(0, -1),
    pair<int, int>(0, 1),
    pair<int, int>(1, -1),
    pair<int, int>(1, 0),
    pair<int, int>(1, 1),
  };

  for (int i = 0; i < 8; i++) {
    pair<int, int> dir = directions[i];
    int mult = 1;

    while (true) {
      int dirX = dir.first * mult + x;
      int dirY = dir.second * mult + y;

      if (dirX < 0 || dirX >= plane.size() || dirY < 0 || dirY >= plane[0].size()) {
        break;
      }

      char pos = plane[dirX][dirY];
      if (pos != '.') {
        if (pos == '#') {
          occ++;
        }
        break;
      }
      mult++;
    }
  }

  if (seat == 'L' && occ == 0) {
    return '#';
  }

  if (seat == '#' && occ >= 5) {
    return 'L';
  }

  return seat;
}

char getNewVal (vector<string> plane, int x, int y) {
  char seat = plane[x][y];
  int occ = 0;

  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if ((i != x || j != y) && i >= 0 && i < plane.size() && j >= 0 && j < plane[0].size()) {
        if (plane[i][j] == '#') {
          occ++;
        }
      }
    }
  }

  // printf("%c, %d, %d, %d\n", seat, x, y, occ);

  if (seat == 'L' && occ == 0) {
    return '#';
  }

  if (seat == '#' && occ >= 4) {
    return 'L';
  }

  return seat;
}

pair<vector<string>, int> updateSeats (vector<string> plane) {
  vector<string> newPlane = copyVector(plane);
  int dif = 0;

  for (int i = 0; i < plane.size(); i++) {
    for (int j = 0; j < plane[0].size(); j++) {
      newPlane[i][j] = getNewValTwo(plane, i, j);
      if (newPlane[i][j] != plane[i][j]) {
        dif++;
      }
    }
  }

  return pair<vector<string>, int>(newPlane, dif);
}

int countOcc (vector<string> plane) {
  int seatsDif;
  int occCount = 0;

  do {
    pair<vector<string>, int> seats = updateSeats(plane);
    seatsDif = seats.second;
    plane = seats.first;
  } while (seatsDif > 0);

  for (int i = 0; i < plane.size(); i++) {
    for (int j = 0; j < plane[0].size(); j++) {
      if (plane[i][j] == '#') {
        occCount++;
      }
    }
  }

  return occCount;
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  cout << countOcc(list);
}