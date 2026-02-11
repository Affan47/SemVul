FindPreferredPkg(bool const &PreferNonVirtual) const {
	pkgCache::PkgIterator Pkg = FindPkg("native");
	if (Pkg.end() == false && (PreferNonVirtual == false || Pkg->VersionList != 0))
		return Pkg;

	std::vector<std::string> const archs = APT::Configuration::getArchitectures();
	for (std::vector<std::string>::const_iterator a = archs.begin();
	     a != archs.end(); ++a) {
		Pkg = FindPkg(*a);
		if (Pkg.end() == false && (PreferNonVirtual == false || Pkg->VersionList != 0))
			return Pkg;
	}

	Pkg = FindPkg("none");
	if (Pkg.end() == false && (PreferNonVirtual == false || Pkg->VersionList != 0))
		return Pkg;

	if (PreferNonVirtual == true)
		return FindPreferredPkg(false);
	return PkgIterator(*Owner, 0);
}
