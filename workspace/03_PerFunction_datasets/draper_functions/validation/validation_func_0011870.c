set_vcl_reason(struct net_t *np, int32 vclflg)
{
 int32 reason;

 if (np->nwid == 1)
  {
   if (vclflg == vcl_verilog_strength) reason = strength_value_change;
   else
    {
     if (np->ntyp >= NONWIRE_ST) reason = sregister_value_change;
     else reason = logic_value_change;
    }
  }
 else
  {
   if (np->ntyp == N_INT) reason = integer_value_change;
   else if (np->ntyp == N_TIME) reason = time_value_change;
   else
    {
     if (np->ntyp >= NONWIRE_ST) reason = vregister_value_change;
     else reason = vector_value_change;
    }
  }
 return(reason);
}
