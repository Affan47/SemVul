callbacks_screen2board(gdouble *X, gdouble *Y, gint x, gint y) {


	if ((screenRenderInfo.scaleFactorX > 0.001)||(screenRenderInfo.scaleFactorY > 0.001)) {
		*X = screenRenderInfo.lowerLeftX + (x / screenRenderInfo.scaleFactorX);
		*Y = screenRenderInfo.lowerLeftY + ((screenRenderInfo.displayHeight - y)
			/ screenRenderInfo.scaleFactorY);
	}
	else {
		*X = *Y = 0.0;
	}
}
