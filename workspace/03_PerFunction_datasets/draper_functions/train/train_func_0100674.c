_FcValuePrint (const FcValue v)
{
    switch (v.type) {
    case FcTypeVoid:
	printf ("<void>");
	break;
    case FcTypeInteger:
	printf ("%d(i)", v.u.i);
	break;
    case FcTypeDouble:
	printf ("%g(f)", v.u.d);
	break;
    case FcTypeString:
	printf ("\"%s\"", v.u.s);
	break;
    case FcTypeBool:
	printf ("%s", v.u.b ? "FcTrue" : "FcFalse");
	break;
    case FcTypeMatrix:
	printf ("(%f %f; %f %f)", v.u.m->xx, v.u.m->xy, v.u.m->yx, v.u.m->yy);
	break;
    case FcTypeCharSet:
	FcCharSetPrint (v.u.c);
	break;
    case FcTypeLangSet:
	FcLangSetPrint (v.u.l);
	break;
    case FcTypeFTFace:
	printf ("face");
	break;
    }
}
