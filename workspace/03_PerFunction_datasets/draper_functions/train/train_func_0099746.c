height() const
{
    if (!isValid())
        return qQNaN();

    double result = d_ptr->topLeft.latitude() - d_ptr->bottomRight.latitude();
    if (result < 0.0)
        result = qQNaN();
    return result;
}
