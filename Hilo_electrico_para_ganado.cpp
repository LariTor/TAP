#include <algorithm>
class Punto {
public:
  Punto(int x, int y) : x(x), y(y) {}
  Punto(const Punto &) = default;
  Punto &operator=(Punto &&) = default;
  Punto &operator=(const Punto &) = default;
  ~Punto() {}

  int x;
  int y;
};

class Node {
public:
  Node(Punto p) : value(p) {}
  Node(Node &&) = default;
  Node(const Node &) = default;
  Node &operator=(Node &&) = default;
  Node &operator=(const Node &) = default;
  ~Node() {}

  Punto value;
  Node *left = nullptr;
  Node *rigth = nullptr;
  int height = 1;
};

class OrthRangeTree {
public:
  OrthRangeTree() {}
  OrthRangeTree(OrthRangeTree &&) = default;
  OrthRangeTree(const OrthRangeTree &) = default;
  OrthRangeTree &operator=(OrthRangeTree &&) = default;
  OrthRangeTree &operator=(const OrthRangeTree &) = default;
  ~OrthRangeTree() {}

  size_t height(Node *n) { return n ? n->height : 0; }

  int balance(Node *n) { return n ? height(n->left) - height(n->rigth) : 0; }

  Node *left_rotate(Node *n) {
    Node *y = n->rigth;
    Node *T2 = y->left;
    y->left = n;
    n->rigth = T2;
    n->height = 1 + std::max(height(n->left), height(n->rigth));
    y->height = 1 + std::max(height(y->left), height(y->rigth));
    return y;
  }

  Node *rigth_rotate(Node *n) {
    Node *y = n->left;
    Node *T3 = y->rigth;
    y->rigth = n;
    n->left = T3;
    n->height = 1 + std::max(height(n->left), height(n->rigth));
    y->height = 1 + std::max(height(y->left), height(y->rigth));
    return y;
  }

  Node *insert(Node *root, Punto value) {
    if (!root) {
      return new Node(value);
    } else if (value.x < root->value.x) {
      root->left = insert(root->left, value);
    } else {
      root->rigth = insert(root->rigth, value);
    }
    root->height = 1 + std::max(height(root->left), height(root->rigth));
    int c_balance = balance(root);
    if (c_balance > 1 && value.x < root->left->value.x) {
      return rigth_rotate(root);
    }
    if (c_balance < -1 && value.x > root->rigth->value.x) {
      return left_rotate(root);
    }
    if (c_balance > 1 && value.x > root->left->value.x) {
      root->left = left_rotate(root->left);
      return rigth_rotate(root);
    }
    if (c_balance < -1 && value.x < root->rigth->value.x) {
      root->left = left_rotate(root->left);
      return rigth_rotate(root);
    }
    return root;
  }

private:
  Node *m_root = nullptr;
};

class Cerco : public Punto {
public:
  Cerco(int x1, int y1, int x2, int y2) : Punto(x1, y1), x2(x2), y2(y2) {}
  Cerco(Cerco &&) = default;
  Cerco(const Cerco &) = default;
  Cerco &operator=(Cerco &&) = default;
  Cerco &operator=(const Cerco &) = default;
  ~Cerco() {}

private:
  int x2;
  int y2;

  float E = 0.;
  float A = 0.;
  int M;
};
