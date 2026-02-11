setPrime(uint32_t i, bool isPrime) {

	if (isPrime) {
		_primeTable[i/_blockSize] &= ~(1 << (i % _blockSize));
	} else {
		_primeTable[i/_blockSize] |= 1 << (i % _blockSize);
	}

}
