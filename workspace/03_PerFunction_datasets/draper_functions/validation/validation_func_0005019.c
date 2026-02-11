append(char c) {
        if (space_left >= 1) {
            *bp++ = c;
            space_left--;
        }
        else if (!space_left) {
            insert_overflow_warning();
        }
    }
