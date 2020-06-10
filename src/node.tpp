#include "../include/operation.h"
#include <memory>
#include <iostream>

// --- BaseNode ---
void BaseNode::setName(std::string n) { _name = n; }

void BaseNode::addInputs(BaseNode *n)
{
    _inputs.push_back(n);
}

void BaseNode::addConsumers(BaseNode *n)
{
    _consumers.push_back(n);
}

template <typename T>
T BaseNode::getValue()
{
    return dynamic_cast<Node<T> *>(this)->getValue();
}

std::string BaseNode::getName() { return _name; }

std::vector<BaseNode *> &BaseNode::getInputs() { return _inputs; }

std::vector<BaseNode *> &BaseNode::getConsumers() { return _consumers; }

nodeType BaseNode::getNodeType() { return _nType; }

operationType BaseNode::getOperationType() { return _opType; }

// --- Node  ---

template <typename T>
T Node<T>::getValue()
{
    //std::cout << "Variable get value..." << std::endl;
    if (_dataAvailable)
    {
        std::cout << "Output get: " << *_output << std::endl;
        return *_output;
    }
    else
    {
        //std::cout << "Data not available" << std::endl;
        return T();
    }
}

template <typename T>
T Node<T>::getGradient()
{
    //std::cout << "Variable get value..." << std::endl;
    if (_gradientAvailable)
    {
        std::cout << "Gradient get: " << *_output << std::endl;
        return *_grad;
    }
    else
    {
        //std::cout << "Data not available" << std::endl;
        return T();
    }
}

template <typename T>
void Node<T>::setValue(T &&t)
{
    _dataAvailable = true;
    _output.reset(new T(t));
    std::cout << "Output set: " << *_output << std::endl;
}

template <typename T>
void Node<T>::setGrad(T &t)
{
    _gradientAvailable = true;
    _output.reset(new T(t));
    std::cout << "Gradient set: " << *_output << std::endl;
}

// --- Variable ---

template <typename T>
Variable<T>::Variable(T &&a)
{
    std::cout << "Variable contructor ..." << std::endl;
    this->_nType = nodeType::variable;
    this->setValue(std::move(a));
}

template <typename T>
Variable<T>::Variable(Variable<T> &v)
{
    std::cout << "Variable copy contructor ..." << std::endl;
    this->_nType = nodeType::variable;
    this->setValue((&v)->getValue());
}
template <typename T>
Variable<T>::Variable(Variable<T> &&v)
{
    std::cout << "Variable move contructor ..." << std::endl;
    this->_nType = nodeType::variable;
    this->_output = std::move(v->_output);
}

template <typename T>
void Variable<T>::compute() { return; }

template <typename T>
void Variable<T>::gradient() { return; }

// --- Placeholder ---

template <typename T>
Placeholder<T>::Placeholder(std::string n)
{
    this->_nType = nodeType::placeholder;
    this->setName(n);
}

template <typename T>
void Placeholder<T>::compute() { return; }

template <typename T>
void Placeholder<T>::gradient() { return; }