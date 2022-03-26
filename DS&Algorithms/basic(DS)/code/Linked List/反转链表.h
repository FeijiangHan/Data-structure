#pragma once

/* ��ת���� */

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
        // �ݹ��������
        if (head == nullptr || head->next == nullptr)
            return head;

        // �ݹ����
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

    // ˼·��next��ǰ����cur����һ��λ�ã�cur����һ��ָ��prev
    // ��ֹ��������curָ�����һ���ڵ�ĺ�һ���㣨NULLʱ��
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;
        ListNode* prev = nullptr;
        ListNode* next;

        while (cur)
        {
            // ��ʱcur����Ϊnull�����һ��Ҳ��ָ�����һ���ڵ�
            next = cur->next;

            // ������ϵ
            cur->next = prev;

            // �ƶ�
            prev = cur;
            cur = next;
        }
        // ���գ�cur == nullptr�� prevָ�����ڵ�

        return prev;
    }
};