void MessageWrapper::Wrap(const std::string& message, std::string& out)
{


	out.assign(prefix);
	if (!fixed)
		out.append(message).append(suffix);
}
