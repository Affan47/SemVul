gt_firstcodes_tab_delete(GtFirstcodesspacelog *fcsl,GtFirstcodestab *fct)
{
  gt_firstcodes_samples_delete(fcsl,fct);
  gt_str_delete(fct->outfilenameleftborder);
  fct->outfilenameleftborder = NULL;
#ifdef _LP64
  GT_FREEARRAY(&fct->bitchangepoints,GtUlong);
#endif
}
