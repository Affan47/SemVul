oauth_decode_base64(unsigned char *dest, const char *src) {
  if(src && *src) {
    unsigned char *p= dest;
    int k, l= strlen(src)+1;
    unsigned char *buf= (unsigned char*) xcalloc(sizeof(unsigned char), l);


    for(k=0, l=0; src[k]; k++) {
      if(oauth_b64_is_base64(src[k])) {
        buf[l++]= src[k];
      }
    }

    for(k=0; k<l; k+=4) {
      char c1='A', c2='A', c3='A', c4='A';
      unsigned char b1=0, b2=0, b3=0, b4=0;
      c1= buf[k];

      if(k+1<l) c2= buf[k+1];
      if(k+2<l) c3= buf[k+2];
      if(k+3<l) c4= buf[k+3];

      b1= oauth_b64_decode(c1);
      b2= oauth_b64_decode(c2);
      b3= oauth_b64_decode(c3);
      b4= oauth_b64_decode(c4);

      *p++=((b1<<2)|(b2>>4) );

      if(c3 != '=') *p++=(((b2&0xf)<<4)|(b3>>2) );
      if(c4 != '=') *p++=(((b3&0x3)<<6)|b4 );
    }
    free(buf);
    dest[p-dest]='\0';
    return(p-dest);
  }
  return 0;
}
