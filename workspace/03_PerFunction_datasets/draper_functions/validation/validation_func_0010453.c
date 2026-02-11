PerformAction(Subject *, ULEvent& , ULConnection& inConnection,
        bool& outWaitingForEvent, EEventID& ){

  AReleaseRQPDU thePDU;
  thePDU.Write(*inConnection.GetProtocol());
  inConnection.GetProtocol()->flush();


  outWaitingForEvent = true;

  return eSta7WaitRelease;
}
