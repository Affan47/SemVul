G_Qtrig(Gen_node g){
  aset A=0,CP=0;
  Ivector T=0;
  int r = 0;
  Gen_node ptr;
  int nargs;
  LOCS(2);
  PUSH_LOC(A);
  PUSH_LOC(CP);
  nargs=Gen_length(g);
  if ((nargs ==0) ||
      (nargs==1  && Can_Be_Aset(Gen_elt(g,1))!=TRUE )||
      (nargs==2  && (r=Can_Be_Vector(Gen_elt(g,2),Int_T))<0)){
    POP_LOCS();
    return Rerror("Usage: Qtrig(Aset,<Int>)",g);
  }
  A=Gen_aset(Gen_elt(g,1));
  if (nargs==2 ){
    if (r==aset_r(A)) T=Gen_to_Imatrix(Gen_elt(g,2));
    else {
      POP_LOCS();
      return Rerror("Usage: Qtrig(Aset,<Int>)",g);
    }
  }
  time0=set_mark();
  CP=aset_print_subdiv(A,aset_lower_facets(A),T);


if (CP!=0){
    ptr=(g=Imatrix_to_Gen((Imatrix)Car(Car(CP))));
    while((CP=Cdr(CP))!=0){
      ptr=Gen_set_next(ptr,Imatrix_to_Gen((Imatrix)Car(Car(CP))));
    }
    g=Gen_node_to_List(g);
  }
  else g=IDND("");
  if (T!=0) Imatrix_free(T);
  POP_LOCS();
  return g;
}
