OFCondition WlmActivityManager::ReceiveAndHandleCommands( T_ASC_Association *assoc )


{
  OFCondition cond = EC_Normal;
  T_DIMSE_Message msg;
  T_ASC_PresentationContextID presID;


  dataSource->SetFailOnInvalidQuery( opt_failInvalidQuery );


  while( cond.good() )
  {

    cond = DIMSE_receiveCommand( assoc, DIMSE_BLOCKING, 0, &presID, &msg, NULL );


    if( cond.good() )
    {


      switch( msg.CommandField )
      {
        case DIMSE_C_ECHO_RQ:

          cond = HandleEchoSCP( assoc, &msg.msg.CEchoRQ, presID );
          break;
        case DIMSE_C_FIND_RQ:

          cond = HandleFindSCP( assoc, &msg.msg.CFindRQ, presID );
          break;
        case DIMSE_C_CANCEL_RQ:


          DCMWLM_WARN("Received late Cancel Request, ignoring");
          break;
        default:


          cond = DIMSE_BADCOMMANDTYPE;
          break;
      }
    }
  }


  return( cond );
}
