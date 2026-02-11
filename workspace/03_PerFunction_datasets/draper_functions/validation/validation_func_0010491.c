coordsto(int from, int to))[4]
{
  WnPosition vp;
  static Transform Tmap;

  if(from == L_NONE) from = L_LOCAL;
  if(to == L_NONE) to = L_LOCAL;
  if(from == to)
    return TM3_IDENTITY;

  switch(to) {
  case L_GLOBAL: return coords2W(from);
  case L_LOCAL:
    if(!(_mgc->has & HAS_S2O)) mg_findS2O();
    switch(from) {
    case L_GLOBAL: return _mgc->xstk->Tinv;
    case L_SCREEN: return _mgc->S2O;
    }
    break;
  case L_SCREEN:
    switch(from) {
    case L_GLOBAL: return _mgc->W2S;
    case L_LOCAL: if(!(_mgc->has & HAS_S2O)) mg_findS2O();
      return _mgc->O2S;
    case L_NDC:
      WnGet(_mgc->win, WN_VIEWPORT, &vp);
      TmScale(Tmap, .5*(vp.xmax-vp.xmin+1), .5*(vp.ymax-vp.ymin+1), 1.0);
      CtmTranslate(Tmap, 1.0, 1.0, 0.0);
      return Tmap;
    }
    break;
  case L_CAMERA:
    if(from == L_GLOBAL) return _mgc->W2C;
    break;
  case L_NDC:
    switch(from) {
    case L_GLOBAL: TmConcat(_mgc->W2S, coordsto(L_SCREEN, L_NDC), Tmap);
      return Tmap;
    case L_SCREEN:
      WnGet(_mgc->win, WN_VIEWPORT, &vp);
      TmTranslate(Tmap, -1.0, -1.0, 0.0);
      CtmScale(Tmap, 2.0/(vp.xmax-vp.xmin+1),
	       2.0/(vp.ymax-vp.ymin+1), 1.0);
      return Tmap;
    }
    break;

  default:
    OOGLError(1, "InstDraw: internal error: unknown coord system 0x%x in coordsto(0x%x, 0x%x)", to, from, to);
    return TM3_IDENTITY;
  }


  TmConcat(coords2W(from), coordsto(L_GLOBAL, to), Tmap);
  return Tmap;
}
