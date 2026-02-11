message (int externalNumber, const char *source,
			     const char *msg, char severity, int loglvl)
{

  if (messageOut_ != messageBuffer_) {
    internalPrint() ;
  }

  internalNumber_ = externalNumber ;
  char detail = ((loglvl >= 0)?(static_cast<char>(loglvl)):'\000') ;
  currentMessage_= CoinOneMessage(externalNumber,detail,msg) ;
  source_ = source ;
  highestNumber_ = CoinMax(highestNumber_,externalNumber);


  messageBuffer_[0] = '\0' ;
  messageOut_ = messageBuffer_ ;


  if (loglvl >= 0) calcPrintStatus(loglvl,0) ;
  if (!printStatus_) {
    printStatus_ = 2 ;
    if (prefix_) {
      sprintf(messageOut_,"%s%4.4d%c ",source_.c_str(),
	      externalNumber,severity) ;
    }
    strcat(messageBuffer_,msg) ;
    messageOut_ = messageBuffer_+strlen(messageBuffer_) ;
  }
  return (*this) ;
}
