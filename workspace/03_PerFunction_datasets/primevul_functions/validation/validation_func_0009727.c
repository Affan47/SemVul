dnp3_al_empty_obj(guint16 al_obj)
{


  switch (al_obj)
  {
    case AL_OBJ_BI_ALL:
    case AL_OBJ_BIC_ALL:
    case AL_OBJ_BOC_ALL:
    case AL_OBJ_2BI_ALL:
    case AL_OBJ_2BIC_ALL:
    case AL_OBJ_CTR_ALL:
    case AL_OBJ_CTRC_ALL:
    case AL_OBJ_AI_ALL:
    case AL_OBJ_AIC_ALL:
    case AL_OBJ_AIDB_ALL:
    case AL_OBJ_AOC_ALL:
    case AL_OBJ_CLASS0:
    case AL_OBJ_CLASS1:
    case AL_OBJ_CLASS2:
    case AL_OBJ_CLASS3:
      return TRUE;
      break;
    default:
      return FALSE;
      break;
  }
}
