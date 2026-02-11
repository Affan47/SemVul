DelSubGraph(Node* p) {
	return p == NULL || (DelNode(p) && (p->up || DelSubGraph(p->next)));
}
