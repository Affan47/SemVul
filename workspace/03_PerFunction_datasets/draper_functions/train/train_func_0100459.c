nxt_psp_get_joystick(nxt_t *nxt,int port,int joy,struct nxt_psp_joystick *jbuf) {
  char buf[4];
  int j1,nj,i;

  if (joy==NXT_PSP_JOY_LEFT|NXT_PSP_JOY_RIGHT) {
    j1 = 0;
    nj = 2;
  }
  else if (joy==NXT_PSP_JOY_LEFT) {
    j1 = 0;
    nj = 1;
  }
  else if (joy==NXT_PSP_JOY_RIGHT) {
    j1 = 1;
    nj = 1;
  }

  if (nxt_i2c_read(nxt,port,nxt_psp_i2c_addr,NXT_PSP_REG_JOYSTICKS+j1*2,nj*2,buf)==nj*2) {
    if (jbuf!=NULL) {
      for (i=0;i<nj;i++) {
        jbuf[i].x = (buf[i*2]&0xFF)-128;
        jbuf[i].y = (buf[i*2+1]&0xFF)-128;
      }
    }

    return 0;
  }
  else {
    return -1;
  }
}
