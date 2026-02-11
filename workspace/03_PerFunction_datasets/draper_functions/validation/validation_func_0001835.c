mg_findcam(void)
{
  HPoint3 camZ;


  if (!_mgc->xstk->hasinv) {
    TmInvert(_mgc->xstk->T, _mgc->xstk->Tinv);
    _mgc->xstk->hasinv = 1;
  }

  HPt3Transform(_mgc->xstk->Tinv, (HPoint3 *)&_mgc->C2W[3][0], &_mgc->cpos);
  HPt3Transform(_mgc->xstk->Tinv, (HPoint3 *)&_mgc->C2W[2][0], &camZ);
  camZ.w = Pt3Length((Point3 *)(void *)&camZ);
  HPt3ToPt3(&camZ, &_mgc->camZ);
  _mgc->has |= HAS_CPOS;
}
