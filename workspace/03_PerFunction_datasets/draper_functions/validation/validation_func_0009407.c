disp_filter_vec(const char* vecname)
{
  fl_vecs_t* vec;
  arglist_t* ap;

  for (vec = filter_vec_list; vec->vec; vec++) {
    if (case_ignore_strcmp(vec->name, vecname)) {
      continue;
    }
    printf("	%-20.20s  %-50.50s\n",
           vec->name, vec->desc);
    for (ap = vec->vec->args; ap && ap->argstring; ap++) {
      if (!(ap->argtype & ARGTYPE_HIDDEN))
        printf("	  %-18.18s    %-.50s %s\n",
               ap->argstring, ap->helpstring,
               (ap->argtype&ARGTYPE_REQUIRED)?"(required)":"");
    }
  }
}
