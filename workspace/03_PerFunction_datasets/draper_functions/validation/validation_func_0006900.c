genTextureTGA (char *fname, int quality, int alphatype, int mipmap2, bool alpha)
{
  char buf [STDSIZE];
  CTexture *mytex;
  if ((mytex = getTextureTGA (fname)) != NULL)
  {
    return mytex;
  }
  texnum ++;
  glBindTexture (GL_TEXTURE_2D, texnum);
  tex [texnum] = new CTexture ();
  if (!tex [texnum]->loadFromTGA (fname, quality, alphatype, mipmap2))
  {
    sprintf (buf, "Texture %s not found", fname);
    display (buf, LOG_ERROR);


    tex [texnum]->width = 8; tex [texnum]->height = 8;
    int buflen = tex [texnum]->width * tex [texnum]->height * 4;
    tex [texnum]->data = (unsigned char *) malloc (buflen);
    if (tex [texnum] == NULL) error_outofmemory ();
    memset (tex [texnum]->data, 0, buflen);
  }
  tex [texnum]->alpha = alpha;
  tex [texnum]->textureID = texnum;
  if (!antialiasing) disableLinearTexture (texnum);
  else enableLinearTexture (texnum);
  if (!mipmap2)
    glTexImage2D (GL_TEXTURE_2D, 0, 4, tex [texnum]->width, tex [texnum]->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex [texnum]->data);
  else
    gluBuild2DMipmaps (GL_TEXTURE_2D, 4, tex [texnum]->width, tex [texnum]->height, GL_RGBA, GL_UNSIGNED_BYTE, tex [texnum]->data);
  return tex [texnum];
}
