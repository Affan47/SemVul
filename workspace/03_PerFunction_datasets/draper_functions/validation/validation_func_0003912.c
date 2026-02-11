centry_urgency_contribution(int slots, const char *name, double value,
                            const lListElem *centry)
{
   double contribution, weight;
   const char *strval;
   u_long32 complex_type;

   DENTER(TOP_LAYER, "centry_urgency_contribution");

   if (!centry ||
       !(strval = lGetString(centry, CE_urgency_weight)) ||
       !(parse_ulong_val(&weight, NULL, TYPE_INT, strval, NULL, 0))) {
      DPRINTF(("no contribution for attribute\n"));
      DRETURN(0);
   }

   switch ((complex_type=lGetUlong(centry, CE_valtype))) {
   case TYPE_INT:
   case TYPE_TIM:
   case TYPE_MEM:
   case TYPE_BOO:
   case TYPE_DOUBLE:
      contribution = value * weight * slots;
      DPRINTF(("   %s: %7f * %7f * %d    ---> %7f\n", name, value, weight, slots, contribution));
      break;

   case TYPE_STR:
   case TYPE_CSTR:
   case TYPE_HOST:
   case TYPE_RESTR:
      contribution = weight;
      DPRINTF(("   %s: using weight as contrib ---> %7f\n", name, weight));
      break;

   default:
      ERROR((SGE_EVENT, MSG_SGETEXT_UNKNOWN_ATTR_TYPE_U, sge_u32c(complex_type)));
      contribution = 0;
      break;
   }

   DRETURN(contribution);
}
