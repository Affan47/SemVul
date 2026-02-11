charput(struct Global *global, int c)
{


  if (global->parmp >= &global->parm[NPARMWORK]) {
    cfatal(global, FATAL_MACRO_AREA_OVERFLOW);
    return(FPP_WORK_AREA_OVERFLOW);
  }
  *global->parmp++ = c;
  return(FPP_OK);
}
