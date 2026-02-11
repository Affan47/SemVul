BigDecimal_IsFinite(VALUE self)
{
    Real *p = GetVpValue(self,1);
    if(VpIsNaN(p)) return Qfalse;
    if(VpIsInf(p)) return Qfalse;
    return Qtrue;
}
