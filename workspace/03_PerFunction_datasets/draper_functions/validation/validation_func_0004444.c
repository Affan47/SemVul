ShowRlist(FILE *fp,struct Rlist *list)

{ struct Rlist *rp;

fprintf(fp," {");

for (rp = list; rp != NULL; rp=rp->next)
   {
   fprintf(fp,"\'");
   ShowRval(fp,rp->item,rp->type);
   fprintf(fp,"\'");

   if (rp->next != NULL)
      {
      fprintf(fp,",");
      }
   }
fprintf(fp,"}");
}
