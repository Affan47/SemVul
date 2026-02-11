chan_focus (chan *ch)
{
	if (ch->cv->focused == ch)
		return;

	ch->cv->func_focus (ch);
}
