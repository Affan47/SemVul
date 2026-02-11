sky2_reg_access_ok(struct sky2_hw *hw, unsigned int b)
{


	switch (b) {

	case 5:
	case 9:
	case 14 ... 15:
	case 17: case 19:
	case 22 ... 23:
	case 25:
	case 27:
	case 31:
	case 40 ... 47:
	case 52: case 54:
	case 112 ... 116:
		return hw->ports > 1;

	case 0:
	case 2:
	case 4:
	case 7:
	case 8:
	case 12 ... 13:
	case 16: case 18:
	case 20 ... 21:
	case 24:
	case 26:
	case 28 ... 29:
	case 30:
	case 32 ... 39:
	case 48: case 50:
	case 56 ... 60:
	case 80 ... 84:
		return 1;

	default:
		return 0;
	}
}
