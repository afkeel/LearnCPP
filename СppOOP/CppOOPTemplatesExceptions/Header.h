#pragma once
#ifndef GROOP_H
#define GROOP_H

template <class T>
class groop
{
private:
    template <class T>
    struct node
    {
        T data = T();
        node* next = nullptr;
    };
public:
    groop();
    ~groop();
    int size() const;
    void push_back(const T);
    void pop_front();
    void clear();
    void show() const;
private:
    int m_size;
    node<T>* head;
};
template <class T>
groop<T>::groop()
{
    m_size = 0;
    head = nullptr;
    printf("Construct group: %p\n", this);
}
template <class T>
groop<T>::~groop()
{
    printf("Destructor group: %p\n", this);
    clear();
}
template <class T>
int groop<T>::size() const
{
    return m_size;
}
template <class T>
void groop<T>::push_back(const T newdata)
{
    if (head == nullptr)
    {
        head = new node<T>;
        head->data = newdata;
        printf("Add node: %p\n", head);
    }
    else
    {
        node<T>* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new node<T>;
        current->next->data = newdata;
        printf("Add node: %p\n", current->next);
    }
    ++m_size;
}
template <class T>
void groop<T>::pop_front()
{
    node<T>* temp;
    temp = head;
    head = head->next;
    printf("Delete node: %p\n", temp);
    delete temp;
    --m_size;
}
template <class T>
void groop<T>::clear()
{
    while (m_size)
    {
        pop_front();
    }
}
template <class T>
void groop<T>::show() const
{
    node<T>* temp = head;
    while (temp != nullptr)
    {
        temp->data->show();
        temp = temp->next;
    }
}
#endif // GROOP_H
