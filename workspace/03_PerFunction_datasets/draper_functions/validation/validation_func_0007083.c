SiS_GetColorDepth(struct SiS_Private *SiS_Pr, unsigned short ModeNo,
		unsigned short ModeIdIndex)
{
   static const unsigned short ColorDepth[6] = { 1, 2, 4, 4, 6, 8 };
   unsigned short modeflag;
   short index;


   if(ModeNo == 0xfe) {
      modeflag = SiS_Pr->CModeFlag;
   } else if(ModeNo <= 0x13) {
      modeflag = SiS_Pr->SiS_SModeIDTable[ModeIdIndex].St_ModeFlag;
   } else {
      modeflag = SiS_Pr->SiS_EModeIDTable[ModeIdIndex].Ext_ModeFlag;
   }

   index = (modeflag & ModeTypeMask) - ModeEGA;
   if(index < 0) index = 0;
   return ColorDepth[index];
}
