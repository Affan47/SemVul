elhash_bigger()
{ int oldsize = web.elhashsize;
  struct element ** oldtable;
  int n;

  if ( web.elhashsize == 0 )
  { web.elhashsize = 4096;
    web.elhashmask = 0xFFF;
  }
  else
  {
    web.elhashmask |= web.elhashsize;
    web.elhashsize *= 2;
  }

  oldtable = web.elhashtable;
  web.elhashtable = (struct element **)mycalloc(web.elhashsize,sizeof(struct element*));


  web.elhashcount = 0;
  for ( n = 0 ; n < oldsize ; n++ )
    if ( oldtable[n] && (oldtable[n] != ELHASH_FREE) )
      elhash_insert(oldtable[n]->self_id,oldtable[n]);
}
