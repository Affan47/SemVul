stackTopType(Renderer *p){
  if( p->nStack<=0 ) return 0;
  return aMarkup[p->aStack[p->nStack-1].iCode].iType;
}
