void DecimalQuantity::roundToMagnitude(int32_t magnitude, RoundingMode roundingMode, bool nickel, UErrorCode& status) {


    int position = safeSubtract(magnitude, scale);


    int8_t trailingDigit = getDigitPos(position);

    if (position <= 0 && !isApproximate && (!nickel || trailingDigit == 0 || trailingDigit == 5)) {

    } else if (precision == 0) {

    } else {


        int8_t leadingDigit = getDigitPos(safeSubtract(position, 1));


        roundingutils::Section section;
        if (!isApproximate) {
            if (nickel && trailingDigit != 2 && trailingDigit != 7) {

                if (trailingDigit < 2) {

                    section = roundingutils::SECTION_LOWER;
                } else if (trailingDigit < 5) {

                    section = roundingutils::SECTION_UPPER;
                } else if (trailingDigit < 7) {

                    section = roundingutils::SECTION_LOWER;
                } else {

                    section = roundingutils::SECTION_UPPER;
                }
            } else if (leadingDigit < 5) {

                section = roundingutils::SECTION_LOWER;
            } else if (leadingDigit > 5) {

                section = roundingutils::SECTION_UPPER;
            } else {

                section = roundingutils::SECTION_MIDPOINT;
                for (int p = safeSubtract(position, 2); p >= 0; p--) {
                    if (getDigitPos(p) != 0) {
                        section = roundingutils::SECTION_UPPER;
                        break;
                    }
                }
            }
        } else {
            int32_t p = safeSubtract(position, 2);
            int32_t minP = uprv_max(0, precision - 14);
            if (leadingDigit == 0 && (!nickel || trailingDigit == 0 || trailingDigit == 5)) {
                section = roundingutils::SECTION_LOWER_EDGE;
                for (; p >= minP; p--) {
                    if (getDigitPos(p) != 0) {
                        section = roundingutils::SECTION_LOWER;
                        break;
                    }
                }
            } else if (leadingDigit == 4 && (!nickel || trailingDigit == 2 || trailingDigit == 7)) {
                section = roundingutils::SECTION_MIDPOINT;
                for (; p >= minP; p--) {
                    if (getDigitPos(p) != 9) {
                        section = roundingutils::SECTION_LOWER;
                        break;
                    }
                }
            } else if (leadingDigit == 5 && (!nickel || trailingDigit == 2 || trailingDigit == 7)) {
                section = roundingutils::SECTION_MIDPOINT;
                for (; p >= minP; p--) {
                    if (getDigitPos(p) != 0) {
                        section = roundingutils::SECTION_UPPER;
                        break;
                    }
                }
            } else if (leadingDigit == 9 && (!nickel || trailingDigit == 4 || trailingDigit == 9)) {
                section = roundingutils::SECTION_UPPER_EDGE;
                for (; p >= minP; p--) {
                    if (getDigitPos(p) != 9) {
                        section = roundingutils::SECTION_UPPER;
                        break;
                    }
                }
            } else if (nickel && trailingDigit != 2 && trailingDigit != 7) {

                if (trailingDigit < 2) {

                    section = roundingutils::SECTION_LOWER;
                } else if (trailingDigit < 5) {

                    section = roundingutils::SECTION_UPPER;
                } else if (trailingDigit < 7) {

                    section = roundingutils::SECTION_LOWER;
                } else {

                    section = roundingutils::SECTION_UPPER;
                }
            } else if (leadingDigit < 5) {

                section = roundingutils::SECTION_LOWER;
            } else {

                section = roundingutils::SECTION_UPPER;
            }

            bool roundsAtMidpoint = roundingutils::roundsAtMidpoint(roundingMode);
            if (safeSubtract(position, 1) < precision - 14 ||
                (roundsAtMidpoint && section == roundingutils::SECTION_MIDPOINT) ||
                (!roundsAtMidpoint && section < 0 )) {


                convertToAccurateDouble();
                roundToMagnitude(magnitude, roundingMode, nickel, status);
                return;
            }


            isApproximate = false;
            origDouble = 0.0;
            origDelta = 0;

            if (position <= 0 && (!nickel || trailingDigit == 0 || trailingDigit == 5)) {

                return;
            }


            if (section == -1) { section = roundingutils::SECTION_LOWER; }
            if (section == -2) { section = roundingutils::SECTION_UPPER; }
        }


        bool isEven = nickel
                ? (trailingDigit < 2 || trailingDigit > 7
                        || (trailingDigit == 2 && section != roundingutils::SECTION_UPPER)
                        || (trailingDigit == 7 && section == roundingutils::SECTION_UPPER))
                : (trailingDigit % 2) == 0;

        bool roundDown = roundingutils::getRoundingDirection(isEven,
                isNegative(),
                section,
                roundingMode,
                status);
        if (U_FAILURE(status)) {
            return;
        }


        if (position >= precision) {
            setBcdToZero();
            scale = magnitude;
        } else {
            shiftRight(position);
        }

        if (nickel) {
            if (trailingDigit < 5 && roundDown) {
                setDigitPos(0, 0);
                compact();
                return;
            } else if (trailingDigit >= 5 && !roundDown) {
                setDigitPos(0, 9);
                trailingDigit = 9;

            } else {
                setDigitPos(0, 5);

                return;
            }
        }


        if (!roundDown) {
            if (trailingDigit == 9) {
                int bubblePos = 0;


                for (; getDigitPos(bubblePos) == 9; bubblePos++) {}
                shiftRight(bubblePos);
            }
            int8_t digit0 = getDigitPos(0);
            U_ASSERT(digit0 != 9);
            setDigitPos(0, static_cast<int8_t>(digit0 + 1));
            precision += 1;
        }

        compact();
    }
}
