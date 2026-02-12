int GetInterval(cmsFloat64Number In, const cmsUInt16Number LutTable[], const struct _cms_interp_struc* p)
{
    int i;
    int y0, y1;


    if (p -> Domain[0] < 1) return -1;


    if (LutTable[0] < LutTable[p ->Domain[0]]) {


        for (i=p->Domain[0]-1; i >=0; --i) {

            y0 = LutTable[i];
            y1 = LutTable[i+1];

            if (y0 <= y1) {
                if (In >= y0 && In <= y1) return i;
            }
            else
                if (y1 < y0) {
                    if (In >= y1 && In <= y0) return i;
                }
        }
    }
    else {

        for (i=0; i < (int) p -> Domain[0]; i++) {

            y0 = LutTable[i];
            y1 = LutTable[i+1];

            if (y0 <= y1) {
                if (In >= y0 && In <= y1) return i;
            }
            else
                if (y1 < y0) {
                    if (In >= y1 && In <= y0) return i;
                }
        }
    }

    return -1;
}
