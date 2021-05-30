
//红黑树
/*
红黑树为什么常用？
    1.以key-value：
        查找的性能很快，时间复杂度O(logn)
    2.通过中序遍历
        中序遍历是顺序的

红黑树的应用：
    1.Linux进程调度CFS
    2.Linux内存管理
    3.Nginx Timer事件管理
    4.Epoll事件块的管理
*/

#define RED 0
#define BLACK 1

typedef int KEY_TYPE;

typedef struct _rbtree_node {
    unsigned char color;
    struct rbtree_node *parent;
    struct rbtree_node *left;
    struct rbtree_node *right;

    KEY_VALUE key;
}rbtree_node;

struct rbtree {
    rbtree_node *root;
    rbtree_node *nil;
}

// rotate

void rbtree_left_rotate(rbtree *T, rbtree_node *x) {
    if (x == NULL) return;

    rbtree_node *y = x->right;
    
    x->right = y->left;
    if (y->left != T->nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == T->nil) {
        T->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void rbtree_right_rotate(rbtree *T, rbtree_node *y) {
     if (y == NULL) return;

    rbtree_node *x = y->left;
    
    y->left = x->right;
    if (x->right != T->nil) {
        x->right->parent = y;
    }

    x->parent = y->parent;
    if (y->parent == T->nil) {
        T->root = x;
    } else if (y == y->parent->left) {
        y->parent->right = x;
    } else {
        y->parent->left = x;
    }

    x->left = y;
    y->parent = x;
}

//添加的时候
/*
    1.在插入一个节点以前，是一个红黑树，怎么证明一个树是红黑树，用归纳法
    2.插入节点的颜色，是红色更容易满足红黑树的性质
    3.插入时违背的是红黑树的性质4，当前节点是红色，父节点也是红色
*/

void rbtree_insert_fixup(rbtree *T, rbtree_node *z) {
    while (z->parent->color == RED) {

        if (z->parent == z->parent->parent->left) {

            y = z->parent->parent->right;
            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;

                z = z->parent->parent;
            } else { //叔父节点是黑色的
                
                if (z == z->parent->right) {
                    z = z->parent;
                    rbtree_left_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbtree_right_rotate(T, z->parent->parent);
            }
        }
    }
}

void rbtree_insert(rbtree *T, rbtree_node *z) {
    rbtree_node *y = T->nil;
    rbtree_node *x = T->nil;

    while (x != T->nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else if (z->key > x->key) {
            x = x->right;
        } else {
            // exists
            return;
        }
    }

    z->parent = y;
    if (y->parent == T->nil) {
        T->root = z;
    } else if (z->key < y->key) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->color = RED;
}