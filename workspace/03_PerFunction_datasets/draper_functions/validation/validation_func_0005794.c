printCell(c)
Cell c; {
    if (isName(c))
	Printf("%s",textToStr(name(c).text));
    else
	Printf("$%d",c);
}
