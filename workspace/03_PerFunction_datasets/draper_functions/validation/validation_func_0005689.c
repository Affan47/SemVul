free_expr ARGS1((ex),
struct expnode *ex)
{

  if ( ex == NULL ) return;
  if ( ex->flag == NOUSERCOPY ) return;
  if ( ex->start )
  {
   struct treenode *node;
    for ( node = ex->start ; node != ex->root ; node ++  )
    {
    #ifdef XXXXXXX

      if ( node->flags & HAS_LOCALLIST )
      { struct locallist_t *locals = node->op5.locals;
        if ( locals->list )
        { if ( locals->flags & LL_PERMANENT ) free((char*)locals->list);
          else myfree((char*)locals->list);
        }
        if ( locals->flags & LL_PERMANENT )
          free((char*)locals);
        else
          myfree((char*)locals);
      }
    #endif
      if ( node->flags & HAS_STRING )
        myfree(node->op1.string);
      if ( node->flags & HAS_STRING_5 )
        myfree(node->op5.string);
    }
    myfree((char *)ex->start);
  }
  ex->root = NULL;
  ex->start = NULL;

  if ( ex->locals )
  { myfree((char*)(ex->locals->list));
    myfree((char*)(ex->locals));
  }
  ex->locals = NULL;

}
