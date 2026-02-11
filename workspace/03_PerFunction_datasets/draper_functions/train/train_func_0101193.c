setTifftype(int pixeltype,
                int imagetype,
                int *pi,
                int *sf,
                int *spp,
                int *bps)
{
    switch (pixeltype) {
      case IM_BINARY:
        *bps = 1;
        *sf = 2;
        break;
      case IM_INT1:
        *bps = 8;
        *sf = 1;
        break;
      case IM_UINT1:
        *bps = 8;
        *sf = 1;
        break;
      case IM_INT2:
        *bps = 16;
        *sf = 2;
        break;
      case IM_UINT2:
        *bps = 16;
        *sf = 1;
        break;
      case IM_INT4:
        *bps = 32;
        *sf = 2;
        break;
      case IM_UINT4:
        *bps = 32;
        *sf = 1;
        break;
      case IM_FLOAT:
        *bps = 32;
        *sf = 3;
        break;
      case IM_DOUBLE:
        *bps = 64;
        *sf = 3;
        break;
    }


    if (*spp == 1 ) {
        if (pixeltype == IM_BINARY)
            *pi = 0;
        else
            *pi = 1;
    }

    if ((imagetype == IM_RGB) || (imagetype == IM_HLS)) {
        *spp = 3;
        *pi = 2;
    }


    if ((*spp > 1) && (*pi != 2))
        *pi = 5;


    return 0;
}
