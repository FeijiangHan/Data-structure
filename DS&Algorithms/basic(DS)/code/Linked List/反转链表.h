#pragma once

/* 翻转链表 */

class Solution {
public:

    struct ListNode
    {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int val, ListNode* n) :val(val), next(n) {}
    };


    ListNode* reverseList(ListNode* head) {
        // 递归结束条件
        if (head == nullptr || head->next == nullptr)
            return head;

        // 递归求解
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;

        return newHead;
    }
};



class Solution2 {
public:

    struct ListNode
    {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int val, ListNode* n) :val(val), next(n) {}
    };

    // 思路：next提前储存cur的下一个位置，cur的下一个指向prev
    // 终止条件就是cur指向最后一个节点的后一个点（NULL时）
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* prev = nullptr;
        ListNode* next;

        while (cur)
        {
            // 此时cur不会为null，最后一步也是指向最后一个节点
            next = cur->next;

            // 建立联系
            cur->next = prev;

            // 移动
            prev = cur;
            cur = next;
        }
        // 最终：cur == nullptr； prev指向最后节点

        return prev;
    }
};