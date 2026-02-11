limnObjectFaceReverse(limnObject *obj) {
  static const char me[]="limnObjectFaceReverse";
  limnFace *face;
  unsigned int faceIdx, sii;
  int *buff;

  if (!obj) {
    biffAddf(LIMN, "%s: got NULL pointer", me);
    return 1;
  }
  buff = NULL;
  for (faceIdx=0; faceIdx<obj->faceNum; faceIdx++) {
    face = obj->face + faceIdx;
    buff = (int *)calloc(face->sideNum, sizeof(int));
    if (!(buff)) {
      biffAddf(LIMN, "%s: couldn't allocate %d side buffer for face %d\n",
               me, face->sideNum, faceIdx);
      return 1;
    }
    memcpy(buff, face->vertIdx, face->sideNum*sizeof(int));
    for (sii=0; sii<face->sideNum; sii++) {
      face->vertIdx[sii] = buff[face->sideNum-1-sii];
    }
    memcpy(buff, face->edgeIdx, face->sideNum*sizeof(int));
    for (sii=0; sii<face->sideNum; sii++) {
      face->edgeIdx[sii] = buff[face->sideNum-1-sii];
    }
    free(buff);
  }
  return 0;
}
