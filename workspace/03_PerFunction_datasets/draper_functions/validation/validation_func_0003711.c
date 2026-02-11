CompositeOperatorToPSDBlendMode(CompositeOperator inOp)
{
  char*  outMode = (char *) "norm";

  switch ( inOp )
  {
    case OverCompositeOp:    outMode = (char *) "norm";  break;
    case MultiplyCompositeOp:  outMode = (char *) "mul ";  break;
    case DissolveCompositeOp:  outMode = (char *) "diss";  break;
    case DifferenceCompositeOp:  outMode = (char *) "diff";  break;
    case DarkenCompositeOp:    outMode = (char *) "dark";  break;
    case LightenCompositeOp:  outMode = (char *) "lite";  break;
    case HueCompositeOp:    outMode = (char *) "hue ";  break;
    case SaturateCompositeOp:  outMode = (char *) "sat ";  break;
    case ColorizeCompositeOp:  outMode = (char *) "colr";  break;
    case LuminizeCompositeOp:  outMode = (char *) "lum ";  break;
    case ScreenCompositeOp:    outMode = (char *) "scrn";  break;
    case OverlayCompositeOp:  outMode = (char *) "over";  break;

    default:
      outMode = (char *) "norm";


  }

  return outMode;
}
