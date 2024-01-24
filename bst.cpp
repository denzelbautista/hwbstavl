#include <cassert>
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

template <typename T>
class bstree {
 private:
  struct Node {
    T data;
    Node* left;
    Node* right;
    Node* parent;

    explicit Node(T data, Node* left = nullptr, Node* right = nullptr)
        : data(data), left(left), right(right) {}
  };

  Node* root;

  Node* createNode(T data, Node* parent) {
    Node* nodo = new Node(data);
    nodo->parent = parent;
    return nodo;
  }

  Node* addNode(Node* node, T data, Node* parent) {
    if (node == nullptr) {
      return createNode(data, parent);
    }

    if (data < node->data) {
      node->left = addNode(node->left, data, node);
    } else {
      node->right = addNode(node->right, data, node);
    }

    return node;
  }

  void printInOrder(Node* node) {
    if (node != nullptr) {
      printInOrder(node->left);
      std::cout << node->data << " ";
      printInOrder(node->right);
    }
  }

  void preOrder(Node* root) {
    if (root != nullptr) {
      std::cout << root->data << " ";
      preOrder(root->left);
      preOrder(root->right);
    }
  }

  void posOrder(Node* root) {
    if (root != nullptr) {
      preOrder(root->left);
      preOrder(root->right);
      std::cout << root->data << " ";
    }
  }

  void dfs(Node* root) {  // Depth First Search
    if (root == nullptr) {
      throw std::runtime_error("Tree is empty");
    }
    std::stack<Node*> stack;
    stack.push(root);
    while (!stack.empty()) {
      Node* current = stack.top();
      stack.pop();
      std::cout << current->data << " ";
      if (current->right != nullptr) {
        stack.push(current->right);
      }
      if (current->left != nullptr) {
        stack.push(current->left);
      }
    }
    std::cout << std::endl;
  }

  void bfs(Node* root) {  // Breadth First Search
    if (root == nullptr) {
      throw std::runtime_error("Tree is empty");
    }
    std::queue<Node*> queue;
    queue.push(root);
    while (!queue.empty()) {
      Node* current = queue.front();
      queue.pop();
      std::cout << current->data << " ";
      if (current->left != nullptr) {
        queue.push(current->left);
      }
      if (current->right != nullptr) {
        queue.push(current->right);
      }
    }
    std::cout << std::endl;
  }

  bool find(T data, Node* root) {
    Node* current = root;
    while (current != nullptr) {
      if (data < current->data) {
        current = current->left;
      } else if (data > current->data) {
        current = current->right;
      } else {
        return true;  // data found
      }
    }
    return false;  // data not found
  }

  Node* search(T data, Node* root) {
    if (find(data, root)) {
      Node* current = root;
      while (current != nullptr) {
        if (data < current->data) {
          current = current->left;
        } else if (data > current->data) {
          current = current->right;
        } else {
          return current;  // data found
        }
      }
    }
    return nullptr;  // data not found
  }

  Node* nextminimun(Node* rightnode) {
    Node* minimun = rightnode;
    if (rightnode->left == nullptr) {
      return nullptr;
    } else {
      while (minimun->left != nullptr) {
        minimun = minimun->left;
      }
    }
    return minimun;
  }

  void deleteNode(Node* nodetodelete) {
    // -- when the node has no children --
    if (nodetodelete->left == nullptr && nodetodelete->right == nullptr) {
      if (nodetodelete->parent->data >
          nodetodelete->data) {  // when the node to delete is at parent's left
        nodetodelete->parent->left = nullptr;
        delete nodetodelete;
      } else {  // when the node to delete is at parent's right
        nodetodelete->parent->right = nullptr;
        delete nodetodelete;
      }
      // -- when the node has two children --
    } else if (nodetodelete->left && nodetodelete->right) {
      // if there isn't a next minimun, only the right node
      Node* nextminimunnode = nextminimun(nodetodelete->right);
      if (nextminimunnode == nullptr) {
        nextminimunnode = nodetodelete->right;
        nodetodelete->data = nextminimunnode->data;
        nodetodelete->right = nextminimunnode->right;
        nextminimunnode->parent = nodetodelete;
        delete nextminimunnode;
      } else {
        nodetodelete->data = nextminimunnode->data;
        nextminimunnode->parent->left = nullptr;
        delete nextminimunnode;
      }
      // -- when the mode has one child
    } else {
      Node* child =
          nodetodelete->left ? nodetodelete->left : nodetodelete->right;
      // Node* parent = nodetodelete->parent;
      if (nodetodelete->parent->data > nodetodelete->data) {
        nodetodelete->parent->left = child;
        child->parent = nodetodelete->parent;
        delete nodetodelete;
      } else {
        nodetodelete->parent->right = child;
        child->parent = nodetodelete->parent;
        delete nodetodelete;
      }
    }
  }

  void removeNode(Node* node, T data) {
    if (node == NULL) {
      return;
    } else if (data < node->data) {
      removeNode(node->left, data);
    } else if (data > node->data) {
      removeNode(node->right, data);
    } else {
      deleteNode(node);  // node found
    }
  }

 public:
  bstree() : root(nullptr) {}

  // Insert del bst
  void insert(T data) { root = addNode(root, data, nullptr); }

  // Remove del bst
  void remove(T data) { removeNode(root, data); }

  // Print in order del bst
  void printInOrder() {
    printInOrder(root);
    std::cout << std::endl;
  }

  // Print pre order del bst
  void preOrder() {
    preOrder(root);
    std::cout << std::endl;
  }

  // Print pos order del bst
  void posOrder() {
    posOrder(root);
    std::cout << std::endl;
  }

  T findMin() {
    if (root == nullptr) {
      throw std::runtime_error("Tree is empty");
    }
    Node* current = root;
    while (current->left != nullptr) {
      current = current->left;
    }
    return current->data;
  }

  T findMax() {
    if (root == nullptr) {
      throw std::runtime_error("Tree is empty");
    }
    Node* current = root;
    while (current->right != nullptr) {
      current = current->right;
    }
    return current->data;
  }

  T findSuccessor(T data) {
    Node* current = search(data);
    if (current == nullptr) {
      throw std::runtime_error("Value not found in tree");
    }
    if (current->right != nullptr) {
      Node* temp = current->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      return temp->data;
    } else {
      Node* successor = nullptr;
      Node* ancestor = root;
      while (ancestor != current) {
        if (current->data < ancestor->data) {
          successor = ancestor;
          ancestor = ancestor->left;
        } else {
          ancestor = ancestor->right;
        }
      }
      if (successor == nullptr) {
        throw std::runtime_error("No successor found for value");
      }
      return successor->data;
    }
  }

  T findPredecessor(T data) {
    Node* current = search(data);
    if (current == nullptr) {
      throw std::runtime_error("Value not found in tree");
    }
    if (current->left != nullptr) {
      Node* temp = current->left;
      while (temp->right != nullptr) {
        temp = temp->right;
      }
      return temp->data;
    } else {
      Node* predecessor = nullptr;
      Node* ancestor = root;
      while (ancestor != current) {
        if (current->data > ancestor->data) {
          predecessor = ancestor;
          ancestor = ancestor->right;
        } else {
          ancestor = ancestor->left;
        }
      }
      if (predecessor == nullptr) {
        throw std::runtime_error("No predecessor found for value");
      }
      return predecessor->data;
    }
  }

  void dfs() { dfs(root); }

  void bfs() { bfs(root); }

  bool find(T data) { return find(data, root); }

  Node* search(T data) { return search(data, root); }
};
/*
int main() {
  bstree<int> intTree;
  std::vector<int> intValues = {5, 3, 7, 1, 4, 6, 8, 10, 9, 11};

  for (int value : intValues) {
    intTree.insert(value);
  }

  std::cout << "In order traversal printing for int: ";
  intTree.printInOrder();

  intTree.remove(5);

  std::cout << "In order traversal printing for int after remove: ";
  intTree.printInOrder();

  bstree<char> charTree;
  std::vector<char> charValues = {'g', 'e', 'i', 'a', 'h', 'f', 'b'};

  for (char value : charValues) {
    charTree.insert(value);
  }

  // std::cout << "In order traversal printing for charl: ";
  // charTree.printInOrder();

  return 0;
}
*/
int main() {
  bstree<int> intTree;
  std::vector<int> intValues = {5, 3, 7, 1, 4, 6, 8};

  for (int value : intValues) {
    intTree.insert(value);
  }

  intTree.remove(5);

  std::cout << "In order traversal printing for int: ";
  intTree.printInOrder();
  std::cout << "Pre order traversal printing for int: ";
  intTree.preOrder();
  std::cout << "Pos order traversal printing for int: ";
  intTree.posOrder();

  // Min & max del bst test
  try {
    std::cout << "Min value in intTree: " << intTree.findMin() << std::endl;
    std::cout << "Max value in intTree: " << intTree.findMax() << std::endl;
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }

  // DFS and BFS testeo
  try {
    std::cout << "BFS traversal of intTree: ";
    intTree.bfs();

    std::cout << "DFS traversal of intTree: ";
    intTree.dfs();
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }

  // Find and search testeo
  int value = 4;
  int value2 = 10;
  std::cout << "Is " << value << " in intTree? "
            << (intTree.find(value) ? "Yes" : "No") << std::endl;
  std::cout << "Is " << value << " in intTree? "
            << (intTree.search(value) != nullptr ? "Yes" : "No") << std::endl;

  std::cout << "Is " << value2 << " in intTree? "
            << (intTree.find(value2) ? "Yes" : "No") << std::endl;
  std::cout << "Is " << value2 << " in intTree? "
            << (intTree.search(value2) != nullptr ? "Yes" : "No") << std::endl;

  // Successor & predecessor testeo
  try {
    std::cout << "Successor of 5 in intTree: " << intTree.findSuccessor(5)
              << std::endl;
    std::cout << "Predecessor of 5 in intTree: " << intTree.findPredecessor(5)
              << std::endl;
  } catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
  }

  bstree<char> charTree;
  std::vector<char> charValues = {'g', 'e', 'i', 'a', 'h', 'f', 'b'};

  for (char value : charValues) {
    charTree.insert(value);
  }

  std::cout << "In order traversal printing for charl: ";
  charTree.printInOrder();

  return 0;
}