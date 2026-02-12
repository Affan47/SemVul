void CLASS Canon_WBCTpresets(short WBCTversion)
{
  if (WBCTversion == 0)
    for (int i = 0; i < 15; i++)
    {
      imgdata.color.WBCT_Coeffs[i][2] = imgdata.color.WBCT_Coeffs[i][4] = 1.0f;
      fseek(ifp, 2, SEEK_CUR);
      imgdata.color.WBCT_Coeffs[i][1] = 1024.0f / fMAX(get2(), 1.f);
      imgdata.color.WBCT_Coeffs[i][3] = 1024.0f / fMAX(get2(), 1.f);
      imgdata.color.WBCT_Coeffs[i][0] = get2();
    }
  else if (WBCTversion == 1)
    for (int i = 0; i < 15; i++)
    {
      imgdata.color.WBCT_Coeffs[i][2] = imgdata.color.WBCT_Coeffs[i][4] = 1.0f;
      imgdata.color.WBCT_Coeffs[i][1] = 1024.0f / fMAX(get2(), 1.f);
      imgdata.color.WBCT_Coeffs[i][3] = 1024.0f / fMAX(get2(), 1.f);
      fseek(ifp, 2, SEEK_CUR);
      imgdata.color.WBCT_Coeffs[i][0] = get2();
    }
  else if ((WBCTversion == 2) && ((unique_id == 0x80000374) ||
                                  (unique_id == 0x80000384) ||
                                  (unique_id == 0x80000394) ||
                                  (unique_id == 0x03970000) ||
                                  (unique_id == 0x04100000)))
    for (int i = 0; i < 15; i++)
    {
      fseek(ifp, 2, SEEK_CUR);
      fseek(ifp, 2, SEEK_CUR);
      imgdata.color.WBCT_Coeffs[i][2] = imgdata.color.WBCT_Coeffs[i][4] = 1.0f;
      imgdata.color.WBCT_Coeffs[i][1] = 1024.0f / fMAX(1.f, get2());
      imgdata.color.WBCT_Coeffs[i][3] = 1024.0f / fMAX(1.f, get2());
      imgdata.color.WBCT_Coeffs[i][0] = get2();
    }
  else if ((WBCTversion == 2) && ((unique_id == 0x03950000) || (unique_id == 0x03930000)))
    for (int i = 0; i < 15; i++)
    {
      fseek(ifp, 2, SEEK_CUR);
      fseek(ifp, 2, SEEK_CUR);
      imgdata.color.WBCT_Coeffs[i][2] = imgdata.color.WBCT_Coeffs[i][4] = 1.0f;
      imgdata.color.WBCT_Coeffs[i][1] = (float)get2() / 512.0f;
      imgdata.color.WBCT_Coeffs[i][3] = (float)get2() / 512.0f;
      imgdata.color.WBCT_Coeffs[i][0] = get2();
    }
  return;
}
