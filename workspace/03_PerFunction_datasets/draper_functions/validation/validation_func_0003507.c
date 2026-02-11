resizeGL(int w, int h)
{

    glViewport (0, 0, w, h);
    glAspect = (GLdouble) w / (GLdouble) h;


    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (viewAngle, glAspect, minZ, maxZ);
    glMatrixMode (GL_MODELVIEW);


    bgRectZ = 2.0 * cubeCentreZ;
    bgRectY = -bgRectZ * tan (3.14159 * viewAngle / 360.0);
    bgRectX = glAspect * bgRectY;

    if (backgroundType == PICTURE) {

	if (glAspect > bgAspect) {

	    bgRectY = bgRectX / bgAspect;
	}
	else {

	    bgRectX = bgRectY * bgAspect;
	}
    }


    game->setSceneLabels();
}
