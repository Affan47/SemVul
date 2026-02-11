SetAntiFlicker(struct SiS_Private *SiS_Pr, unsigned short ModeNo, unsigned short ModeIdIndex)
{
  unsigned char  *ROMAddr = SiS_Pr->VirtualRomBase;
  unsigned short index,temp,temp1,romptr=0;

  if(SiS_Pr->SiS_TVMode & (TVSetYPbPr750p|TVSetYPbPr525p)) return;

  if(ModeNo<=0x13)
     index = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].VB_StTVFlickerIndex;
  else
     index = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].VB_ExtTVFlickerIndex;

  temp = GetTVPtrIndex(SiS_Pr);
  temp >>= 1;
  temp1 = temp;

  if(SiS_Pr->SiS_UseROM && (!(SiS_Pr->SiS_ROMNew))) {
     if(SiS_Pr->ChipType >= SIS_661) {
        temp1 = GetOEMTVPtr661(SiS_Pr);
        temp1 >>= 1;
        romptr = SISGETROMW(0x260);
        if(SiS_Pr->ChipType >= SIS_760) {
	   romptr = SISGETROMW(0x360);
	}
     } else if(SiS_Pr->ChipType >= SIS_330) {
        romptr = SISGETROMW(0x192);
     } else {
        romptr = SISGETROMW(0x112);
     }
  }

  if(romptr) {
     temp1 <<= 1;
     temp = ROMAddr[romptr + temp1 + index];
  } else {
     temp = SiS310_TVAntiFlick1[temp][index];
  }
  temp <<= 4;

  SiS_SetRegANDOR(SiS_Pr->SiS_Part2Port,0x0A,0x8f,temp);
}
