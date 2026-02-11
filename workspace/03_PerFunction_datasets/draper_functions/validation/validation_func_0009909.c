doDragMoving(const Point& local_mouse)
{

	float	deltaX = local_mouse.d_x - d_dragPoint.d_x;
	float	deltaY = local_mouse.d_y - d_dragPoint.d_y;


	d_dragPosition.d_x += deltaX;
	d_dragPosition.d_y += deltaY;


	d_dragPoint.d_x += deltaX;
	d_dragPoint.d_y += deltaY;

	WindowEventArgs args(this);
	onSegmentDragPositionChanged(args);
}
