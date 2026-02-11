layout()
{
    calcWidth();
    calcHeight();

    RenderWidget::layout();

    if (mediaElement()->controls() && widget()->layout()->count() == 1) {
        MediaControls* toolbox = new MediaControls(player(), widget());
	widget()->layout()->addWidget(toolbox);
	if ((!widget()->underMouse()) && mediaElement()->isVideo())
	    toolbox->hide();
	else
	    toolbox->show();
    }
}
