SetOEMPhaseIncr(struct SiS_Private *SiS_Pr, unsigned short ModeNo,unsigned short ModeIdIndex)
{
  unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
  unsigned short index,i,j,temp,romptr=0;

  if(SiS_Pr->SiS_VBInfo & SetCRT2ToHiVision) return;

  if(SiS_Pr->SiS_TVMode & (TVSetNTSC1024 | TVSetNTSCJ | TVSetPALM | TVSetPALN)) return;

  if(SiS_Pr->SiS_UseROM) {
     if(!(ROMAddr[0x238] & 0x01)) return;
     if(!(ROMAddr[0x238] & 0x08)) return;
     romptr = SISGETROMW(0x245);
  }

  temp = GetOEMTVPtr(SiS_Pr);

  index = SiS_Pr->SiS_VBModeIDTable[ModeIdIndex].VB_TVPhaseIndex;

  if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {
     for(i=0x31, j=0; i<=0x34; i++, j++) {
        SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS300_Phase2[temp][index][j]);
     }
  } else {
     if(romptr) {
        romptr += (temp * 2);
	romptr = SISGETROMW(romptr);
	romptr += (index * 4);
        for(i=0x31, j=0; i<=0x34; i++, j++) {
	   SiS_SetReg(SiS_Pr->SiS_Part2Port,i,ROMAddr[romptr + j]);
	}
     } else {
        for(i=0x31, j=0; i<=0x34; i++, j++) {
           SiS_SetReg(SiS_Pr->SiS_Part2Port,i,SiS300_Phase1[temp][index][j]);
	}
     }
  }
}
