fftw_make_plan(int n, fftw_direction dir,
			 fftw_plan_node *root, int flags,
			 enum fftw_node_type wisdom_type,
			 int wisdom_signature,
			 fftw_recurse_kind recurse_kind, int vector_size)
{
     fftw_plan p = (fftw_plan) fftw_malloc(sizeof(struct fftw_plan_struct));

     p->n = n;
     p->dir = dir;
     p->flags = flags;
     fftw_use_node(root);
     p->root = root;
     p->cost = 0.0;
     p->wisdom_type = wisdom_type;
     p->wisdom_signature = wisdom_signature;
     p->recurse_kind = recurse_kind;
     p->vector_size = vector_size;
     if (recurse_kind == FFTW_VECTOR_RECURSE && vector_size > 1)
	  fftw_die("invalid vector-recurse plan attempted\n");
     p->next = (fftw_plan) 0;
     p->refcnt = 0;
     fftw_plan_cnt++;
     return p;
}
