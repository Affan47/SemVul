xsh_order_list_verify( xsh_order_list * list, int ny )
{
  int i ;


  for( i = 0 ; i<list->size ; i++ )
    if ( list->list[i].endy <= list->list[i].starty ) {
      list->list[i].endy = ny;
      list->list[i].starty = 1;
    }

  return ;
}
