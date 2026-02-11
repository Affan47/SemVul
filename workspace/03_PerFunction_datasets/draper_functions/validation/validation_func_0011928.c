createNewConnectionBeforeFork(dmtcp::string& progName)
{
  JTRACE("Informing coordinator of a to-be-created process/program")
    (progName) (UniquePid::ThisProcess());
  _coordinatorSocket = createNewConnectionToCoordinator();
  JASSERT(_coordinatorSocket.isValid());

  sendCoordinatorHandshake(progName);
  recvCoordinatorHandshake();
}
