free_or_tmp(Or_tmp *op)
{
  if(op != NULL){
    if(op->next == NULL){
      free(op);
    }else{
      free_or_tmp(op->next);
      free(op);
    }
  }
}
