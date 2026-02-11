PostScalingFl2(int arrayOut[], int arrayIn[]) {


    int iEr, iEg, iEb;
    int iShift;

    if (arrayIn[0] <= 0) {
        arrayOut[0] = 0;
        iEr = 0;
    }
    else if ((arrayIn[0] >> 7) > 1) {
        arrayOut[0] = (arrayIn[0] & 0x7F) + 0x80;
        iEr = (arrayIn[0] >> 7);
    }
    else {
        arrayOut[0] = arrayIn[0];
        iEr = 1;
    }
    if (arrayIn[1] <= 0) {
        arrayOut[1] = 0;
        iEg = 0;
    }
    else if ((arrayIn[1] >> 7) > 1) {
        arrayOut[1] = (arrayIn[1] & 0x7F) + 0x80;
        iEg = (arrayIn[1] >> 7);
    }
    else {
        arrayOut[1] = arrayIn[1];
        iEg = 1;
    }
    if (arrayIn[2] <= 0) {
        arrayOut[2] = 0;
        iEb = 0;
    }
    else if ((arrayIn[2] >> 7) > 1) {
        arrayOut[2] = (arrayIn[2] & 0x7F) + 0x80;
        iEb = (arrayIn[2] >> 7);
    }
    else {
        arrayOut[2] = arrayIn[2];
        iEb = 1;
    }


    arrayOut[3] = iEr> iEg? (iEr>iEb?iEr:iEb):(iEg>iEb?iEg:iEb);

    if( arrayOut[3] > iEr){
        iShift = ( arrayOut[3] - iEr);
        arrayOut[0] = (unsigned char)((((int) arrayOut[0]) * 2 + 1) >> (iShift + 1));
    }
    if( arrayOut[3] > iEg){
        iShift = ( arrayOut[3]- iEg);
        arrayOut[1] = (unsigned char)((((int) arrayOut[1]) * 2 + 1) >> (iShift + 1));
    }
    if( arrayOut[3] > iEb){
        iShift = ( arrayOut[3]- iEb);
        arrayOut[2] = (unsigned char)((((int) arrayOut[2]) * 2 + 1) >> (iShift + 1));
    }
}
