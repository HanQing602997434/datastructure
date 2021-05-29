
//链表

//节点定义
struct link_node {
    struct link_node* prev;
    struct link_node* next;

    int value;  
};

//判断链表是否有环
/*
    基本思路：快慢指针，快指针每次移动两个节点，慢指针每次移动一个节点
*/
bool is_loop(struct link_node* head) {
    struct link_node* fast = head;
    struct link_node* slow = head;
    while (fast != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow) {
            return true;
        }
    }
}

//判断两个链表是否相交
/*
    基本思路：求出两个链表的长度m, n，将长的链表往后移动|m - n|个节点，然后一趟循环，时间复杂度O(m + n)
*/

bool is_intersect(struct link_node* list1_head, struct link_node* list2_head) {
    int m = 0, n = 0, movestep = 0;
    struct link_node* node = list1_head;
    while (node != NULL) {
        node = node->next;
        m += 1;
    }
    node = list2_head;
    while (node != NULL) {
        node = node->next;
        n += 1;
    }
    
    struct link_node* long_node = NULL;
    struct link_node* short_node = NULL;
    if (m > n) {
        movestep = m - n;
        long_node = list1_head;
        short_node = list2_head;
       
    } else {
        movestep = n - m;
        long_node = list2_head;
        short_node = list1_head;
    }

    while (movestep > 0) {
        node = node->next;
        movestep -= 1;
    }

    while (long_node != NULL && short_node != NULL) {
        if (long_node == short_node) {
            return true
        }
    }

    return false;
}

//单链表如何找到倒数第n个节点
/*
    基本思路：定义两个指针，一个指针先走n个节点，然后一起走，判断是否会相等
*/

struct link_node* find_last_n_node(struct link_node* head) {
    struct link_node* front = head;
    struct link_node* behind = head;

    while (n > 0) {
        front = front->next;
        n -= 1;
    }

    while (front != NULL) {
        front = front->next;
        behind = behind->next;
    }

    return behind;
}

//链表反转
/*
    基本思路：头插法
*/
struct link_node* reverse_list(struct link_node* head) {
    struct link_node* prev = NULL;
    struct link_node* current = head;
    struct link_node* next = NULL;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
}