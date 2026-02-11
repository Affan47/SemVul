dbtopow(t_float f)
{
    if (f <= 0)
        return(0);
    else
    {
        if (f > 870)
            f = 870;
        return (exp((LOGTEN * 0.1) * (f-100.)));
    }
}
