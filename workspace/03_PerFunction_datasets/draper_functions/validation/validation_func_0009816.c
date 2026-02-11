generateMacroInterfaceTree(const string& pathname, Tree t)
{
	Tree 	label, elements, varname, sig;

	if (isUiFolder(t, label, elements)) {
		string pathname2 = pathname;

		string str = tree2str(right(label));
		if (str.length()>0) pathname2 += str + "/";
		generateMacroInterfaceElements(pathname2, elements);

	} else if (isUiWidget(t, label, varname, sig)) {

		generateWidgetMacro(pathname, label, varname, sig);

	} else {

		fprintf(stderr, "error in user interface macro generation 2\n");
		exit(1);

	}
}
