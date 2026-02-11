saveMetricMapRepresentationToFile(
	const std::string	&filNamePrefix ) const
{

	saveToTextFile( filNamePrefix + std::string("_probability.txt") );
}
