static rsRetVal qDestructLinkedList(qqueue_t __attribute__((unused)) *pThis)
{
	DEFiRet;

	queueDrain(pThis);


	RETiRet;
}
