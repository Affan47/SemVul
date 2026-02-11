apply_adjust_command(struct yomi_entry_list *yl,
		     struct adjust_command *ac_list)
{
  struct adjust_command *cmd;
  for (cmd = ac_list->next; cmd; cmd = cmd->next) {
    struct word_entry *we = find_word_entry(yl, cmd->yomi,
					    cmd->wt, cmd->word);
    if (!we) {
      char *yomi = anthy_xstr_to_cstr(cmd->yomi, ANTHY_UTF8_ENCODING);
      printf("failed to find target of adjust command (%s, %s, %s)\n",
	     yomi, cmd->wt, cmd->word);
      free(yomi);
      continue;
    }
    if (cmd->type == ADJUST_FREQ_UP) {
      we->raw_freq *= 4;
    }
    if (cmd->type == ADJUST_FREQ_DOWN) {
      we->raw_freq /= 4;
      if (we->raw_freq == 0) {
	we->raw_freq = 1;
      }
    }
    if (cmd->type == ADJUST_FREQ_KILL) {
      we->raw_freq = 0;
    }
  }
}
