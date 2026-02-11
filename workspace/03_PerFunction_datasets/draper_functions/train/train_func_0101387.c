glob(const Path& pathPattern, std::set<std::string>& files, int options)
{
	Path pattern(pathPattern);
	pattern.makeDirectory();
	Path base(pattern);
	Path absBase(base);
	absBase.makeAbsolute();
	while (base.depth() > 0 && base[base.depth() - 1] != "..")
	{
		base.popDirectory();
		absBase.popDirectory();
	}
	if (pathPattern.isDirectory()) options |= GLOB_DIRS_ONLY;
	collect(pattern, absBase, base, pathPattern[base.depth()], files, options);
}
