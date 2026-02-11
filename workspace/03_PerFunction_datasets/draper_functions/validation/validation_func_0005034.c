procDefCats()
{
  while(type == XML_READER_TYPE_END_ELEMENT || !(name == L"transfer" || name == L"interchunk" || name == L"postchunk"))
  {
    step();
    if(name != L"#text" && name != L"transfer" &&  name != L"interchunk" &&
       name != L"postchunk" && name != L"section-def-cats" && name != L"#comment")
    {
      parseError(L"'<" + name + L">' tag unexpected");
    }
  }

  wstring catname = L"";

  while(type != XML_READER_TYPE_END_ELEMENT ||
	name != L"section-def-cats")
  {
    step();
    if(name == L"cat-item")
    {
      if(type != XML_READER_TYPE_END_ELEMENT)
      {
        if(attrib(L"tags") != L"")
        {
          insertCatItem(catname, attrib(L"lemma"), attrib(L"tags"));
        }
        else
        {
          insertCatItem(catname, attrib(L"name"), L"");
        }
      }
    }
    else if(name == L"def-cat")
    {
      if(type != XML_READER_TYPE_END_ELEMENT)
      {
        catname = attrib(L"n");
      }
      else
      {
        catname = L"";
      }
    }
    else if(name == L"#text")
    {

    }
    else if(name == L"#comment")
    {

    }
    else if(name == L"section-def-cats")
    {

    }
    else
    {
      parseError(L"Unexpected '<" + name + L">' tag");
    }
  }
}
