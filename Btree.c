
//B树
/*
    B树就是多叉树

    B树的性质
        一棵M阶B树T，满足以下条件：
            1.每个节点至多拥有M棵子树
            2.根节点至少有两棵子树
            3.除了根节点以外，其余每个分支节点至少拥有M/2棵子树
            4.所有的叶节点都在同一层
            5.有k棵子树的分支节点则存在k-1个关键字，关键字按照递增顺序进行排序
            6.关键字数量满足ceil(M/2)-1<=n<=M-1
*/

#define M 6
#define DEGREE (M/2)

typedef int KEY_VALUE;

struct btree_node {
    KEY_VALUE *keys;
    struct btree_node **childrens;

    int num;
    int leaf;
}

struct btree {
    struct btree_node *root;
}

//在添加key的时候
/*
    分裂有两种情况：
    1.只有根节点的时候，1分裂成3个节点
    2.其余的情况，1分裂2个节点
    所以建议阶数M定义一个偶数，便于分裂

    插入的时候，两个步骤
    1.找到对应的节点
    2.对节点的key对比，找到合适的位置
    插入的数据是插在叶子节点上面
*/

struct btree_node *btree_create_node(struct rbtree *T) {

}

//x分裂节点的父节点，i表示x的第几个子树分裂
void btree_split_child(struct btree *T, struct btree_node *x, int i) {
    struct btree_node *y = x->childrens[i];
    
    struct btree_node *z = (struct btree_node*)malloc(struct btree_node);
    for (j = 0; j < DEGREE - 1; ++j) {
        z[j].keys = y[j].keys;
    }

    if (y->leaf == 0) {
        for (j = 0; j = DEGREE; ++j) {
            z[j].childrens = y[j].childrens;
        }
    }
    z->num = y->num;

}

void btree_insert_nofull(struct btree *T, struct btree_node *x, KEY_VALUE k) {
    int i = x->num;

    if (x->leaf == 1) {

    } else {
        //从节点后面开始找
        while (i >= 0; x->keys[i] > k) --i;

        if (x->childrens[i + 1]->num == M - 1) {
            btree_split_child(T, x->childrens[i + 1], k);
        }

        btree_insert_nofull(T, x->childrens[i + 1], k);
    }
}

void btree_insert(struct btree *T, KEY_VALUE key) {
    struct btree_node *r = T->root;
    if (r->num == M - 1) {
        struct btree_node *node = btree_create_node(T);

        T->root = node;
        node->childrens[0] = r;
        btree_split_child(T, node, 0);
    } else {

    }
}

//B树删除
/*
    删除的时候，删除的值是在叶子节点上面
    1.如果idx子树等于ceil(M/2)-1
        A.借位 先借位
            a.从idx-1借 大于ceil(M/2)-1 先从前面借
            b.从idx+1借 大于ceil(M/2)-1 前面没有从后面借
        B.合并 借不来就合并
            {childs[idx].keys} {keys[idx]} {childs[idx+1].keys}

    2.idx子树 > ceil(M/2)-1 直接删除

    删除的步骤：
    1.找到对应的子树
    2.删除
*/

void btree_merge(struct btree *T, struct btree_node *x, int idx) {
    //{x->childs[idx].keys} {keys[idx]} {x->childs[idx+1].keys}
}

void rbtree_delete_key(struct btree *T, struct btree_node *x, KEY_VALUE k) {
    int idx = 0;
    while (idx < x->num && k > x->keys[idx]) ++idx;
    
    if (k == x->keys[idx]) {
        if (x->leaf) {

        } else if (x->childrens[idx]->num >= DEGREE) {

        } else if (x->childrens[idx + 1]->num >= DEGREE) {

        } else {
            
            btree_merge(T, x, idx);

            btreee_delete_key();
        }
    }
}