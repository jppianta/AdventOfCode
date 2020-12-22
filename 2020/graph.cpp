#include <string>
#include <vector>

template <typename T>

class Graph {
  public:
    class GraphNode {
      private:
        T val;
        std::vector<GraphNode*> children;

      public:
        GraphNode (T v) {
          this->val = v;
        }

        T getVal() {
          return this->val;
        }

        std::vector<GraphNode*>* getChildren () {
          return &(this->children);
        }

        int childrenSize() {
          return this->children.size();
        }

        void addChild(GraphNode* child) {
          this->children.push_back(child);
        }

        void print() {
          cout << "Node: " << this->val << "\n";
          cout << "Children: ";
          for (auto i = this->children.begin(); i != this->children.end(); ++i) {
            cout << (*i)->getVal() << ", ";
          }

          cout << "\n";
        }
    };

    void createNode(T n) {
      this->nodes.push_back(GraphNode(n));
    }

    GraphNode* getNode(T val) {
      for (auto i = this->nodes.begin(); i != this->nodes.end(); ++i) {
        if ((*i).getVal() == val) {
          return &(*i);
        }
      }

      throw "Node not found";
    }

    void connectNodes(T from, T to) {
      GraphNode* fromNode = getNode(from);
      GraphNode* toNode = getNode(to);

      fromNode->addChild(toNode);
    }

    std::vector<GraphNode>* getNodes() {
      return &(this->nodes);
    }

    void print() {
      for (auto i = this->nodes.begin(); i != this->nodes.end(); ++i) {
        GraphNode n = *i;
        n.print();
      }
    }

  private:
    std::vector<GraphNode> nodes;
};