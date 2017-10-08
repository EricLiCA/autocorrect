#include "Node.h"

Node::Node(char character) {
    value_ = character;

    left_ = nullptr;
    middle_ = nullptr;
    right_ = nullptr;

    state_ = edge;
}

char Node::Value() {
    return value_;
}

void Node::setLeft(Node *node) {
    left_ = node;
}

void Node::setMiddle(Node *node) {
    middle_ = node;
}

void Node::setRight(Node *node) {
    right_ = node;
}

Node *Node::Left() {
    return left_;
}

Node *Node::Middle() {
    return middle_;
}

Node *Node::Right() {
    return right_;
}

void Node::setState(State state) {
    state_ = state;
}

State Node::currentState() {
    return state_;
}
