smtp_respond(uschar* code, int codelen, BOOL final, uschar *msg)
{
int esclen = 0;
uschar *esc = US"";

if (!final && f.no_multiline_responses) return;

if (codelen > 4)
  {
  esc = code + 4;
  esclen = codelen - 4;
  }


if (fl.rcpt_in_progress)
  {
  if (rcpt_smtp_response == NULL)
    rcpt_smtp_response = string_copy(msg);
  else if (fl.rcpt_smtp_response_same &&
           Ustrcmp(rcpt_smtp_response, msg) != 0)
    fl.rcpt_smtp_response_same = FALSE;
  fl.rcpt_in_progress = FALSE;
  }


for (;;)
  {
  uschar *nl = Ustrchr(msg, '\n');
  if (nl == NULL)
    {
    smtp_printf("%.3s%c%.*s%s\r\n", !final, code, final ? ' ':'-', esclen, esc, msg);
    return;
    }
  else if (nl[1] == 0 || f.no_multiline_responses)
    {
    smtp_printf("%.3s%c%.*s%.*s\r\n", !final, code, final ? ' ':'-', esclen, esc,
      (int)(nl - msg), msg);
    return;
    }
  else
    {
    smtp_printf("%.3s-%.*s%.*s\r\n", TRUE, code, esclen, esc, (int)(nl - msg), msg);
    msg = nl + 1;
    while (isspace(*msg)) msg++;
    }
  }
}
