_ApSet(Appearance *ap, int attr1, va_list *alist)
{
  int mask;
  int attr;

#define NEXT(type) va_arg(*alist, type)

  if (ap == NULL) {


    ap = OOGLNewE(Appearance, "ApCreate Appearance");
    ApDefault(ap);
  }

  for ( attr = attr1; attr != AP_END; attr = NEXT(int)) {
    switch (attr) {
    case AP_DO:
      mask = NEXT(int);
      ap->flag |= mask;
      ap->valid |= mask;
      break;
    case AP_DONT:
      mask = NEXT(int);
      ap->flag &= ~mask;
      ap->valid |= mask;
      break;
    case AP_INVALID:
      ap->valid &= ~NEXT(int);
      break;
    case AP_OVERRIDE:
      ap->override |= NEXT(int);
      break;
    case AP_NOOVERRIDE:
      ap->override &= ~NEXT(int);
      break;
    case AP_MAT:
      ap->mat = NEXT(Material*);
      break;
    case AP_MtSet:
      ap->mat = _MtSet(ap->mat, va_arg(*alist, int), alist);
      break;
    case AP_LGT:
      ap->lighting = NEXT(LmLighting*);
      break;
    case AP_LmSet:
      if (!ap->lighting) ap->lighting = LmCreate(LM_END);
      ap->lighting = _LmSet(ap->lighting, va_arg(*alist, int), alist);
      break;
    case AP_NORMSCALE:
      ap->nscale = NEXT(double);
      ap->valid |= APF_NORMSCALE;
      break;
    case AP_LINEWIDTH:
      ap->linewidth = NEXT(int);
      ap->valid |= APF_LINEWIDTH;
      break;
    case AP_SHADING:

      ap->shading = NEXT(int);
      ap->valid |= APF_SHADING;
      break;
    case AP_DICE:
      ap->dice[0] = NEXT(int);
      ap->dice[1] = NEXT(int);
      ap->valid |= APF_DICE;
      break;
    default:
      OOGLError (0, "_ApSet: undefined option: %d\n", attr);
      return NULL;
      break;
    }
  }
  return ap;

#undef NEXT
}
