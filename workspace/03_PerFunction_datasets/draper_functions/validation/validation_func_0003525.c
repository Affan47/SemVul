R_DrawBloodEffect (void)
{
	image_t *gl = NULL;

	gl = R_RegisterPic ("blood_ring");

	if (!gl)
	{
		return;
	}

	qglEnable (GL_BLEND);

	qglActiveTextureARB(GL_TEXTURE0);
	qglBindTexture(GL_TEXTURE_2D, gl->texnum);

	qglEnableClientState (GL_VERTEX_ARRAY);
	qglEnableClientState (GL_TEXTURE_COORD_ARRAY);

	qglTexCoordPointer (2, GL_FLOAT, sizeof(tex_array[0]), tex_array[0]);
	qglVertexPointer (2, GL_FLOAT, sizeof(vert_array[0]), vert_array[0]);
	qglColorPointer (4, GL_FLOAT, sizeof(col_array[0]), col_array[0]);

	VA_SetElem2(vert_array[0],0, 0);
	VA_SetElem2(vert_array[1],vid.width, 0);
	VA_SetElem2(vert_array[2],vid.width, vid.height);
	VA_SetElem2(vert_array[3],0, vid.height);

	VA_SetElem2(tex_array[0],gl->sl, gl->tl);
	VA_SetElem2(tex_array[1],gl->sh, gl->tl);
	VA_SetElem2(tex_array[2],gl->sh, gl->th);
	VA_SetElem2(tex_array[3],gl->sl, gl->th);

	qglMatrixMode( GL_PROJECTION );
    qglLoadIdentity ();
	qglOrtho(0, viddef.width, viddef.height, 0, -10, 100);
	qglMatrixMode( GL_MODELVIEW );
    qglLoadIdentity ();

	R_DrawVarrays(GL_QUADS, 0, 4);

	qglDisable (GL_BLEND);

	R_KillVArrays();
}
