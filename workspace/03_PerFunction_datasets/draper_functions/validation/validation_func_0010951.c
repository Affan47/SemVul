collect_processor(void *data, void *proc_data)
{
     struct table_entry *t = data;
     struct collect_data *cd = proc_data;
     Symbol *s;
     for (s = t->sym; s; s = s->next) {
	  if (cd->sel(s)) {
	       if (cd->sym)
		    cd->sym[cd->index] = s;
	       cd->index++;
	  }
     }
     return true;
}
