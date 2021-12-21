
#include <string>
#include "models.h"
#include "logs.h"

Element ElementNode::to_element() {
    // convert 'this' to an @Element object.
    Element res{};
    if (getElementType() == ElementType::OPERATOR)
        res.setOperator(getOperator());
    else res.setValue(getValue());
    return res;
}

ElementNode::ElementNode(Element &element) : Element() {
    // simply initialize this object by an element.
    if (element.getElementType() == ElementType::OPERATOR)
        setOperator(element.getOperator());
    else setValue(element.getValue());
}


ElementStack::ElementStack() {
    // if you declared a empty stack, we should clear it.
    this->m_size = 0;
    this->m_top = nullptr;
}

ElementStack::~ElementStack() {
    auto *i = this->m_top;

    // delete all the node in the stack.
    while (i != nullptr) {
        auto *p = i;
        i = i->previous();
        delete p;
    }
}

void ElementStack::pop() {
    // if the stack is empty, this method should not be called. so if we did it,
    // there must be some errors in code, this function should cancel the whole program.
    if (this->m_size <= 0) {
        log(LogLevel::ERROR, "the stack is empty",
            "please check your code to ensure there is no duplicate pop().");
        exit(1);
    }

    try {
        // move the top pointer to previous node.
        auto *p = this->m_top;
        if (this->m_size > 1) {
            this->m_top = this->m_top->previous();
            this->m_top->setNext(nullptr);
        } else this->m_top = nullptr;
        // disconnect the top node with others.
        // delete the top element.
        delete p;
    } catch (std::string &e) {
        log(LogLevel::FATAL, "could not pop the node.", e);
        exit(1);
    }
    this->m_size--;
}

void ElementStack::push(Element node) {
    auto *n = new ElementNode(node);

    // if stack is not empty, we should just set the top pointer on it.
    if (this->m_size == 0) {
        this->m_top = n;
        n->setPrevious(nullptr);
        n->setNext(nullptr);
    }
        // if stack is not empty, we should push the element after the top pointer,
        // and move the top pointer onto it.
    else
        try {
            // connect the new node.
            this->m_top->setNext(n);
            n->setPrevious(this->m_top);
            n->setNext(nullptr);
            // move the top pointer.
            this->m_top = this->m_top->next();
        } catch (std::string &e) {
            log(LogLevel::FATAL, "could not insert a node into stack", e);
            exit(1);
        }

    // pushing succeeded, incrementing m_size.
    this->m_size++;
}

bool ElementStack::empty() const {
    return this->m_size == 0;
}


ElementExpression::ElementExpression() {

    // if you declared a empty expression, we should clear it.
    this->m_head = nullptr;
    this->m_tail = nullptr;
    this->m_size = 0;
}

ElementExpression::~ElementExpression() {
    auto *i = this->head();

    // remove all the node inside the expression.
    while (i != nullptr) {
        auto *p = i;
        i = i->next();
        delete p;
    }
}

Element ElementExpression::operator[](int pos) {
    int i = 0;
    auto *p = this->head();

    // find the element you need
    while (i < pos && p != nullptr) {
        i++;
        p = p->next();
    }

    // index out of range
    if (i > pos || p == nullptr) {
        log(LogLevel::FATAL, "expression index out of range.");
        exit(1);
    }
    return p->to_element();
}

void ElementExpression::append(Element element) {
    auto *p = new ElementNode(element);

    // if the expression is empty
    if (this->m_tail == nullptr) {
        this->m_head = this->m_tail = p;
        p->setPrevious(nullptr);
        p->setNext(nullptr);
    } else { // the expression is not empty, we can simply add the node
             // behind tail, ans move tail pointer.
        this->tail()->setNext(p);
        p->setPrevious(this->tail());
        p->setNext(nullptr);
        this->m_tail = this->tail()->next();
    }
    this->m_size++;
}

bool Element::operator<=(Element e) const  {

    // reload this so we can compare two operators like this: a <= b
    if (this->getElementType() == e.getElementType()) {
        if (this->getElementType() == ElementType::OPERATOR) {
            if (this->getOperator() > 1 && e.getOperator() < 2) return false;
            return true;
        } else {
            return this->getValue() <= e.getValue();
        }
    } else {
        throw std::runtime_error("operator<=(): the two operand is not in the same type.");
    }
}
