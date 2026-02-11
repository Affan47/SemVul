xml_markup_network(int tab, int action)
{
	static int markup_state = CLOSE_XML_MARKUP;

	if (action == markup_state)
		return;
	markup_state = action;

	if (action == OPEN_XML_MARKUP) {

		xprintf(tab, "<network per=\"second\">");
	}
	else {

		xprintf(tab, "</network>");
	}
}
