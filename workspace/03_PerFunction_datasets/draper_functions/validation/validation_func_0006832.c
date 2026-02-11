convert_tree_comp_to_rtx (enum tree_code tcode, int unsignedp)
{
  enum rtx_code code;
  switch (tcode)
    {
    case EQ_EXPR:
      code = EQ;
      break;
    case NE_EXPR:
      code = NE;
      break;
    case LT_EXPR:
      code = unsignedp ? LTU : LT;
      break;
    case LE_EXPR:
      code = unsignedp ? LEU : LE;
      break;
    case GT_EXPR:
      code = unsignedp ? GTU : GT;
      break;
    case GE_EXPR:
      code = unsignedp ? GEU : GE;
      break;
    case UNORDERED_EXPR:
      code = UNORDERED;
      break;
    case ORDERED_EXPR:
      code = ORDERED;
      break;
    case UNLT_EXPR:
      code = UNLT;
      break;
    case UNLE_EXPR:
      code = UNLE;
      break;
    case UNGT_EXPR:
      code = UNGT;
      break;
    case UNGE_EXPR:
      code = UNGE;
      break;
    case UNEQ_EXPR:
      code = UNEQ;
      break;
    case LTGT_EXPR:
      code = LTGT;
      break;

    default:
      gcc_unreachable ();
    }
  return code;
}
