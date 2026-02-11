setImagePointer(FG_Graphic ** pDocGraphic,GR_Image ** pDocImage)
{
	if(pDocImage != NULL)
	{
		DELETEP(m_pImage);
		DELETEP(m_pGraphic);
	}
	m_pDocImage = pDocImage;
	m_pDocGraphic = pDocGraphic;
	m_FillType = FG_FILL_IMAGE;
}
