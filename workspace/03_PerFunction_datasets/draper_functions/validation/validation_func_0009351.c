diameter_verify(REQUEST *request,
			   const uint8_t *data, unsigned int data_len)
{
	uint32_t attr;
	uint32_t length;
	unsigned int offset;
	unsigned int data_left = data_len;

	while (data_left > 0) {
		if (data_len < 12) {
			RDEBUG2(" Diameter attribute is too small to contain a Diameter header");
			return 0;
		}

		rad_assert(data_left <= data_len);
		memcpy(&attr, data, sizeof(attr));
		data += 4;
		attr = ntohl(attr);
		if (attr > 255) {
			RDEBUG2(" Non-RADIUS attribute in tunneled authentication is not supported");
			return 0;
		}

		memcpy(&length, data , sizeof(length));
		data += 4;
		length = ntohl(length);


		offset = 8;
		if ((length & (1 << 31)) != 0) {
			int attribute;
			uint32_t vendor;
			DICT_ATTR *da;

			memcpy(&vendor, data, sizeof(vendor));
			vendor = ntohl(vendor);

			if (vendor > 65535) {
				RDEBUG2("Vendor codes larger than 65535 are not supported");
				return 0;
			}

			attribute = (vendor << 16) | attr;

			da = dict_attrbyvalue(attribute);


			if (!da) {
				RDEBUG2("Fatal! Vendor %u, Attribute %u was not found in our dictionary. ",
				       vendor, attr);
				return 0;
			}

			data += 4;
			offset += 4;
		}


		length &= 0x00ffffff;


		if (length < offset) {
			RDEBUG2("Tunneled attribute %d is too short (%d)to contain anything useful.", attr, length);
			return 0;
		}


		if ((attr != PW_EAP_MESSAGE) &&
		    (length > (MAX_STRING_LEN + 8))) {
			RDEBUG2("Tunneled attribute %d is too long (%d) to pack into a RADIUS attribute.", attr, length);
			return 0;
		}

		if (length > data_left) {
			RDEBUG2("Tunneled attribute %d is longer than room left in the packet (%d > %d).", attr, length, data_left);
			return 0;
		}


		if (data_left == length) break;


		length += 0x03;
		length &= ~0x03;


		if (data_left < length) {
			RDEBUG2("ERROR! Diameter attribute overflows packet!");
			return 0;
		}


		if (data_left == length) break;


		data_left -= length;
		data += length - offset;
	}


	return 1;
}
