__dup_concat(int32 repcnt, struct expr_t *catndp)
{
 register int32 w;
 struct expr_t *dupndp, *newndp, *end_ndp;


 for (newndp = NULL, w = 0; w < repcnt; w++)
  {

   if (w < repcnt - 1) dupndp = __copy_expr(catndp); else dupndp = catndp;
   if (newndp == NULL) newndp = dupndp;
   else
    {
     end_ndp = __find_catend(dupndp);
     end_ndp->ru.x = newndp;
     newndp = dupndp;
    }
  }
 return(newndp);
}
