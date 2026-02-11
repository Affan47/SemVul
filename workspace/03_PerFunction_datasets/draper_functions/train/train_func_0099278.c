turnTowardDestination()
{
    if (x() <= destinationPoint.x())
        setLook(right);
    else setLook(left);
}
