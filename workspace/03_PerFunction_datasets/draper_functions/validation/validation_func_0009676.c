FindFirstSets(lemp)
struct lemon *lemp;
{
  int i;
  struct rule *rp;
  int progress;

  for(i=0; i<lemp->nsymbol; i++){
    lemp->symbols[i]->lambda = FALSE;
  }
  for(i=lemp->nterminal; i<lemp->nsymbol; i++){
    lemp->symbols[i]->firstset = SetNew();
  }


  do{
    progress = 0;
    for(rp=lemp->rule; rp; rp=rp->next){
      if( rp->lhs->lambda ) continue;
      for(i=0; i<rp->nrhs; i++){
         if( rp->rhs[i]->lambda==FALSE ) break;
      }
      if( i==rp->nrhs ){
        rp->lhs->lambda = TRUE;
        progress = 1;
      }
    }
  }while( progress );


  do{
    struct symbol *s1, *s2;
    progress = 0;
    for(rp=lemp->rule; rp; rp=rp->next){
      s1 = rp->lhs;
      for(i=0; i<rp->nrhs; i++){
        s2 = rp->rhs[i];
        if( s2->type==TERMINAL ){
          progress += SetAdd(s1->firstset,s2->index);
          break;
	}else if( s1==s2 ){
          if( s1->lambda==FALSE ) break;
	}else{
          progress += SetUnion(s1->firstset,s2->firstset);
          if( s2->lambda==FALSE ) break;
	}
      }
    }
  }while( progress );
  return;
}
