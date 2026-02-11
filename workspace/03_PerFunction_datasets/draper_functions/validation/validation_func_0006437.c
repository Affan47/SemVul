px_dump(FILE *fp, const PERM *px)
#endif
{
     unsigned int      i;

     if ( ! px )
     {  fprintf(fp,"Permutation: NULL\n");      return;         }
     fprintf(fp,"Permutation: size: %u @ 0x%lx\n",px->size,(long)(px));
     if ( ! px->pe )
     {  fprintf(fp,"NULL\n");   return;         }
     fprintf(fp,"px->pe @ 0x%lx\n",(long)(px->pe));
     for ( i=0; i<px->size; i++ )
	  fprintf(fp,"%u->%u ",i,px->pe[i]);
     fprintf(fp,"\n");
}
