operator==(const FMSkew& first, const FMSkew& other)
{
	return IsEquivalent(first.rotateAxis, other.rotateAxis) && IsEquivalent(first.aroundAxis, other.aroundAxis) && IsEquivalent(first.angle, other.angle);
}
