#include "../file.cpp"
#include "../graph.cpp"
#include <map>

pair<string, vector<pair<int, string>>> parseLine (string line) {
  line.pop_back();
  vector<string> res = FileManager::split(line, ',');
  if (res.size() > 1) {
    res[1].erase(res[1].begin());
  }
  vector<string> first = FileManager::split(res[0], ' ');
  res.erase(res.begin());

  vector<vector<string>> firstGroup = FileManager::splitVec(first, "contain");

  vector<vector<string>> groups = FileManager::splitVec(res, "contain");

  firstGroup[0].erase(firstGroup[0].end() - 1);
  string nodeName = FileManager::join(firstGroup[0], ' ');
  res.insert(res.begin(), FileManager::join(firstGroup[1], ' '));

  vector<pair<int, string>> childrenPairs;

  for (auto i = res.begin(); i != res.end(); ++i) {
    string items = FileManager::trimStart(*i);
    vector<string> ch = FileManager::split(items, ' ');

    if (ch.front() == "no") {
      continue;
    }

    int quant = stoi(ch.front());
    ch.erase(ch.begin());

    ch.erase(ch.end() - 1);
    string name = FileManager::join(ch, ' ');

    childrenPairs.push_back(pair<int, string> (quant, name));
  }

  return pair<string, vector<pair<int, string>>> (nodeName, childrenPairs);
}

vector<pair<string, vector<pair<int, string>>>> getPairs (vector<string> inp) {
  vector<pair<string, vector<pair<int, string>>>> res;

  for (auto i = inp.begin(); i != inp.end(); ++i) {
    res.push_back(parseLine(*i));
  }

  return res;
}

Graph<string> createGraph (vector<pair<string, vector<pair<int, string>>>> pairs) {
  Graph<string> g;

  for (auto i = pairs.begin(); i != pairs.end(); ++i) {
    pair<string, vector<pair<int, string>>> p = *i;
    g.createNode(p.first);
  }

  for (auto i = pairs.begin(); i != pairs.end(); ++i) {
    pair<string, vector<pair<int, string>>> p = *i;

    for (auto j = p.second.begin(); j != p.second.end(); ++j) {
      pair<int, string> pj = *j;

      for (int n = 0; n < pj.first; n++) {
        g.connectNodes(p.first, pj.second);
      }
    }
  }

  return g;
}

int countBagsRec(Graph<string>::GraphNode& currentNode) {
  int count = 1;

  vector<Graph<string>::GraphNode*>* children = currentNode.getChildren();

  for (auto i = children->begin(); i != children->end(); ++i) {
    count += countBagsRec(*(*i));
  }

  return count;
}

int countBagsInsineGold(Graph<string>& g) {
  Graph<string>::GraphNode* gold = g.getNode("shiny gold");
  return countBagsRec(*gold) - 1;
}

bool hasShinyGoldBagRec(Graph<string>::GraphNode& currentNode, map<string, bool>& visited) {
  if (visited.count(currentNode.getVal())) {
    return visited.at(currentNode.getVal());
  }

  if (currentNode.getVal() == "shiny gold") {
    visited.insert(pair<string, bool>(currentNode.getVal(), true));
    return true;
  }

  vector<Graph<string>::GraphNode*>* children = currentNode.getChildren();

  for (auto i = children->begin(); i != children->end(); ++i) {
    if (hasShinyGoldBagRec(*(*i), visited)) {
      visited.insert(pair<string, bool>(currentNode.getVal(), true));
      return true;
    }
  }

  visited.insert(pair<string, bool>(currentNode.getVal(), false));
  return false;
}

bool hasShinyGoldBag (Graph<string>::GraphNode& startNode, map<string, bool>& visited) {
  return hasShinyGoldBagRec(startNode, visited);
}

int countShinyGoldBag (Graph<string>& g) {
  map<string, bool> visited;
  int count = 0;

  vector<Graph<string>::GraphNode>* nodes = g.getNodes();

  for (auto i = nodes->begin(); i != nodes->end(); ++i) {
    if ((*i).getVal() != "shiny gold" && hasShinyGoldBag((*i), visited)) {
      count++;
    }
  }

  return count;
}

void add(int* a, vector<int*>& b) {
  b.push_back(a);
}

int main() {
  FileManager f("input.txt");
  vector<string> list = f.readFile();
  auto pairs = getPairs(list);
  Graph<string> g = createGraph(pairs);
  cout << countShinyGoldBag(g) << "\n";
  cout << countBagsInsineGold(g);
}