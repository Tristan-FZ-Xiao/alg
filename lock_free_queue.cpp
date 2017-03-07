
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
	q->data = x;
	q->next = NULL;
	p = tail;

	do {
		/* get tail entry itself to avoid infinited-loop when other thread
		 * suspend or dead between CAS */
		while (p->next != NULL)
			p = p->next;
	} while (CAS(p->next, NULL, q) != TRUE);
	
	/* Thread may suspend point */
	
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






