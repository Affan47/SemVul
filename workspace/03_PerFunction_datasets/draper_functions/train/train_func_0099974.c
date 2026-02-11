evaluate16Bit(DCM_OBJECT* obj)
{
  CONDITION cond;
  static U16 pixels[33];
  void* ctx = 0;
  U32 length = 0;
  int idx = 0;
  int errorFlag = 0;

  DCM_ELEMENT e =
	{ DCM_PXLPIXELDATA, DCM_OW, "", 0, sizeof(pixels), (void*)pixels };

  cond = DCM_GetElementValue(&obj, &e, &length, &ctx);
  if (cond != DCM_NORMAL) {
    COND_DumpConditions();
    exit(3);
  }
  if (length != 64) {
    fprintf(stderr, "Expected 64 bytes, retrieved %d bytes\n", length);
    exit(3);
  }

  for (idx = 0; idx < 26; idx++) {
    U16 expectedValue;

    expectedValue = idx + 'A';
    if (pixels[idx] != expectedValue) {
      fprintf(stderr, "Error in retrieving 16 bit pixels\n");
      fprintf(stderr, "At index: %d, expected %02x, received %02x \n",
		idx, expectedValue, pixels[idx]);
      errorFlag = 1;
    }
  }

  for (idx = 0; idx < 6; idx++) {
    U16 expectedValue;

    expectedValue = idx + 'a';
    if (pixels[idx+26] != expectedValue) {
      fprintf(stderr, "Error in retrieving 16 bit pixels\n");
      fprintf(stderr, "At index: %d, expected %02x, received %02x \n",
		idx+26, expectedValue, pixels[idx+26]);
      errorFlag = 1;
    }
  }

  if (errorFlag)
    exit(3);
}
