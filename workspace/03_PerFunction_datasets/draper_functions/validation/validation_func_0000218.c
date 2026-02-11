registerRead (int reg)
{
  switch (gMode)
    {
    case UMAX_PP_PARPORT_ECP:
      return ECPregisterRead (reg);
    case UMAX_PP_PARPORT_BYTE:
      DBG (0, "STEF: gMode BYTE in registerRead !!\n");
      return 0xFF;
    case UMAX_PP_PARPORT_EPP:
      return EPPregisterRead (reg);
    case UMAX_PP_PARPORT_PS2:
      DBG (0, "STEF: gMode PS2 in registerRead !!\n");
      return PS2registerRead (reg);
    default:
      DBG (0, "STEF: gMode unset in registerRead !!\n");
      return 0xFF;
    }
}
