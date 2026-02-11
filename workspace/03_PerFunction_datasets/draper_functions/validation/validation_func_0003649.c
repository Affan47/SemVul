ReadPnmStream(FILE *file, ByteImage *im) {

  const int NUM_VALUES = 3 ;
  const int INT_BUFFER_SIZE = 256 ;

  int magicnumber, depth ;
  char intBuffer[INT_BUFFER_SIZE];
  int values[NUM_VALUES], valuesIndex = 0, intIndex = 0, inToken = 0 ;
  int res;


  res = fscanf(file, "P%d", &magicnumber);
  if (res != 1) {
    return 0;
  }
  if (magicnumber == 5) {
    depth = 1;
  } else if (magicnumber == 6) {
    depth = 3;
  } else {
    return 0;
  }


  while (valuesIndex < NUM_VALUES) {
    char nextChar ;
    res = fread(&nextChar,1,1,file);
    if (res == 0) return 0;

    if (isspace(nextChar)) {
      if (inToken) {
        inToken = 0;
        intBuffer[intIndex] = 0 ;
        values[valuesIndex++] = atoi(intBuffer);
        intIndex = 0;


        if (valuesIndex == 3 && values[2] > 255) return 0;
      }
    }
    else if (isdigit(nextChar)) {
      inToken = 1 ;
      intBuffer[intIndex++] = nextChar ;
      if (intIndex == INT_BUFFER_SIZE)
        return 0;
    }
    else if (nextChar == '#') {
      do {
        res = fread(&nextChar,1,1,file);
      } while (res == 1 && nextChar != '\n');
      if (res == 0) return 0;
    }
    else {

      return 0;
    }
  }


  im->Resize(values[1],values[0], depth);
  res = fread(im->Data(), 1, im->Size(), file);
  if (res != im->Size()) {
    return 0;
  }
  return 1;
}
