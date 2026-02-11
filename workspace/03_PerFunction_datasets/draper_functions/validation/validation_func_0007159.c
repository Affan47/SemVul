SUBR_pi(ushort code)
{
  SUBR_ENTER();

  if (NPARAM == 0)
  {
    SP->type = T_FLOAT;
    SP->_float.value = M_PI;
		SP++;
  }
  else
  {
    VALUE_conv_float(PARAM);
    PARAM->_float.value = M_PI * PARAM->_float.value;
  }
}
