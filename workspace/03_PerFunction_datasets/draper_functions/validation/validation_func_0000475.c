closeTestMethod(const svUnitTest::svutTestCase& , const svUnitTest::svutTestMethod& , const svUnitTest::svutStatusInfo& status)
{
	string statusLower = status.getStatusName();
	std::transform(statusLower.begin(), statusLower.end(), statusLower.begin(), ::tolower);
	*out << "\t\t\t<status>" << statusLower << "</status>" << endl;
	*out << "\t\t\t<time>" << setprecision(2) << status.getDuration() << "</time>" << endl;
	if (status.getStatus() != SVUT_STATUS_SUCCESS && status.getStatus() != SVUT_STATUS_SKIPED)
		this->printAssertInfo(status);
	*out << "\t\t</TestFunction>" << endl;
}
