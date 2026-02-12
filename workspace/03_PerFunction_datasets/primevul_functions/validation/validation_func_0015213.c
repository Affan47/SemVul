void license_generate_randoms(rdpLicense* license)
{
#ifdef LICENSE_NULL_CLIENT_RANDOM
	ZeroMemory(license->ClientRandom, CLIENT_RANDOM_LENGTH);
#else
	winpr_RAND(license->ClientRandom, CLIENT_RANDOM_LENGTH);
#endif

#ifdef LICENSE_NULL_PREMASTER_SECRET
	ZeroMemory(license->PremasterSecret, PREMASTER_SECRET_LENGTH);
#else
	winpr_RAND(license->PremasterSecret, PREMASTER_SECRET_LENGTH);
#endif
}
