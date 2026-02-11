draw_spectrum_line(int y, QPainter& paint,
			       const double *const data, const int buf_size)
{
	int from_x = 2;
	int from_y = y - 1;

	for (int i = 0; i < buf_size; i++) {
		int to_y = y - data[i];
		int to_x = i + 2;

		paint.drawLine(from_x, from_y, to_x , to_y);
		from_x = to_x;
		from_y = to_y;
	}
}
