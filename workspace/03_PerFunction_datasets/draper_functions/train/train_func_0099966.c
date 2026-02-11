asn1PE_H245OpenLogicalChannelAck_reverseLogicalChannelParameters (OOCTXT* pctxt, H245OpenLogicalChannelAck_reverseLogicalChannelParameters* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;


   extbit = (ASN1BOOL)(pvalue->m.replacementForPresent);

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.portNumberPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.multiplexParametersPresent);


   stat = asn1PE_H245LogicalChannelNumber (pctxt, pvalue->reverseLogicalChannelNumber);
   if (stat != ASN_OK) return stat;


   if (pvalue->m.portNumberPresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->portNumber, 0U, 65535U);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.multiplexParametersPresent) {
      stat = asn1PE_H245OpenLogicalChannelAck_reverseLogicalChannelParameters_multiplexParameters (pctxt, &pvalue->multiplexParameters);
      if (stat != ASN_OK) return stat;
   }

   if (extbit) {


      stat = encodeSmallNonNegWholeNumber (pctxt, 0);
      if (stat != ASN_OK) return stat;


      encodeBit (pctxt, (ASN1BOOL)pvalue->m.replacementForPresent);


      if (pvalue->m.replacementForPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         stat = asn1PE_H245LogicalChannelNumber (&lctxt, pvalue->replacementFor);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         freeContext (&lctxt);
      }

   }

   return (stat);
}
