dtos(double value,
                   UnicodeString& string)
{

    char temp[DBL_DIG + 16];
    char *itrPtr = temp;
    char *expPtr;

    sprintf(temp, "%.*g", DBL_DIG, value);


    while (*itrPtr && (*itrPtr == '-' || isdigit(*itrPtr))) {
        itrPtr++;
    }
    if (*itrPtr != 0 && *itrPtr != 'e') {


        *itrPtr = '.';
        itrPtr++;
    }

    while (*itrPtr && *itrPtr != 'e') {
        itrPtr++;
    }
    if (*itrPtr == 'e') {
        itrPtr++;

        if (*itrPtr == '+' || *itrPtr == '-') {
            itrPtr++;
        }

        expPtr = itrPtr;
        while (*itrPtr == '0') {
            itrPtr++;
        }
        if (*itrPtr && expPtr != itrPtr) {

            while (*itrPtr) {
                *(expPtr++)  = *(itrPtr++);
            }

            *expPtr = 0;
        }
    }

    string = UnicodeString(temp, -1, US_INV);
    return string;
}
