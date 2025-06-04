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
	Node* node = new Node; //메모리 공간에 노드 할당하고
	node->item = item; //데이터 넣고
	node->next = nullptr; //초기화
	return node;
}


void nfree(Node* node) {
	return;
}

//원본을 삭제해도 복사본이 남게 깊은복사를 해라..?
Node* nclone(Node* node) {

	if (node == nullptr) {
		return nullptr;
	}
	Item item;
	//키복사
	item.key = node->item.key;

	// 일단 타입변환
	int* original = (int*)node->item.value;

	//잘 되었는지확인
	if (original != nullptr) {

		//형변환한 포인터를 담을 변수 만들어주고?
		int* i = new int;
		//깊은 복사
		*i = *original;

		//썻으니 재변환
		item.value = (void*)i;
	}
	else {
		item.value = nullptr;
	}
	return nalloc(item);
}

// 키가 이미 존재하면 덮어쓰기를 해라..?
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
			// 여기다 조건을 하나 더 넣어야함
			//(key=10, value="abc"), (key=10, value="xyz")가 차례로 수행된다면, 즉 키가 같다면
			if (now->item.key == item.key) {
				//value만 덮어써라
				now->item.value = item.value;
				return { true, item };
			}
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

//키의 시작부터 끝까지 복사..
Queue* range(Queue* queue, Key start, Key end) {
	//새로운 큐 만들고 처음노드 시작.
	Queue* nq = init();
	Node* now = queue->head;
	//반복
	while (now) {
		// 현재 노드가 키의 범위
		if (now->item.key >= start && now->item.key <= end) {
			nclone(now); //깊은복사
		}
		now = now->next;
	}
	return nq;
}
