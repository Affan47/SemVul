append_numeric(String::int_large_t num, int base, bool uppercase)
{
    if (num < 0) {
	*this << '-';
	append_numeric(static_cast<String::uint_large_t>(-num), base, uppercase);
    } else
	append_numeric(static_cast<String::uint_large_t>(num), base, uppercase);
}
