_FcValuePrintFile (FILE *f, const FcValue v)
{
    FcRange r;

    switch (v.type) {
    case FcTypeUnknown:
	fprintf (f, "<unknown>");
	break;
    case FcTypeVoid:
	fprintf (f, "<void>");
	break;
    case FcTypeInteger:
	fprintf (f, "%d(i)", v.u.i);
	break;
    case FcTypeDouble:
	fprintf (f, "%g(f)", v.u.d);
	break;
    case FcTypeString:
	fprintf (f, "\"%s\"", v.u.s);
	break;
    case FcTypeBool:
	fprintf (f, "%s", v.u.b ? "True" : "False");
	break;
    case FcTypeMatrix:
	fprintf (f, "[%g %g; %g %g]", v.u.m->xx, v.u.m->xy, v.u.m->yx, v.u.m->yy);
	break;
    case FcTypeCharSet:
	if (f == stdout)
	    FcCharSetPrint (v.u.c);
	break;
    case FcTypeLangSet:
	FcLangSetPrint (v.u.l);
	break;
    case FcTypeFTFace:
	fprintf (f, "face");
	break;
    case FcTypeRange:
	r = FcRangeCanonicalize (v.u.r);
	fprintf (f, "(%g, %g)", r.u.d.begin, r.u.d.end);
	break;
    }
}
