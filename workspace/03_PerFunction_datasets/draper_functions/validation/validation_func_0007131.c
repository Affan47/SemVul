loadToken(const Pkcs11& p11, CK_OBJECT_HANDLE ulObjectHandle)
{
   const QStringList tokenInfoList(p11.tokenInfo());
   m_strCardLabel = tokenInfoList[0];
   m_strManufacturer = tokenInfoList[1];
   m_strSerialNo = tokenInfoList[2];

   try
   {
      Pkcs11AttrUlong bitLengthAttribute(CKA_MODULUS_BITS);
      p11.loadAttribute(bitLengthAttribute, ulObjectHandle);
      m_strBitLength.setNum(bitLengthAttribute.getValue());
   }
   catch (ErrorEx &e)
   {

   }

   Pkcs11AttrData idAttribute(CKA_ID);
   p11.loadAttribute(idAttribute, ulObjectHandle);
   m_strObjectId = BNOneLine(idAttribute.getBignum());

   try
   {
      Pkcs11AttrData objectLabelAttribute(CKA_LABEL);
      p11.loadAttribute(objectLabelAttribute, ulObjectHandle);
      m_strObjectLabel = objectLabelAttribute.getText();
   }
   catch (ErrorEx &e)
   {

   }

   m_strSlotId.setNum(p11.slotId());

   Pkcs11AttrData x509ValueAttribute(CKA_VALUE);
   p11.loadAttribute(x509ValueAttribute, ulObjectHandle);
   const unsigned char* pcValue;

   const unsigned long ulLen(x509ValueAttribute.getValue(&pcValue));

   if (m_pCertificateInfo)
      delete m_pCertificateInfo;

   m_pCertificateInfo = new CertificateInfo(QByteArray::fromRawData(reinterpret_cast<const char*>(pcValue), ulLen));
}
