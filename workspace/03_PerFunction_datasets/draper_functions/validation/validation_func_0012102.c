hit_lt(Hit *hit1, Hit *hit2)
{
    if (hit1->score == hit2->score) {
        return hit1->doc > hit2->doc;
    }
    else {
        return hit1->score < hit2->score;
    }
}
