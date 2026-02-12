callbacks_update_ruler_scales (void) {
	double xStart, xEnd, yStart, yEnd;

	xStart = screenRenderInfo.lowerLeftX;
	yStart = screenRenderInfo.lowerLeftY;
	xEnd = screenRenderInfo.lowerLeftX + (screenRenderInfo.displayWidth / screenRenderInfo.scaleFactorX);
	yEnd = screenRenderInfo.lowerLeftY + (screenRenderInfo.displayHeight / screenRenderInfo.scaleFactorY);


	if (!((screen.unit == GERBV_MILS) && ((screenRenderInfo.scaleFactorX < 80)||(screenRenderInfo.scaleFactorY < 80)))) {
		xStart = callbacks_calculate_actual_distance (xStart);
		xEnd = callbacks_calculate_actual_distance (xEnd);
		yStart = callbacks_calculate_actual_distance (yStart);
		yEnd = callbacks_calculate_actual_distance (yEnd);
	}


	if (screen.win.hRuler)
		gtk_ruler_set_range (GTK_RULER (screen.win.hRuler), xStart, xEnd, 0, xEnd - xStart);

	if (screen.win.vRuler)
		gtk_ruler_set_range (GTK_RULER (screen.win.vRuler), yEnd, yStart, 0, yEnd - yStart);
}
