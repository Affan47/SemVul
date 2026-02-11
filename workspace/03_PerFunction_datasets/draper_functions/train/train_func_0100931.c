button_print(int row, int col)
{
	int j;

	button_start = col;

	for (j = 0; j < button_num; j++)
		c_put_str(TERM_SLATE, button_mse[j].label, row, col + button_mse[j].left);

	return button_length;
}
