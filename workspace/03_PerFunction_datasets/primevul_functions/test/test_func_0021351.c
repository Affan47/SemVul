ObjectIsSequence(
		 OBJECT          *object
		 )
{
    pAssert(object != NULL);
    return (object->attributes.hmacSeq == SET
	    || object->attributes.hashSeq == SET
	    || object->attributes.eventSeq == SET);
}
