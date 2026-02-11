executeCommand()
{
	std::string temp;

	temp = "exec " + exe + " & ";


	system((char*)temp.c_str());
}
