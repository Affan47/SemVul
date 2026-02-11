appendContextKeyword(deparse_context *context, const char *str,
					 int indentBefore, int indentAfter, int indentPlus)
{
	if (PRETTY_INDENT(context))
	{
		context->indentLevel += indentBefore;

		appendStringInfoChar(context->buf, '\n');
		appendStringInfoSpaces(context->buf,
							   Max(context->indentLevel, 0) + indentPlus);
		appendStringInfoString(context->buf, str);

		context->indentLevel += indentAfter;
		if (context->indentLevel < 0)
			context->indentLevel = 0;
	}
	else
		appendStringInfoString(context->buf, str);
}
