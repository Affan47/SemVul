do_clone(area_s *p)
{
	if (p) {
		area_s *q = new area_s;
		q->left = do_clone(p->left);
		q->right = do_clone(p->right);
		q->start = p->start->clone();
		q->end = p->end->clone();
		return q;
	} else {
		return NULL;
	}
}
