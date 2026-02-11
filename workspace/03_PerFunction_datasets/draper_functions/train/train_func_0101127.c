hugsAPI5() {
    static HugsAPI5 api;
    static Bool initialised = FALSE;
    if (!initialised) {
	api.getBool       = getBool;
      	api.getInt        = getInt;
	api.getWord       = getWord;
	api.getAddr       = getAddr;
	api.getFloat      = getFloat;
	api.getDouble     = getDouble;
	api.getChar       = getChar;
	api.getForeign    = getForeign;
        api.getInt8       = getInt8;
        api.getInt16      = getInt16;
        api.getInt32      = getInt32;
        api.getInt64      = getInt64;
        api.getWord8      = getWord8;
        api.getWord16     = getWord16;
        api.getWord32     = getWord32;
        api.getWord64     = getWord64;
        api.getPtr        = getPtr;
        api.getFunPtr     = getFunPtr;
        api.getForeignPtr = getForeignPtr;
	api.getStablePtr4 = getStablePtr4;

	api.putBool       = putBool;
	api.putInt        = putInt;
	api.putWord       = putWord;
	api.putAddr       = putAddr;
	api.putFloat      = putFloat;
	api.putDouble     = putDouble;
	api.putChar       = putChar;
	api.putForeign    = putForeign;
        api.putInt8       = putInt8;
        api.putInt16      = putInt16;
        api.putInt32      = putInt32;
        api.putInt64      = putInt64;
        api.putWord8      = putWord8;
        api.putWord16     = putWord16;
        api.putWord32     = putWord32;
        api.putWord64     = putWord64;
        api.putPtr        = putPtr;
        api.putFunPtr     = putFunPtr;
        api.putForeignPtr = putForeignPtr;
	api.putStablePtr4 = putStablePtr4;

	api.returnIO      = returnIO;
	api.runIO         = runIO;
        api.returnId      = returnId;
        api.runId         = runId;

	api.registerPrims = registerPrims;

        api.lookupName    = lookupName;
        api.ap            = apMany;
        api.getUnit       = getUnit;
        api.mkThunk       = mkThunk;
        api.freeThunk     = freeHaskellFunctionPtr;

	api.makeStablePtr4 = getStablePtr;
	api.derefStablePtr4= putStablePtr;
	api.freeStablePtr4 = freeStablePtr4;
    }
    return &api;
}
