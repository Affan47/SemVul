decode16BitConstrainedString
(OOCTXT* pctxt, Asn116BitCharString* pString, Asn116BitCharSet* pCharSet)
{
   ASN1UINT i, idx, nbits = pCharSet->alignedBits;
   int stat;


   stat = decodeLength (pctxt, &pString->nchars);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);


   stat = decodeByteAlign (pctxt);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);


   pString->data = (ASN116BITCHAR*)
      ASN1MALLOC (pctxt, pString->nchars*sizeof(ASN116BITCHAR));

   if (pString->data) {
      for (i = 0; i < pString->nchars; i++) {
         stat = decodeBits (pctxt, &idx, nbits);
         if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);

         pString->data[i] = (pCharSet->charSet.data == 0) ?
            idx + pCharSet->firstChar : pCharSet->charSet.data[idx];
      }
   }
   else
      return LOG_ASN1ERR (pctxt, ASN_E_NOMEM);

   return ASN_OK;
}
