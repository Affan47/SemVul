static void CursorUp(int n)
{
	if (curr->w_y < curr->w_top) {
		if ((curr->w_y -= n) < 0)
			curr->w_y = 0;
	} else if ((curr->w_y -= n) < curr->w_top)
		curr->w_y = curr->w_top;
	LGotoPos(&curr->w_layer, curr->w_x, curr->w_y);
}
