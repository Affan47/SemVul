viptr(v,i)
vari *v;
INT i;
{ switch(vmode(v))
  { case VDOUBLE: return(&v->dpr[i]);
    case VCHAR: return(&((char *)v->dpr)[i]);
    case VARGL: return(&((carg *)v->dpr)[i]);
    case VARC:  return(&((arstruct *)v->dpr)[i]);
    case VVARI: return(&((vari *)v->dpr)[i]);
    case VXYZ:  return(&((plxyz *)v->dpr)[i]);
  }
  ERROR(("Unknown mode %d in viptr",vmode(v)));
  return(NULL);
}
