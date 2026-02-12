static bool hufBuildDecTable(const long long *hcode,
                             int im,
                             int iM,
                             HufDec *hdecod)

{


  for (; im <= iM; im++) {
    long long c = hufCode(hcode[im]);
    int l = hufLength(hcode[im]);

    if (c >> l) {


      return false;
    }

    if (l > HUF_DECBITS) {


      HufDec *pl = hdecod + (c >> (l - HUF_DECBITS));

      if (pl->len) {


        return false;
      }

      pl->lit++;

      if (pl->p) {
        int *p = pl->p;
        pl->p = new int[pl->lit];

        for (int i = 0; i < pl->lit - 1; ++i) pl->p[i] = p[i];

        delete[] p;
      } else {
        pl->p = new int[1];
      }

      pl->p[pl->lit - 1] = im;
    } else if (l) {


      HufDec *pl = hdecod + (c << (HUF_DECBITS - l));

      for (long long i = 1ULL << (HUF_DECBITS - l); i > 0; i--, pl++) {
        if (pl->len || pl->p) {


          return false;
        }

        pl->len = l;
        pl->lit = im;
      }
    }
  }

  return true;
}
