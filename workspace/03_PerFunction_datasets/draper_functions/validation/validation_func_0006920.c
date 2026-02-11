onMouseButtonUp(MouseEventArgs& e)
{

	Window::onMouseButtonUp(e);

	if (e.button == LeftButton)
	{

		if (d_segmentPushed && d_segmentHover)
		{
			WindowEventArgs args(this);
			onSegmentClicked(args);
		}
		else if (d_dragMoving)
		{
			MouseCursor::getSingleton().setImage(getMouseCursor());

			WindowEventArgs args(this);
			onSegmentDragStop(args);
		}


		releaseInput();
		++e.handled;
	}

}
