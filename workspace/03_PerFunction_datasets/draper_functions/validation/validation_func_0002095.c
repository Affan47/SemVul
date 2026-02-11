Fd_Element_Var_V_To_I(Range *i, Range *v, WamWord **l)
{
  WamWord *fdv_adr;
  long n;
  int j;

  Vector_Allocate(i->vec);
  Vector_Empty(i->vec);


  n = (long) *l;

  for (j = 1; j <= n; j++)
    {
      fdv_adr = l[j];
      if (!Range_Test_Null_Inter(Range(fdv_adr), v))
	  Vector_Set_Value(i->vec, j);
    }

  Range_From_Vector(i);
}
