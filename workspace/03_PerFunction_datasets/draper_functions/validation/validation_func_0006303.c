showTooltip(GdkEventMotion* ev)
{
	int x_root,y_root, origY;
	int width,height;
	int x,y;
	int s_width,s_height;
	int currentX,currentY;
	channel->get_pointer(currentX,currentY);

	x_root=(int)ev->x_root;
	y_root=(int)ev->y_root;
	origY =(int)ev->y;
	this->get_size(width,height);
	s_width = this->get_screen()->get_width();
	s_height = this->get_screen()->get_height();

	x=x_root - width/2;
	if(currentY>=origY)
		y=y_root+24;
	else
		y=y_root+6;


	if(x+width > s_width)
		x=s_width-width;
	else if(x<0)
		x=0;
	if(y+height > s_height)
		y = y-height-24;
	else if(y<0)
		y=0;

	this->move(x,y);
	this->show_all();

}
