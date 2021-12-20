#ifndef _STACK_MANAGE_H_
#define _STACK_MANAGE_H_

#include <cstdlib>

/*
 * enum ElementType: the base type for elements.
 * this flag defines the value's type.
 */
enum ElementType {
    OPERAND = false,
    OPERATOR = true
};

/*
 * enum ElementOperator: the base type for operator element.
 */
enum ElementOperator {
    ADD = 0,
    SUBTRACT = 1,
    MULTIPLY = 2,
    DIVIDE = 3,
    // this type maybe contain '(', but we needn't assign it.
};

/*
 * class Element: the base type for expression element.
 *
 * m_type: the element type, should be type: @ElementType
 * m_value: the element value, should be type: @int
 *
 * all members should be read and modify by member functions.
 */
class Element {

    /*
     * class definition @Element:
     * this class is the base class to show a single element in the expression.
     * it could be an operand or an operator.
     * we implement this two types into a single class type so that we can manage it
     * in one stack or one queue.
     */

private:
    ElementType m_type; // the type of the element.
    double m_value; // operand value of element, it should be used only the @m_type is ElementType::OPERAND
    int m_ops; // operator value of element, it should be used only the @m_type is ElementType::OPERATOR
public:
    // getValue(): return the value of member @m_value.
    double getValue() const { return this->m_value; }

    // getOperator(): return the value of member @m_ops.
    int getOperator() const { return this->m_ops; }

    // getElementType(): return the value of member @m_type, in type @ElementType
    ElementType getElementType() const { return this->m_type; }

    // setValue(): set the value of member @m_value.
    // @val -> int: the source value.
    // when it is called, the element type will be set to ElementType::OPERAND automatically.
    void setValue(double val) {
        this->m_value = val;
        this->m_type = ElementType::OPERAND;
    }

    // setOperator(): set the value of member @m_ops.
    // @op -> int: the source value. it's type should be ElementOperator, but we need this to
    //             save the operator '(', so just use int to implement it.
    // when it is called, the element type will be set to ElementType::OPERATOR automatically.
    void setOperator(int op) {
        this->m_ops = op;
        this->m_type = ElementType::OPERATOR;
    }

    // reloaded function operator<=(): compare the two operator's priority.
    bool operator<=(Element e) const;

};

class ElementNode : public Element {

    /*
     * class definition @ElementNode:
     * this class inherits the Element class, for the purpose of stack management.
     * we'd like to implement the stack by linked list, so that we can save some memories
     * and won't be afraid of expression's length.
     */

private:
    // @m_next -> ElementNode*: the next element of this linked list.
    ElementNode *m_next{};
    // @m_previous -> ElementNode*: the previous element of this linked list.
    ElementNode *m_previous{};
public:

    // the default constructor: do nothing.
    ElementNode() : Element() {};

    // Constructor @ElementNode(): this constructor is designed to initialize
    // with a parent type @Element, so that we can easily transform between these two types.
    // @element -> Element&: the element you want to use it to initialize this class.
    explicit ElementNode(Element &element);

    // setNext(): set the value of member @m_next.
    // @n -> ElementNode*: the node you want to set.
    void setNext(ElementNode *n) { this->m_next = n; }

    // next(): return the value of member @m_next.
    ElementNode *next() { return this->m_next; }

    // setPrevious(): set the value of member @m_previous.
    // @n -> ElementNode*: the node you want to set.
    void setPrevious(ElementNode *n) { this->m_previous = n; }

    // previous(): return the value of member @m_previous.
    ElementNode *previous() { return this->m_previous; }

    // to_element(): this function returns the element main data in @Element type.
    Element to_element();
};

class ElementStack {
private:
    // @m_top -> ElementNode*: the top pointer of this stack.
    ElementNode *m_top;
    // @m_size -> int: the size of this stack;
    int m_size;
public:
    // default constructor.
    ElementStack();

    // destructor: delete all the node to avoid the leak of memory.
    ~ElementStack();

    // top(): return the top element of this stack
    Element top() const { return this->m_top->to_element(); }

    // pop(): remove the top element of this stack, resolve nodes' relation.
    void pop();

    // push(): push a element into the stack.
    // @node -> Element: the node you want to push into.
    void push(Element node);

    // empty(): return true if the stack is empty.
    bool empty() const;
};

/*
 * class ElementExpression:
 * this class is used to save the expression.
 * we use a linked list to save the expression.
 */
class ElementExpression {
private:
    ElementNode *m_head; // the expression element head.
    ElementNode *m_tail; // the expression element tail.
    int m_size; // the expression element size.
public:
    // default constructor
    ElementExpression();

    // destructor, this function will free all the node in this linked list.
    ~ElementExpression();

    // head() -> ElementNode*: return the member @m_head
    ElementNode *head() { return this->m_head; }

    // tail() -> ElementNode*: return the member @m_tail
    ElementNode *tail() { return this->m_tail; }

    // size(): return the expression size
    int size() const { return this->m_size; }

    // append(): append a element after the expression.
    // @element -> Element: the element to be appended.
    // use this function to construct the expression.
    void append(Element element);

    // reload function operator[](): get the Element at the position @pos.
    // @pos -> int: the position of the element you want to get.
    Element operator[](int pos);


};

#endif // _STACK_MANAGE_H_