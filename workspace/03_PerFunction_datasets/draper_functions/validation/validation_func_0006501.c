unserialize(uint8_t const * ptr, uint32_t nbytes, TxRef* parent, int32_t idx)
{
   parentTx_ = parent;
   index_ = idx;
   nBytes_ = (nbytes==0 ? BtcUtils::TxOutCalcLength(ptr) : nbytes);
   self_ = BinaryDataRef(ptr, nBytes_);

   scriptOffset_ = 8 + BtcUtils::readVarIntLength(getPtr()+8);
   BinaryDataRef scriptRef(self_.getPtr()+scriptOffset_, getScriptSize());
   scriptType_ = BtcUtils::getTxOutScriptType(scriptRef);
   recipientBinAddr20_ = BtcUtils::getTxOutRecipientAddr(scriptRef, scriptType_);
}
