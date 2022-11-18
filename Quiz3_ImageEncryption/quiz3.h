/*  COP3530
    Quiz 3: Image Encryptor

    Student: Erik Meurrens
   
*/

#include <iostream>
#include <vector>

struct ListNode
{
    int data;
    ListNode* next;
};

ListNode* addEnd(ListNode* head, int value)
{
    ListNode* newNode = new ListNode;
    newNode -> data = value;
    newNode -> next = nullptr;
    
    if (head == nullptr)
        return newNode;
        
    ListNode* curr = head;
    while(curr -> next != nullptr)
        curr = curr -> next;
        
    curr -> next = newNode; 

    return head;
}


std::vector<int> encryptImage(ListNode* head)
{
    std::vector<int> encryptedImage;

    ListNode* currNode = head;
    ListNode* seekerNode = head;

    while (currNode != nullptr) {
        while ((seekerNode != nullptr) && (currNode->data >= seekerNode->data)) {
            seekerNode = seekerNode->next;
        }
        if (seekerNode != nullptr)
            encryptedImage.push_back(seekerNode->data);
        else
            encryptedImage.push_back(0);

        currNode = currNode->next;
        seekerNode = currNode;
    }
    
    return encryptedImage;
}