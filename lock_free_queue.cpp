
typedef struct {
	entry *next;
	int data;
}entry;

entry *head, tail;

int en_queue(int x)
{
	entry *p = NULL;
	entry *q = (entry *)malloc(sizeof(entry));
	
	if (!q)
		return -1;
	p->data = x;
	p->next = NULL;
	
	do {
		p = tail;
	} while (CAS(p->next, NULL, q) != TRUE);
	
	CAS(tail, p, q);
	return 0;
}

entry *de_queue(void)
{
	entry p = NULL;
	
	do {
		p = head;
		if (p->next == NULL)
			return NULL;
		
	} while(CAS(head, p, head->next) != TRUE);
	return p;
}






