#pragma once

namespace rtcpp {

template <typename T>
struct bst_node {
  typedef T value_type;
  bst_node* llink;
  bst_node* rlink;
  value_type key;
  int tag;
};

namespace detail {
static const int rbit = 1;
static const int lbit = 2;
}

inline
int set_lbit(int tag) noexcept
{
  return tag | detail::lbit;
}

inline
int set_rbit(int tag) noexcept
{
  return tag | detail::rbit;
}

inline
int has_null_llink(int tag) noexcept
{
  return tag & detail::lbit;
}

inline
int has_null_rlink(int tag) noexcept
{
  return tag & detail::rbit;
}

template <typename Node>
Node* inorder_successor(Node* p) noexcept
{
  if (has_null_rlink(p->tag))
    return p->rlink;

  Node* q = p->rlink;
  while (!has_null_llink(q->tag))
    q = q->llink;

  return q;
}

template <typename Node>
Node* inorder_predecessor(Node* p) noexcept
{
  if (has_null_llink(p->tag))
    return p->llink;

  Node* q = p->llink;
  while (!has_null_rlink(q->tag))
    q = q->rlink;

  return q;
}

template <typename Node>
Node* preorder_successor(Node* p) noexcept
{
  if (!has_null_llink(p->tag))
    return p->llink;

  if (!has_null_rlink(p->tag))
    return p->rlink;

  // This is a leaf node.
  Node* q = p->rlink;
  while (has_null_rlink(q->tag))
    q = q->rlink;

  return q->rlink;
}

template <typename Node>
void attach_node_left(Node* p, Node* q) noexcept
{
  // Attaches node q on the left of p. Does not check if pointers are valid.
  q->llink = p->llink;
  q->tag = has_null_rlink(q->tag) | has_null_llink(p->tag);
  p->llink = q;
  p->tag = has_null_rlink(p->tag);
  q->rlink = p;
  q->tag = set_rbit(q->tag);

  if (!has_null_llink(q->tag)) {
    Node* qs = inorder_predecessor(q);
    qs->rlink = q;
  }
}

template <typename Node>
void attach_node_right(Node* p, Node* q) noexcept
{
  // Attaches node q on the left of p. Does not check if pointers are valid.
  q->rlink = p->rlink;
  q->tag = has_null_llink(q->tag) | has_null_rlink(p->tag);
  p->rlink = q;
  p->tag = has_null_llink(p->tag);
  q->llink = p;
  q->tag = set_lbit(q->tag);

  if (!has_null_rlink(q->tag)) {
    Node* qs = inorder_successor(q);
    qs->llink = q;
  }
}

}
