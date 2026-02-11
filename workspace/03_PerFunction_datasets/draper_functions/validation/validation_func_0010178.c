scm_i_procedure_arity (SCM proc)
{
  int a = 0, o = 0, r = 0;
  if (SCM_IMP (proc))
    return SCM_BOOL_F;
 loop:
  switch (SCM_TYP7 (proc))
    {
    case scm_tc7_subr_1o:
      o = 1;
    case scm_tc7_subr_0:
      break;
    case scm_tc7_subr_2o:
      o = 1;
    case scm_tc7_subr_1:
    case scm_tc7_dsubr:
    case scm_tc7_cxr:
      a += 1;
      break;
    case scm_tc7_subr_2:
      a += 2;
      break;
    case scm_tc7_subr_3:
      a += 3;
      break;
    case scm_tc7_asubr:
    case scm_tc7_rpsubr:
    case scm_tc7_lsubr:
      r = 1;
      break;
    case scm_tc7_lsubr_2:
      a += 2;
      r = 1;
      break;
    case scm_tc7_smob:
      if (SCM_SMOB_APPLICABLE_P (proc))
	{
	  int type = SCM_SMOB_DESCRIPTOR (proc).gsubr_type;
	  a += SCM_GSUBR_REQ (type);
	  o = SCM_GSUBR_OPT (type);
	  r = SCM_GSUBR_REST (type);
	  break;
	}
      else
	{
	  return SCM_BOOL_F;
	}
    case scm_tc7_cclo:
      if (scm_is_eq (SCM_CCLO_SUBR (proc), scm_f_gsubr_apply))
	{
	  int type = scm_to_int (SCM_GSUBR_TYPE (proc));
	  a += SCM_GSUBR_REQ (type);
	  o = SCM_GSUBR_OPT (type);
	  r = SCM_GSUBR_REST (type);
	  break;
	}
      else
	{
	  proc = SCM_CCLO_SUBR (proc);
	  a -= 1;
	  goto loop;
	}
    case scm_tc7_pws:
      proc = SCM_PROCEDURE (proc);
      goto loop;
    case scm_tcs_closures:
      proc = SCM_CLOSURE_FORMALS (proc);
      if (scm_is_null (proc))
	break;
      while (scm_is_pair (proc))
	{
	  ++a;
	  proc = SCM_CDR (proc);
	}
      if (!scm_is_null (proc))
	r = 1;
      break;
    case scm_tcs_struct:
      if (SCM_OBJ_CLASS_FLAGS (proc) & SCM_CLASSF_PURE_GENERIC)
	{
	  r = 1;
	  break;
	}
      else if (!SCM_I_OPERATORP (proc))
	return SCM_BOOL_F;
      proc = (SCM_I_ENTITYP (proc)
	      ? SCM_ENTITY_PROCEDURE (proc)
	      : SCM_OPERATOR_PROCEDURE (proc));
      a -= 1;
      goto loop;
    default:
      return SCM_BOOL_F;
    }
  return scm_list_3 (scm_from_int (a), scm_from_int (o), scm_from_bool(r));
}
