frCombMedian(VimosImage **ima_list, int num, int flag)
{
  VimosImage     *ima_med;
  float          *zvalue, value;
  int             i, j, n, xlen, ylen, rej;
  char            modName[] = "frCombMedian";

  if (ima_list == NULL) {
    cpl_msg_error(modName, "NULL input list");
    return(NULL);
  }


  xlen = ima_list[0]->xlen;
  ylen = ima_list[0]->ylen;
  for (i=1; i<num; i++) {
    if ((ima_list[i]->xlen != xlen) || (ima_list[i]->ylen != ylen)) {
      cpl_msg_error(modName, "Images must have the same dimensions");
      return NULL;
    }
  }

  if (num < MIN_FRAMES_MEDIAN) {
    cpl_msg_error(modName,
                "At least %d frames are needed for median computation",
                MIN_FRAMES_MEDIAN);
    return NULL;
  }
  else {
    ima_med = newImageAndAlloc(xlen, ylen);


    zvalue =(float*)pil_calloc(num, sizeof(float));

    if(flag) {
      for (j=0; j<ylen; j++) {
	for (i=0; i<xlen; i++) {
	  rej=0;
	  for (n=0; n<num; n++) {
	    value = ima_list[n]->data[i+j*xlen];
	    if (fabs(value+32000) > 0.001)
              zvalue[n-rej] = ima_list[n]->data[i+j*xlen];
	    else
              rej++;
	  }
	  if(rej!=num) ima_med->data[i+j*xlen] = medianPixelvalue(zvalue, num-rej);
	  else ima_med->data[i+j*xlen] = -32000;
	}
      }
    } else {
      for (j=0; j<ylen; j++) {
	for (i=0; i<xlen; i++) {
	  for (n=0; n<num; n++) {
	    zvalue[n] = ima_list[n]->data[i+j*xlen];
	  }
	  ima_med->data[i+j*xlen] = medianPixelvalue(zvalue, num);
	}
      }
    }
    pil_free(zvalue);
  }
  return ima_med;
}
