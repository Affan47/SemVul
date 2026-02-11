output_desc_list(int msex, const char *intro, const char *list[], int n, byte attr)
{
	if (n != 0)
	{

		text_out(format("%^s %s ", wd_he[msex], intro));


		output_list(list, n, attr, "and ");


		text_out(".  ");
	}
}
