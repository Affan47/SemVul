filterbank_new(int banks, spx_word32_t sampling, int len, int type)
{
   FilterBank *bank;
   spx_word32_t df;
   spx_word32_t max_mel, mel_interval;
   int i;
   int id1;
   int id2;
   df = DIV32(SHL32(sampling,15),MULT16_16(2,len));
   max_mel = toBARK(EXTRACT16(sampling/2));
   mel_interval = PDIV32(max_mel,banks-1);

   bank = (FilterBank*)speex_alloc(sizeof(FilterBank));
   bank->nb_banks = banks;
   bank->len = len;
   bank->bank_left = (int*)speex_alloc(len*sizeof(int));
   bank->bank_right = (int*)speex_alloc(len*sizeof(int));
   bank->filter_left = (spx_word16_t*)speex_alloc(len*sizeof(spx_word16_t));
   bank->filter_right = (spx_word16_t*)speex_alloc(len*sizeof(spx_word16_t));

#ifndef FIXED_POINT
   bank->scaling = (float*)speex_alloc(banks*sizeof(float));
#endif
   for (i=0;i<len;i++)
   {
      spx_word16_t curr_freq;
      spx_word32_t mel;
      spx_word16_t val;
      curr_freq = EXTRACT16(MULT16_32_P15(i,df));
      mel = toBARK(curr_freq);
      if (mel > max_mel)
         break;
#ifdef FIXED_POINT
      id1 = DIV32(mel,mel_interval);
#else
      id1 = (int)(floor(mel/mel_interval));
#endif
      if (id1>banks-2)
      {
         id1 = banks-2;
         val = Q15_ONE;
      } else {
         val = DIV32_16(mel - id1*mel_interval,EXTRACT16(PSHR32(mel_interval,15)));
      }
      id2 = id1+1;
      bank->bank_left[i] = id1;
      bank->filter_left[i] = SUB16(Q15_ONE,val);
      bank->bank_right[i] = id2;
      bank->filter_right[i] = val;
   }


#ifndef FIXED_POINT
   for (i=0;i<bank->nb_banks;i++)
      bank->scaling[i] = 0;
   for (i=0;i<bank->len;i++)
   {
      int id = bank->bank_left[i];
      bank->scaling[id] += bank->filter_left[i];
      id = bank->bank_right[i];
      bank->scaling[id] += bank->filter_right[i];
   }
   for (i=0;i<bank->nb_banks;i++)
      bank->scaling[i] = Q15_ONE/(bank->scaling[i]);
#endif
   return bank;
}
