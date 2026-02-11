parse_top_item(CS& cmd, CARD_LIST* Scope)
{
  cmd.get_line(I_PROMPT);
  CMD::cmdproc(cmd, Scope);
}
