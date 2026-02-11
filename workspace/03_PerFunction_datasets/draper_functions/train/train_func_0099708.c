writeHandler(std::ostream& ostr)
{
	ostr << "void " << _class << "::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response)\n";
	ostr << "{\n";
	writeResponse(ostr);
	if (_page.has("page.precondition"))
	{
		ostr << "\tif (!(" << _page.get("page.precondition") << ")) return;\n\n";
	}
	writeSession(ostr);
	writeForm(ostr);
	ostr << _page.preHandler().str();
	writeContent(ostr);
	ostr << "}\n";
}
