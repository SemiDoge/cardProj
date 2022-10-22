#ifndef PLAYING_CARD_H
#define PLAYING_CARD_H

#include <string>

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
    std::string name;

    void GenerateName() {
        switch(face) {
        case Ace:
            name.append("Ace");
        break;
        case Two:
            name.append("Two");
        break;
        case Three:
            name.append("Three");
        break;
        case Four:
            name.append("Four");
        break;
        case Five:
            name.append("Five");
        break;
        case Six:
            name.append("Six");
        break;
        case Seven:
            name.append("Seven");
        break;
        case Eight:
            name.append("Eight");
        break;
        case Nine:
            name.append("Nine");
        break;
        case Ten:
            name.append("Ten");
        break;
        case Jack:
            name.append("Jack");
        break;
        case Queen:
            name.append("Queen");
        break;
        case King:
            name.append("King");
        break;
        }

        switch(suit) {
        case Club:
            name.append("ofClubs");
        break;
        case Diamond:
            name.append("ofDiamonds");
        break;
        case Heart:
            name.append("ofHearts");
        break;
        case Spade:
            name.append("ofSpades");
        }
    }
};

#endif