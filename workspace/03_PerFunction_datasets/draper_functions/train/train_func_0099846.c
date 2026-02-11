subdiv_fprint(FILE *fout, cell c){
#ifdef LOG_PRINT
  fprintf(fout,"\n")
#endif
;
  while(c!=0){
      cell_fprint(fout,c);
      c=cell_next(c);
  }

}
