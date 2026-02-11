Op_3(WamWord prec_word, WamWord specif_word, WamWord oper_word)
{
  int atom_op;
  int prec;
  int atom_specif;
  int i;
  int type, left, right;


  atom_op = Rd_Atom_Check(oper_word);
  prec = Rd_Integer_Check(prec_word);
  if (prec < 0 || prec > MAX_PREC)
    Pl_Err_Domain(domain_operator_priority, prec_word);

  atom_specif = Rd_Atom_Check(specif_word);

  for (i = 0; i < 7 && atom_specif != atom_specif_tbl[i]; i++)
    ;

  switch (i)
    {
    case FX:
    case FY:
      type = PREFIX;
      left = 0;
      right = (i == FX) ? prec - 1 : prec;
      break;

    case XF:
    case YF:
      type = POSTFIX;
      left = (i == XF) ? prec - 1 : prec;
      right = 0;
      break;

    case XFX:
    case XFY:
    case YFX:
      type = INFIX;
      left = (i == XFX || i == XFY) ? prec - 1 : prec;
      right = (i == XFX || i == YFX) ? prec - 1 : prec;
      break;

    default:
      Pl_Err_Domain(domain_operator_specifier, specif_word);
      type = left = right = 0;
    }

  if (type != PREFIX
      && Check_Oper(atom_op, (type == POSTFIX) ? INFIX : POSTFIX))
    Pl_Err_Permission(permission_operation_create, permission_type_operator,
		      oper_word);

  if (atom_op == ATOM_CHAR(','))
    Pl_Err_Permission(permission_operation_modify,
		      permission_type_operator, oper_word);

  if (prec > 0)
    Create_Oper(atom_op, type, prec, left, right);
  else
    Delete_Oper(atom_op, type);
}
