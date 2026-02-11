cl2(I v)
{
    if(!v)R -1;
    I e = 0;
    if(v & (v - 1ULL))e=1;
    #if UINTPTR_MAX >= 0xffffffffffffffff
      if(v & 0xFFFFFFFF00000000ULL){e+=32;v>>=32;}
    #endif
    if(v & 0x00000000FFFF0000ULL){e+=16;v>>=16;}


    if(v & 0x000000000000FF00ULL){e+=8; v>>=8; }
    if(v & 0x00000000000000F0ULL){e+=4; v>>=4; }
    if(v & 0x000000000000000CULL){e+=2; v>>=2; }
    if(v & 0x0000000000000002ULL){e+=1; v>>=1; }
    R e;
}
