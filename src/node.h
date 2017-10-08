#ifndef NODE_H
#define NODE_H

enum State {
    start, edge, endOfWord, final
};

class Node {
private:
    char value_;

    Node *left_;
    Node *middle_;
    Node *right_;

    State state_;

public:
    Node(char character);

    char Value();

    void setLeft(Node *node);

    void setMiddle(Node *node);

    void setRight(Node *node);

    Node *Left();

    Node *Middle();

    Node *Right();

    void setState(State state);

    State currentState();
};

#endif // NODE_H
