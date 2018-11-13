#include <pthread.h>
#include <stdio.h>
#include <vector>
#include <new>

class Node {
public:
  int value;
  std::vector<Node*> children;
  Node(int _value) : value(_value) {}
  ~Node() { this->children.clear(); }
};

struct argument {
  Node *root;
  int result;
};

extern "C" {

int traverse(Node *node) {
  int sum = node->value;
  for(int i = 0, il = node->children.size(); i < il; i++) {
    sum += traverse(node->children[i]);
  }
  return sum;
}

void* bgFunc(void *arg) {
  struct argument *a = (struct argument*)arg;
  a->result = traverse(a->root);
  return a;
}

int traverseThread(Node *node) {
  struct argument arg1, arg2;
  pthread_t thread1, thread2;

  // Assuming root has two children.
  arg1.root = node->children[0];
  arg2.root = node->children[1];

  if(pthread_create(&thread1, NULL, bgFunc, &arg1)) {
    perror("Thread create failed");
    return 0;
  }
  if(pthread_create(&thread2, NULL, bgFunc, &arg2)) {
    perror("Thread create failed");
    return 0;
  }

  if(pthread_join(thread1, NULL)) {
    perror("Thread join failed");
    return 0;
  }
  if(pthread_join(thread2, NULL)) {
    perror("Thread join failed");
    return 0;
  }

  return node->value + arg1.result + arg2.result;
}

int sizeofNode() {
  return sizeof(Node);
}

Node* NodeInit(Node *node, int value) {
  return new(node) Node(value);
}

void NodeDelete(Node *node) {
  node->~Node();
}

Node* NodeAdd(Node *node, Node *child) {
  node->children.push_back(child);
  return node;
}

}
