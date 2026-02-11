GetMessageSummary()
  {
    stringstream summary;
    if (_messageCount[obError] > 0)
      summary << _messageCount[obError] << " errors ";
    if (_messageCount[obWarning] > 0)
      summary << _messageCount[obWarning] << " warnings ";
    if (_messageCount[obInfo] > 0)
      summary << _messageCount[obInfo] << " info messages ";
    if (_messageCount[obAuditMsg] > 0)
      summary << _messageCount[obAuditMsg] << " audit log messages ";
    if (_messageCount[obDebug] > 0)
      summary << _messageCount[obDebug] << " debugging messages ";

    return summary.str();
  }
