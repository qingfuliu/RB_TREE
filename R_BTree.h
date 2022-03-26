#ifndef __RBTREE_H_
#define __RBTREE_H_
#include <string>
#include <iostream>
#include <assert.h>
#include <sstream>
#include <iostream>
#include <exception>

template <class T>
class R_BTreeNode
{
public:
    R_BTreeNode(const T &val, R_BTreeNode<T> *parent);
    R_BTreeNode(const T &val);
    R_BTreeNode();
    ~R_BTreeNode();

    bool operator==(const R_BTreeNode &temp) const
    {
        return is_Rad_ == temp.is_Rad_ &&
               left_Child_ == temp.left_Child_ &&
               right_Child_ == temp.right_Child_ &&
               GetParent() == temp.GetParent() &&
               val_ == temp.val_;
    }
public:
    inline bool isLeftChild();
    inline R_BTreeNode<T> *GetParent();
    inline R_BTreeNode<T> *GetUncle();
    inline R_BTreeNode<T> *GetAncestor();
    inline R_BTreeNode<T> *GetBrother();
    inline R_BTreeNode<T> *GetNear_Nephew();
    inline R_BTreeNode<T> *GetFar_Nephew();

public:
    bool is_Rad_;
    R_BTreeNode<T> *left_Child_ = nullptr;
    R_BTreeNode<T> *right_Child_ = nullptr;
    R_BTreeNode<T> *parent_ = nullptr;
    T val_;
};

template <class T>
R_BTreeNode<T>::R_BTreeNode()
{
    left_Child_ = nullptr;
    right_Child_ = nullptr;
    is_Rad_ = true;
}

template <class T>
R_BTreeNode<T>::R_BTreeNode(const T &val) : val_(val)
{
    left_Child_ = nullptr;
    right_Child_ = nullptr;
    is_Rad_ = true;
}

template <class T>
R_BTreeNode<T>::R_BTreeNode(const T &val, R_BTreeNode<T> *parent) : val_(val),
                                                                    parent_(parent)
{
    left_Child_ = nullptr;
    right_Child_ = nullptr;
    is_Rad_ = true;
}

template <class T>
R_BTreeNode<T>::~R_BTreeNode()
{
    assert(left_Child_ == nullptr && right_Child_ == nullptr);
}

template <class T>
R_BTreeNode<T> *R_BTreeNode<T>::GetParent()
{
    return parent_;
}

template <class T>
R_BTreeNode<T> *R_BTreeNode<T>::GetUncle()
{
    assert(GetParent() != nullptr);
    if (GetParent()->isLeftChild())
        return GetParent()->GetParent()->right_Child_;
    else
        return GetParent()->GetParent()->left_Child_;
}

template <class T>
R_BTreeNode<T> *R_BTreeNode<T>::GetAncestor()
{
    assert(GetParent() != nullptr);
    return GetParent()->GetParent();
}
template <class T>
R_BTreeNode<T> *R_BTreeNode<T>::GetBrother()
{
    assert(GetParent() != nullptr);
    if (isLeftChild())
        return GetParent()->right_Child_;
    else
        return GetParent()->left_Child_;
}

template <class T>
R_BTreeNode<T> *R_BTreeNode<T>::GetNear_Nephew()
{
    assert(GetBrother() != nullptr);
    if (isLeftChild())
    {
        return GetBrother()->left_Child_;
    }
    {
        return GetBrother()->right_Child_;
    }
}

template <class T>
R_BTreeNode<T> *R_BTreeNode<T>::GetFar_Nephew()
{
    assert(GetBrother() != nullptr);
    if (isLeftChild())
    {
        return GetBrother()->right_Child_;
    }
    {
        return GetBrother()->left_Child_;
    }
}

template <class T>
bool R_BTreeNode<T>::isLeftChild()
{
    return GetParent()->left_Child_ == this;
}

template <class T>
class R_BTree
{
public:
    R_BTree();
    R_BTree(const T &val);
    R_BTreeNode<T> *search(const T &val) ;
    R_BTreeNode<T> *search(const R_BTreeNode<T> *val) ;
    bool insert(const T &val);
    bool insert(R_BTreeNode<T> *val);
    void delete_node(const T &val);
    void delete_node(R_BTreeNode<T> *val, bool delete_alternative = true);
    R_BTreeNode<T> *GetRoot();
    std::string toString();

private:
    R_BTreeNode<T> *searchAlternative(const T &val) const;
    R_BTreeNode<T> *searchAlternative( R_BTreeNode<T> *val) ;
    void Preamble(R_BTreeNode<T> *val, std::stringstream &os);
    static void remove_a_node(R_BTreeNode<T> *val);
    static void Left_rotate(R_BTreeNode<T> *val);
    static void Right_rotate(R_BTreeNode<T> *val);

private:
    R_BTreeNode<T> *Pre_root = nullptr;
};

template <class T>
R_BTree<T>::R_BTree()
{
    Pre_root = new R_BTreeNode<T>;
}

template <class T>
R_BTree<T>::R_BTree(const T &val)
{
    Pre_root = R_BTreeNode<T>();
    Pre_root->left_Child_ = R_BTreeNode<T>(val, Pre_root);
    Pre_root->left_Child_->is_Rad_ = false;
}

template <class T>
R_BTreeNode<T> *R_BTree<T>::GetRoot()
{
    return Pre_root->left_Child_;
}
template <class T>
std::string R_BTree<T>::toString()
{
    std::stringstream os;
    Preamble(GetRoot(), os);
    return os.str();
}
template <class T>
void R_BTree<T>::Preamble(R_BTreeNode<T> *val, std::stringstream &os)
{
    if (!val)
    {
        return;
    }
    if (os)
        os << "{ " << val->val_ << "," << val->is_Rad_ << " }"
           << "  ";
    Preamble(val->left_Child_, os);
    Preamble(val->right_Child_, os);
}
template <class T>
void R_BTree<T>::remove_a_node(R_BTreeNode<T> *val)
{
    if (val->isLeftChild())
    {
        val->GetParent()->left_Child_ = nullptr;
        val->parent_ = nullptr;
        delete val;
    }
    else
    {
        val->GetParent()->right_Child_ = nullptr;
        val->parent_ = nullptr;
        delete val;
    }
}

template <class T>
void R_BTree<T>::Left_rotate(R_BTreeNode<T> *val)
{
    assert(val->right_Child_ != nullptr);
    assert(val->GetParent() != nullptr);
    R_BTreeNode<T> *father = val->GetParent();
    R_BTreeNode<T> *new_root = val->right_Child_;
    R_BTreeNode<T> *new_right = new_root->left_Child_;
    if (father != nullptr)
    {
        if (val->isLeftChild())
        {
            father->left_Child_ = new_root;
        }
        else
        {
            father->right_Child_ = new_root;
        }
        new_root->parent_ = father;
    }
    new_root->left_Child_ = val;
    val->parent_ = new_root;
    val->right_Child_ = new_right;
    if (new_right)
    {
        new_right->parent_ = val;
    }
}

template <class T>
void R_BTree<T>::Right_rotate(R_BTreeNode<T> *val)
{
    assert(val->left_Child_ != nullptr);
    assert(val->GetParent() != nullptr);
    R_BTreeNode<T> *father = val->GetParent();
    R_BTreeNode<T> *new_root = val->left_Child_;
    R_BTreeNode<T> *new_left = new_root->right_Child_;

    if (val->isLeftChild())
    {
        father->left_Child_ = new_root;
    }
    else
    {
        father->right_Child_ = new_root;
    }
    new_root->parent_ = father;

    new_root->right_Child_ = val;
    val->parent_ = new_root;
    val->left_Child_ = new_left;
    if (new_left)
    {
        new_left->parent_ = val;
    }
}
template <class T>
R_BTreeNode<T> *R_BTree<T>::search(const T &val) 
{
    R_BTreeNode<T> *Cur = GetRoot();
    while (Cur)
    {
        if (val > Cur->val_)
        {
            Cur = Cur->right_Child_;
        }
        else if (val < Cur->val_)
        {
            Cur = Cur->left_Child_;
        }
        else
        {
            break;
        }
    }
    return Cur;
}
template <class T>
R_BTreeNode<T> *R_BTree<T>::search(const R_BTreeNode<T> *val) 
{
    R_BTreeNode<T> *Cur = GetRoot();
    while (Cur)
    {
        if (val->val > Cur->val_)
        {
            Cur = Cur->right_Child_;
        }
        else if (val->val < Cur->val_)
        {
            Cur = Cur->left_Child_;
        }
        else
        {
            break;
        }
    }
    return Cur;
}

template <class T>
R_BTreeNode<T> *R_BTree<T>::searchAlternative(const T &val) const
{
    R_BTreeNode<T> *cur = GetRoot();
    assert(cur != nullptr);
    while (cur->val_ != val)
    {
        if (val >= cur->val_)
        {
            cur = cur->right_Child_;
        }
        else
        {
            cur = cur->left_Child_;
        }
    }
    return searchAlternative(cur);
}

template <class T>
R_BTreeNode<T> *R_BTree<T>::searchAlternative( R_BTreeNode<T> *val) 
{
    //cdse 0:left_child==nullptr right child==nullptr
    if (val->left_Child_ == nullptr && val->right_Child_ == nullptr)
    {
        return val;
    }
    //cdse 1:right_child!=null
    if (val->right_Child_ != nullptr)
    {
        R_BTreeNode<T> *p = val->right_Child_;
        while (p->left_Child_)
            p = p->left_Child_;
        return p;
    }
    //case 1:right_childs==nullptr left!=nullptr
    if (val->left_Child_ != nullptr)
    {
        R_BTreeNode<T> *p = val->left_Child_;
        while (p->right_Child_)
            p = p->right_Child_;
        return p;
    }
    //case 3: right_child==nullptr&&left_Child==nullptr
    return val;
}
//insert------
template <class T>
bool R_BTree<T>::insert(const T &val)
{
    if (nullptr == GetRoot())
    {
        insert(new R_BTreeNode<T>(val, Pre_root));
        return true;
    }
    R_BTreeNode<T> *location = GetRoot();
    while (location)
    {
        if (val >= location->val_)
        {
            if (location->right_Child_ == nullptr)
            {
                location->right_Child_ = new R_BTreeNode<T>(val, location);
                location = location->right_Child_;
                break;
            }
            location = location->right_Child_;
        }
        else if (val < location->val_)
        {
            if (location->left_Child_ == nullptr)
            {
                location->left_Child_ = new R_BTreeNode<T>(val, location);
                location = location->left_Child_;
                break;
            }
            location = location->left_Child_;
        }
    }
    insert(location);
    return true;
}
template <class T>
bool R_BTree<T>::insert(R_BTreeNode<T> *val)
{
    //case 0:root==null
    if (GetRoot() == nullptr)
    {
        val->is_Rad_ = false;
        Pre_root->left_Child_ = val;
        return true;
    }
    else if (val == GetRoot())
    {
        val->is_Rad_ = false;
        return true;
    }
    assert(val->GetParent() != nullptr);
    //case 1:fathre is black
    if (!val->GetParent()->is_Rad_)
    {
        return true;
    }
    //case 2:fathre is rad && uncle is rad
    if (val->GetParent()->is_Rad_ && val->GetUncle() && val->GetUncle()->is_Rad_)
    {
        val->GetParent()->is_Rad_ = false;
        val->GetUncle()->is_Rad_ = false;
        val->GetAncestor()->is_Rad_ = true;
        insert(val->GetAncestor());
        return true;
    }
    //case 3:fathre is rad && uncle is black ans val is a left_child
    if (val->GetParent()->isLeftChild())
    {
        if (val->GetParent()->is_Rad_ && !val->isLeftChild())
        {
            auto temp = val->GetParent();
            Left_rotate(val->GetParent());
            insert(temp);
            return true;
        }
        if (val->is_Rad_ && val->isLeftChild())
        {
            assert(val->GetAncestor());
            bool temp_color = val->GetParent()->is_Rad_;
            val->GetParent()->is_Rad_ = val->GetAncestor()->is_Rad_;
            val->GetAncestor()->is_Rad_ = temp_color;
            Right_rotate(val->GetAncestor());
            return true;
        }
    }
    else
    {
        if (val->GetParent()->is_Rad_ && val->isLeftChild())
        {
            auto temp = val->GetParent();
            Right_rotate(val->GetParent());
            insert(temp);
            return true;
        }
        if (val->is_Rad_ && !val->isLeftChild())
        {
            assert(val->GetAncestor());
            bool temp_color = val->GetParent()->is_Rad_;
            val->GetParent()->is_Rad_ = val->GetAncestor()->is_Rad_;
            val->GetAncestor()->is_Rad_ = temp_color;
            Left_rotate(val->GetAncestor());
            return true;
        }
    }
    std::__throw_invalid_argument("R_B Tree insert an invaild argument!");
}

template <class T>
void R_BTree<T>::delete_node(const T &val)
{
    R_BTreeNode<T> *target= search(val);
    if (target != nullptr)
        delete_node(target);
    else
    std::cout << "No such node which val has the value [" << val << "]" << std::endl;
}

template <class T>
void R_BTree<T>::delete_node(R_BTreeNode<T> *val, bool delete_alternative)
{
    R_BTreeNode<T> *alternative = searchAlternative(val);
    T *temp_val = &val->val_;
    val->val_ = alternative->val_;
    alternative->val_ = *temp_val;

    //case 1:alternative is a red node
    if (alternative->is_Rad_)
    {
        if (delete_alternative)
            remove_a_node(alternative);
        return;
    }
    //case 2: alternative is a black node
    //case 2.1 alternative has left_child
    if (alternative->left_Child_ != nullptr)
    {
        alternative->val_ = alternative->left_Child_->val_;
        remove_a_node(alternative->left_Child_);
        return;
    }
    //case 2.1 alternative has right_child
    if (alternative->right_Child_ != nullptr)
    {
        alternative->val_ = alternative->right_Child_->val_;
        remove_a_node(alternative->right_Child_);
        return;
    }
    //case 2.3:alternative has no child
    //csse 2.3.1:alterantive's S is a rad node
    if (alternative->GetBrother() && alternative->GetBrother()->is_Rad_)
    {
        bool temp_color = alternative->GetParent()->is_Rad_;
        alternative->GetParent()->is_Rad_ = alternative->GetBrother()->is_Rad_;
        alternative->GetBrother()->is_Rad_ = temp_color;
        if (alternative->isLeftChild())
        {
            Left_rotate(alternative->GetParent());
        }
        else
        {
            Left_rotate(alternative->GetParent());
        }
        delete_node(alternative);
        return;
    }
    //csse 2.3.2:alterantive's S is a black node
    //csse 2.3.2.1:alterantive's far Newphew is a red node
    if (alternative->GetFar_Nephew() && alternative->GetFar_Nephew()->is_Rad_)
    {
        alternative->is_Rad_ = false;
        bool temp_color = alternative->GetParent()->is_Rad_;
        alternative->GetParent()->is_Rad_ = alternative->GetBrother()->is_Rad_;
        alternative->GetBrother()->is_Rad_ = temp_color;
        if (alternative->isLeftChild())
        {
            Left_rotate(alternative->GetParent());
        }
        else
        {
            Right_rotate(alternative->GetParent());
        }
        if (delete_alternative)
            remove_a_node(alternative);
        return;
    }
    //csse 2.3.2.2:alterantive's far Newphew is a black node  &&   near Newphew is a black node
    if (alternative->GetNear_Nephew() && alternative->GetNear_Nephew()->is_Rad_)
    {
        alternative->GetNear_Nephew()->is_Rad_ = alternative->GetParent()->is_Rad_;
        alternative->GetParent()->is_Rad_ = false;
        if (alternative->isLeftChild())
        {
            Right_rotate(alternative->GetBrother());
            Left_rotate(alternative->GetParent());
        }
        else
        {
            Left_rotate(alternative->GetBrother());
            Right_rotate(alternative->GetParent());
        }
        remove_a_node(alternative);
        return;
    }
    //csse 2.3.2.3:alterantive's parent is a black node
    if (!alternative->GetParent()->is_Rad_)
    {
        alternative->GetBrother()->is_Rad_ = true;
        remove_a_node(alternative);
        return;
    }
    //csse 2.3.2.3:alterantive's parent is a rad node
    if (alternative->GetParent()->is_Rad_)
    {
        alternative->GetBrother()->is_Rad_ = true;
        alternative->GetParent()->is_Rad_ = false;
        remove_a_node(alternative);
        return;
    }
}
#endif