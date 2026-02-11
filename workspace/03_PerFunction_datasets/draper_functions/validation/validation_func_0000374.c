New_msg_struct()
{

  struct msg_struct *msg;

  msg = (struct msg_struct *)malloc(sizeof(struct msg_struct));

  if(msg){

    msg->msg_type = MSG_NOTSET;
    msg->msg_uid  = NULL;
    msg->status   = NULL;
    msg->control  = NULL;
    msg->supp_cmd = NULL;
    msg->io_def   = NULL;
    msg->chk_def  = NULL;
    msg->log      = NULL;
  }

  return msg;
}
