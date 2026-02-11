WriteGeometryToMIFFile(MIDDATAFile *fp)
{
    double dXMin,dYMin,dXMax,dYMax;
    char   *pszTmpString;


    pszTmpString = TABEscapeString(m_pszString);
    if(pszTmpString == NULL)
        fp->WriteLine("Text \"\"\n" );
    else
        fp->WriteLine("Text \"%s\"\n", pszTmpString );
    if (pszTmpString != m_pszString)
        CPLFree(pszTmpString);


    GetMBR(dXMin, dYMin, dXMax, dYMax);
    fp->WriteLine("    %.15g %.15g %.15g %.15g\n",dXMin, dYMin,dXMax, dYMax);

    if (IsFontBGColorUsed())
      fp->WriteLine("    Font (\"%s\",%d,%d,%d,%d)\n", GetFontNameRef(),
                    GetFontStyleMIFValue(),0,GetFontFGColor(),
                    GetFontBGColor());
    else
      fp->WriteLine("    Font (\"%s\",%d,%d,%d)\n", GetFontNameRef(),
                    GetFontStyleMIFValue(),0,GetFontFGColor());

    switch (GetTextSpacing())
    {
      case   TABTS1_5:
        fp->WriteLine("    Spacing 1.5\n");
        break;
      case TABTSDouble:
        fp->WriteLine("    Spacing 2.0\n");
        break;
      case TABTSSingle:
      default:
        break;
    }

    switch (GetTextJustification())
    {
      case TABTJCenter:
        fp->WriteLine("    Justify Center\n");
        break;
      case TABTJRight:
        fp->WriteLine("    Justify Right\n");
        break;
      case TABTJLeft:
      default:
        break;
    }

    if (ABS(GetTextAngle()) >  0.000001)
        fp->WriteLine("    Angle %.15g\n",GetTextAngle());

    switch (GetTextLineType())
    {
      case TABTLSimple:
        if (m_bLineEndSet)
            fp->WriteLine("    Label Line Simple %.15g %.15g \n",
                          m_dfLineEndX, m_dfLineEndY );
        break;
      case TABTLArrow:
        if (m_bLineEndSet)
            fp->WriteLine("    Label Line Arrow %.15g %.15g \n",
                          m_dfLineEndX, m_dfLineEndY );
        break;
      case TABTLNoLine:
      default:
        break;
    }
    return 0;

}
