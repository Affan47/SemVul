rds_language_lut(const uint8_t lc)
{
	const uint8_t max_lc = 127;
	const char *language;

	static const char *language_lut[128] = {
		"Unknown", "Albanian", "Breton", "Catalan",
		"Croatian", "Welsh", "Czech", "Danish",
		"German", "English", "Spanish", "Esperanto",
		"Estonian", "Basque", "Faroese", "French",
		"Frisian", "Irish", "Gaelic", "Galician",
		"Icelandic", "Italian", "Lappish", "Latin",
		"Latvian", "Luxembourgian", "Lithuanian", "Hungarian",
		"Maltese", "Dutch", "Norwegian", "Occitan",
		"Polish", "Portuguese", "Romanian", "Ramansh",
		"Serbian", "Slovak", "Slovene", "Finnish",
		"Swedish", "Turkish", "Flemish", "Walloon",
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, "Zulu", "Vietnamese", "Uzbek",
		"Urdu", "Ukrainian", "Thai", "Telugu",
		"Tatar", "Tamil", "Tadzhik", "Swahili",
		"Sranan Tongo", "Somali", "Sinhalese", "Shona",
		"Serbo-Croat", "Ruthenian", "Russian", "Quechua",
		"Pushtu", "Punjabi", "Persian", "Papamiento",
		"Oriya", "Nepali", "Ndebele", "Marathi",
		"Moldavian", "Malaysian", "Malagasay", "Macedonian",
		"Laotian", "Korean", "Khmer", "Kazahkh",
		"Kannada", "Japanese", "Indonesian", "Hindi",
		"Hebrew", "Hausa", "Gurani", "Gujurati",
		"Greek", "Georgian", "Fulani", "Dani",
		"Churash", "Chinese", "Burmese", "Bulgarian",
		"Bengali", "Belorussian", "Bambora", "Azerbaijani",
		"Assamese", "Armenian", "Arabic", "Amharic"
	};


	language = (lc > max_lc) ? "Unknown" : language_lut[lc];
	if (!language)
		return "Unknown";
	return language;
}
