free_hash_table(hash_table *table, void (*func)(void *))
{
      unsigned i;
      bucket *ptr, *temp;


      if(func || !table->pool) {
	  for (i=0;i<table->size; i++)
	  {
	      ptr = (table->table)[i];
	      while (ptr)
	      {
		  temp = ptr;
		  ptr = ptr->next;
		  if (func)
		      func(temp->data);
		  if(!table->pool) {
		      free(temp->key);
		      free(temp);
		  }
	      }
	  }
      }


      if(table->pool) {
	  free_mpool(table->pool);
	  table->pool = NULL;
      } else {
	  free(table->table);
      }
      table->table = NULL;
      table->size = 0;
}
