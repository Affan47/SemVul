smtp_setup_batch_msg(void)
{
int done = 0;
void *reset_point = store_get(0);


bsmtp_transaction_linecount = receive_linecount;

if ((receive_feof)()) return 0;

cancel_cutthrough_connection(TRUE, US"smtp_setup_batch_msg");
smtp_reset(reset_point);


while (done <= 0)
  {
  uschar *errmess;
  uschar *recipient = NULL;
  int start, end, sender_domain, recipient_domain;

  switch(smtp_read_command(FALSE, GETC_BUFFER_UNLIMITED))
    {


    case HELO_CMD:
    case EHLO_CMD:

      check_helo(smtp_cmd_data);


    case RSET_CMD:
      cancel_cutthrough_connection(TRUE, US"RSET received");
      smtp_reset(reset_point);
      bsmtp_transaction_linecount = receive_linecount;
      break;


    case MAIL_CMD:
      smtp_mailcmd_count++;
      if (sender_address != NULL)

	moan_smtp_batch(smtp_cmd_buffer, "503 Sender already given");

      if (smtp_cmd_data[0] == 0)

	moan_smtp_batch(smtp_cmd_buffer, "501 MAIL FROM must have an address operand");


      cancel_cutthrough_connection(TRUE, US"MAIL received");
      smtp_reset(reset_point);


      raw_sender = ((rewrite_existflags & rewrite_smtp) != 0)?
	rewrite_one(smtp_cmd_data, rewrite_smtp|rewrite_smtp_sender, NULL, FALSE,
	  US"", global_rewrite_rules) : smtp_cmd_data;


      raw_sender =
	parse_extract_address(raw_sender, &errmess, &start, &end, &sender_domain,
	  TRUE);

      if (!raw_sender)

	moan_smtp_batch(smtp_cmd_buffer, "501 %s", errmess);

      sender_address = string_copy(raw_sender);


      if (  !sender_domain
         && sender_address[0] != 0 && sender_address[0] != '@')
	if (f.allow_unqualified_sender)
	  {
	  sender_address = rewrite_address_qualify(sender_address, FALSE);
	  DEBUG(D_receive) debug_printf("unqualified address %s accepted "
	    "and rewritten\n", raw_sender);
	  }

	else
	  moan_smtp_batch(smtp_cmd_buffer, "501 sender address must contain "
	    "a domain");
      break;


    case RCPT_CMD:
      if (!sender_address)

	moan_smtp_batch(smtp_cmd_buffer, "503 No sender yet given");

      if (smtp_cmd_data[0] == 0)

	moan_smtp_batch(smtp_cmd_buffer,
	  "501 RCPT TO must have an address operand");


      if (recipients_max > 0 && recipients_count + 1 > recipients_max)

	moan_smtp_batch(smtp_cmd_buffer, "%s too many recipients",
	  recipients_max_reject? "552": "452");


      recipient = rewrite_existflags & rewrite_smtp
	? rewrite_one(smtp_cmd_data, rewrite_smtp, NULL, FALSE, US"",
		      global_rewrite_rules)
	: smtp_cmd_data;

      recipient = parse_extract_address(recipient, &errmess, &start, &end,
	&recipient_domain, FALSE);

      if (!recipient)

	moan_smtp_batch(smtp_cmd_buffer, "501 %s", errmess);


      if (!recipient_domain)
	if (f.allow_unqualified_recipient)
	  {
	  DEBUG(D_receive) debug_printf("unqualified address %s accepted\n",
	    recipient);
	  recipient = rewrite_address_qualify(recipient, TRUE);
	  }

	else
	  moan_smtp_batch(smtp_cmd_buffer,
	    "501 recipient address must contain a domain");

      receive_add_recipient(recipient, -1);
      break;


    case DATA_CMD:
      if (!sender_address || recipients_count <= 0)

	if (!sender_address)
	  moan_smtp_batch(smtp_cmd_buffer,
	    "503 MAIL FROM:<sender> command must precede DATA");
	else
	  moan_smtp_batch(smtp_cmd_buffer,
	    "503 RCPT TO:<recipient> must precede DATA");
      else
	{
	done = 3;
	message_ended = END_NOTENDED;
	}
      break;


    case VRFY_CMD:
    case EXPN_CMD:
    case HELP_CMD:
    case NOOP_CMD:
    case ETRN_CMD:
      bsmtp_transaction_linecount = receive_linecount;
      break;


    case EOF_CMD:
    case QUIT_CMD:
      done = 2;
      break;


    case BADARG_CMD:

      moan_smtp_batch(smtp_cmd_buffer, "501 Unexpected argument data");
      break;


    case BADCHAR_CMD:

      moan_smtp_batch(smtp_cmd_buffer, "501 Unexpected NULL in SMTP command");
      break;


    default:

      moan_smtp_batch(smtp_cmd_buffer, "500 Command unrecognized");
      break;
    }
  }

return done - 2;
}
