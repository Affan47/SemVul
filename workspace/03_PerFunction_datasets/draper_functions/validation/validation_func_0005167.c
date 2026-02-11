print_type(FILE * fptr,unsigned dtype,char * dptr,int offset)


#ifdef DOC
FILE *          fptr      ;
unsigned        dtype     ;
char *          dptr      ;
int		offset    ;
#endif


{

   switch (dtype) {
      case DFINTPAR:
         return fprintf( fptr, DFINT_PRFORM, *((int *)dptr+offset) );
      case DFUNSPAR:
         return fprintf( fptr, DFUNS_PRFORM, *((unsigned int *)dptr+offset) );
      case SHINTPAR:
         return fprintf( fptr, SHINT_PRFORM, *((short *)dptr+offset) );
      case SHUNSPAR:
         return fprintf( fptr, SHUNS_PRFORM, *((unsigned short *)dptr+offset) );
      case LNINTPAR:
         return fprintf( fptr, LNINT_PRFORM, *((long *)dptr+offset) );
      case LNUNSPAR:
         return fprintf( fptr, LNUNS_PRFORM, *((unsigned long *)dptr+offset) );
      case FLOATPAR:
         return fprintf( fptr, FLOAT_PRFORM, *((float *)dptr+offset) );
      case DOUBLPAR:
         return fprintf( fptr, DOUBL_PRFORM, *((double *)dptr+offset) );
      case CHAR_PAR:
         return fprintf( fptr, "%c", *(dptr+offset) );
      case STRNGPAR:
         return fprintf( fptr, "%s", *((char **)dptr+offset) );
      case BOOL_PAR:
         return fprintf( fptr, "%s", (*((BOOLEAN *)dptr+offset) ? "TRUE" : "FALSE" ));
      }

   return 0;

}
