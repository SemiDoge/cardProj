#ifndef PLAYING_CARD_H
#define PLAYING_CARD_H

enum faces {
    Ace = 1, Two, Three, 
    Four, Five, Six,
    Seven, Eight, Nine, 
    Ten, Jack, Queen,
    King
};

enum suits {
    Club = 1, Diamond,
    Heart, Spade 
};

struct playingCard {
    faces face;
    suits suit;
};

#endif