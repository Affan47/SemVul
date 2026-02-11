gkm_manager_find_one_by_attributes (GkmManager *self, GkmSession *session,
                                    CK_ATTRIBUTE_PTR attrs, CK_ULONG n_attrs)
{
	Finder finder = { 0, };

	g_return_val_if_fail (GKM_IS_MANAGER (self), NULL);
	g_return_val_if_fail (attrs || !n_attrs, NULL);

	finder.accumulator = accumulate_one;
	finder.results = NULL;
	finder.manager = self;
	finder.attrs = attrs;
	finder.n_attrs = n_attrs;
	finder.session = session;

	find_for_attributes (&finder);

	return finder.results;
}
