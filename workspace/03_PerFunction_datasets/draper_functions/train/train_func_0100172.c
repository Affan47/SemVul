pp_cxx_type_id (cxx_pretty_printer *pp, tree t)
{
  pp_flags saved_flags = pp_c_base (pp)->flags;
  pp_c_base (pp)->flags |= pp_c_flag_abstract;

  switch (TREE_CODE (t))
    {
    case TYPE_DECL:
    case UNION_TYPE:
    case RECORD_TYPE:
    case ENUMERAL_TYPE:
    case TYPENAME_TYPE:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
    case UNBOUND_CLASS_TEMPLATE:
    case TEMPLATE_TEMPLATE_PARM:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_PARM_INDEX:
    case TEMPLATE_DECL:
    case TYPEOF_TYPE:
    case UNDERLYING_TYPE:
    case DECLTYPE_TYPE:
    case TEMPLATE_ID_EXPR:
      pp_cxx_type_specifier_seq (pp, t);
      break;

    case TYPE_PACK_EXPANSION:
      pp_cxx_type_id (pp, PACK_EXPANSION_PATTERN (t));
      pp_cxx_ws_string (pp, "...");
      break;

    default:
      pp_c_type_id (pp_c_base (pp), t);
      break;
    }

  pp_c_base (pp)->flags = saved_flags;
}
