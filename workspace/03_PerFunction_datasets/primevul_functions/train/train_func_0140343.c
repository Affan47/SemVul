static void key_transpose(struct key_s *key)
{
	int t, sf;

	t = curvoice->transpose / 3;
	sf = (t & ~1) + (t & 1) * 7 + key->sf;
	switch ((curvoice->transpose + 210) % 3) {
	case 1:
		sf = (sf + 4 + 12 * 4) % 12 - 4;
		break;
	case 2:
		sf = (sf + 7 + 12 * 4) % 12 - 7;
		break;
	default:
		sf = (sf + 5 + 12 * 4) % 12 - 5;
		break;
	}
	key->sf = sf;
}
