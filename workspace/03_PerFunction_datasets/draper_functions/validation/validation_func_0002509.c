failed() {


	switch (command().command()[0]) {
	case NW:
	case NE:
	case SW:
	case SE:


		World::level().setDungeonSymbol(directionToPoint((unsigned char) command().command()[0]), UNKNOWN_TILE_DIAGONALLY_UNPASSABLE);
		break;

	case N:
	case E:
	case S:
	case W:


		World::level().setDungeonSymbol(directionToPoint((unsigned char) command().command()[0]), UNKNOWN_TILE_UNPASSABLE);
		break;

	default:

		analyzer()->actionFailed();
		break;
	}
}
