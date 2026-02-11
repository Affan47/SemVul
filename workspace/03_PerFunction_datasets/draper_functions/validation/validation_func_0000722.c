ooOnReceivedRequestChannelClose(OOH323CallData *call,
                                    H245RequestChannelClose *rclc)
{
   int ret=0, error=0;
   H245Message *ph245msg=NULL;
   H245ResponseMessage *response = NULL;
   OOCTXT *pctxt=NULL;
   H245RequestChannelCloseAck *rclcAck;
   ooLogicalChannel * lChannel=NULL;


   lChannel = ooFindLogicalChannelByLogicalChannelNo(call,
                                        rclc->forwardLogicalChannelNumber);
   if(!lChannel)
   {
      OOTRACEERR4("ERROR:Channel %d requested to be closed not found "
                  "(%s, %s)\n", rclc->forwardLogicalChannelNumber,
                  call->callType, call->callToken);
      return OO_FAILED;
   }
   else{
      if(strcmp(lChannel->dir, "transmit"))
      {
         OOTRACEERR4("ERROR:Channel %d requested to be closed, Not a forward "
                     "channel (%s, %s)\n", rclc->forwardLogicalChannelNumber,
                     call->callType, call->callToken);
         return OO_FAILED;
      }
   }
   ret = ooCreateH245Message(call, &ph245msg,
                             T_H245MultimediaSystemControlMessage_response);
   if(ret != OO_OK)
   {
      OOTRACEERR3("ERROR:Memory allocation for RequestChannelCloseAck message "
                  "failed (%s, %s)\n", call->callType, call->callToken);
      return OO_FAILED;
   }

   pctxt = call->msgctxt;
   ph245msg->msgType = OORequestChannelCloseAck;
   ph245msg->logicalChannelNo = rclc->forwardLogicalChannelNumber;
   response = ph245msg->h245Msg.u.response;
   response->t = T_H245ResponseMessage_requestChannelCloseAck;
   response->u.requestChannelCloseAck = (H245RequestChannelCloseAck*)ASN1MALLOC
                                   (pctxt, sizeof(H245RequestChannelCloseAck));
   if(!response->u.requestChannelCloseAck)
   {
      OOTRACEERR3("ERROR:Failed to allocate memory for RequestChannelCloseAck "
                  "message (%s, %s)\n", call->callType, call->callToken);
      return OO_FAILED;
   }
   rclcAck = response->u.requestChannelCloseAck;
   memset(rclcAck, 0, sizeof(H245RequestChannelCloseAck));
   rclcAck->forwardLogicalChannelNumber = rclc->forwardLogicalChannelNumber;

   OOTRACEDBGA3("Built RequestCloseChannelAck message (%s, %s)\n",
                 call->callType, call->callToken);
   ret = ooSendH245Msg(call, ph245msg);
   if(ret != OO_OK)
   {
      OOTRACEERR3("Error:Failed to enqueue RequestCloseChannelAck to outbound queue. (%s, %s)\n", call->callType,
                  call->callToken);
      error++;
   }

   ooFreeH245Message(call, ph245msg);


   if (lChannel->state == OO_LOGICALCHAN_ESTABLISHED) {
     ret = ooSendCloseLogicalChannel(call, lChannel);
     if (ret != OO_OK) {
      OOTRACEERR3("ERROR:Failed to build CloseLgicalChannel message(%s, %s)\n",
                   call->callType, call->callToken);
      return OO_FAILED;
     }
   }
   if (error) {
	return OO_FAILED;
   }
   return ret;
}
