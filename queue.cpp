#include <iostream>
#include "queue.h"
#include "qtype.h"


Queue* init(void) {
	Queue* q = new Queue; //메모리 할당? 해주고
	q->head = nullptr;
	return q;
}


void release(Queue* queue) {
	Node* free = queue->head;

	//노드가 많으니 반복문
	while (free) {
		Node* nextfree = free->next;
		delete free; //얘만 nfree에 둘까..?
		free = nextfree;
	}
}


Node* nalloc(Item item) {
	// Node 생성, item으로 초기화
	Node* node = new Node; //메모리 공간에 노드 할당하고!
	node->item = item; //데이터 넣고!
	node->next = nullptr; //초기화!
	return node;
}


void nfree(Node* node) {
	return;
}


Node* nclone(Node* node) {
	return NULL;
}


Reply enqueue(Queue* queue, Item item) {
	Reply reply = { false, NULL };
	Node* inode = nalloc(item); //일단 노드 생성 하고

	//1. 이 아이템이? 처음 들어가냐(최초의 노든가?) 
	if (queue->head == nullptr) {
		queue->head = inode;
	}
	else {
		Node* bef = nullptr;
		Node* now = queue->head;
		while (now != nullptr && now->item.key <= item.key) {
			bef = now;
			now = now->next;
		}
		if (bef == nullptr) {
			inode->next = queue->head;
			queue->head = inode;
		}
		else {
			inode->next = now;
			bef->next = inode;
		}
	}
	reply.success = true; //연산 수행완료
	reply.item = item;
	return reply;
}

Reply dequeue(Queue* queue) {
	if (queue->head == nullptr) 
	{
		Reply reply = { false, NULL };
		return reply;
	}
	Node* del = queue->head;
	queue->head = queue->head->next;

	Item a = del->item;
	delete del;
	Reply reply = { true, a };
	return reply;
}

Queue* range(Queue* queue, Key start, Key end) {
	return NULL;
}
