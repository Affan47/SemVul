addrtlasg( Figure, VexAtom, Type )

  rtlfig_list *Figure;
  vexexpr     *VexAtom;
  int          Type;
{
  rtlasg_list *Assign;

  Assign = allocrtlasg();

  Assign->VEX_ATOM   = VexAtom;
  Assign->TYPE       = Type;
  Assign->LAST_BIVEX = &Assign->BIVEX;

  Assign->NEXT   = Figure->ASSIGN;
  Assign->PREV   = &Figure->ASSIGN;

  if ( Figure->ASSIGN != (rtlasg_list *)0 )
  {
    Figure->ASSIGN->PREV = &Assign->NEXT;
  }

  Figure->ASSIGN = Assign;

  return( Assign );
}
