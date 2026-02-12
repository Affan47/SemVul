void HtmlString::endString()
{
  if( dir == textDirRightLeft && len > 1 )
  {

    for (int i = 0; i < len / 2; i++)
    {
      Unicode ch = text[i];
      text[i] = text[len - i - 1];
      text[len - i - 1] = ch;
    }
  }
}
