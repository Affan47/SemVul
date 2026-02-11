dump() const
{
    list_iterator_t<depend_t> iter;

    fprintf(stderr, "Depend stack dump:\n");
    for (iter = depend_stack_.last() ; *iter ; --iter)
    {
    	fprintf(stderr, "    [%ld]", (*iter)->lineno_);
    	(*iter)->deltas_->foreach(dump_one_delta, 0);
	fputc('\n', stderr);
    }
}
