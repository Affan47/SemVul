decodeBocu1TrailByte(int32_t count, int32_t b) {
    if(b<=0x20) {

        b=bocu1ByteToTrail[b];

#if BOCU1_MAX_TRAIL<0xff
    } else if(b>BOCU1_MAX_TRAIL) {
        return -99;
#endif
    } else {
        b-=BOCU1_TRAIL_BYTE_OFFSET;
    }


    if(count==1) {
        return b;
    } else if(count==2) {
        return b*BOCU1_TRAIL_COUNT;
    } else  {
        return b*(BOCU1_TRAIL_COUNT*BOCU1_TRAIL_COUNT);
    }
}
