#include <iostream>
#include  <string>

using namespace std;


struct Card;
struct Deck;

enum CardValue { Ace=1, Two=2, Three=3, Four=4, Five=5, Six=6, Seven=7, Eight=8, Nine=9, Ten=10, Jack=11, Queen=12, King=13 };
enum Suit { CUPS=1, COINS=2, CLUBS=3, SPADES=4 };

const int frenchSuitNumber = 13;

int indexCounter = 0;

// -------------------------------------- CARD --------------------------------------------
struct Card {

    int id;
    Suit suit;
    CardValue value;
    bool turned;
    Card *next;
    Card *prev;

    Card();
    Card(Suit _suit, CardValue _value, bool _turned, int _id);
    string getStringValue();
    string getStringSuit();
};

Card::Card(Suit _suit, CardValue _value, bool _turned, int _id) {
    suit = _suit;
    value = _value;
    turned = _turned;
    next = nullptr;
    prev = nullptr;
    id = _id;
}

string Card::getStringValue() {
    string resp;
    if (turned) {
        return "--";
    } else {
        switch (value) {
            case Ace:
                resp = "Ace";
                break;
            case Two:
                resp = "2";
                break;
            case Three:
                resp = "3";
                break;
            case Four:
                resp = "4";
                break;
            case Five:
                resp = "5";
                break;
            case Six:
                resp = "6";
                break;
            case Seven:
                resp = "7";
                break;
            case Eight:
                resp = "8";
                break;
            case Nine:
                resp = "9";
                break;
            case Ten:
                resp = "10";
                break;
            case Jack:
                resp = "Jack";
                break;
            case Queen:
                resp = "Queen";
                break;
            case King:
                resp = "King";
                break;
        }
        return resp;
    }
}

string Card::getStringSuit() {
    string resp;
    switch (suit) {
        case CUPS:
            resp = "Cups";
            break;
        case COINS:
            resp = "Coins";
            break;
        case CLUBS:
            resp = "Clubs";
            break;
        case SPADES:
            resp = "Spades";
            break;
    }
    return resp;
}

// -------------------------------------- Deck --------------------------------------------

struct Deck {
    Card * head;
    Card * tail;
    int size;

    Deck();
    void addCard(Card *c);
    void addFrenchSuit(Suit _suit);
    CardValue getNumberOfValue(int _i);
    void handOutCardsTo(int quantity, Deck * to);
    void fillPerSuit(int number_of_suits, Suit _suit);
    void moveCardTo(Card *_card, Deck * to);
    void shuffle();
    void printCards();
};

Deck::Deck() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

void Deck::addCard(Card *c) {
    if (tail == nullptr) {
        head = tail = c;
    } else {
        tail->next = c;
        c->prev = tail;
        tail = c;
    }
    size++;
}

void Deck::addFrenchSuit(Suit _suit) {
    for (int i = 0; i < frenchSuitNumber; ++i) {
        addCard(new Card(_suit, getNumberOfValue(i+1), false, indexCounter++));
    }
}

CardValue Deck::getNumberOfValue(int _i) {
    CardValue resp;
    switch (_i) {
        case 1:
            resp = Ace;
            break;
        case 2:
            resp = Two;
            break;
        case 3:
            resp = Three;
            break;
        case 4:
            resp = Four;
            break;
        case 5:
            resp = Five;
            break;
        case 6:
            resp = Six;
            break;
        case 7:
            resp = Seven;
            break;
        case 8:
            resp = Eight;
            break;
        case 9:
            resp = Nine;
            break;
        case 10:
            resp = Ten;
            break;
        case 11:
            resp = Jack;
            break;
        case 12:
            resp = Queen;
            break;
        case 13:
            resp = King;
            break;
    }
    return resp;
}

void Deck::moveCardTo(Card * _card, Deck * to) {
    if (_card != nullptr && to != nullptr) {
        if (_card == head){

            if (to->head == nullptr) {
                to->head = _card;
                to->tail = tail;
                to->size = size;
                //
                size = 0;
                head = tail = nullptr;
            } else {
                _card->prev = to->tail;
                to->tail->next = _card;
                to->tail = tail;
                to->size += size;
                //
                size = 0;
                head = tail = nullptr;
            }

        } else if (_card == tail) {

            if (to->head == nullptr) {
                _card->prev->next = nullptr;
                tail = _card->prev;
                _card->prev = nullptr;
                size--;
                //
                to->size++;
                to->head = to->tail = _card;
            } else {
                int newSize = 0;
                Card * aux = _card;
                while (aux != nullptr){
                    aux = aux->next;
                    newSize++;
                }
                size -=newSize;
                to->size += newSize;
                tail->prev->next = nullptr;
                tail = tail->prev;

                //
                to->tail->next = _card;
                _card->prev = to->tail;
                _card->next = nullptr;
                to->tail = _card;

            }

        } else {

            if (to->head == nullptr) {
                int newSize = 0;
                Card * aux = _card;
                while (aux != nullptr){
                    aux = aux->next;
                    newSize++;
                }

                to->head = _card;
                to->tail = tail;
                size -= newSize;
                to->size += newSize;
                //
                tail = _card->prev;
                _card->prev->next = nullptr;
            } else {
                int newSize = 0;
                Card * aux = _card;
                while (aux != nullptr){
                    aux = aux->next;
                    newSize++;
                }

                Card * thisTail = _card->prev;
                to->tail->next = _card;
                _card->prev = to->tail;
                to->tail = tail;
                to->size += newSize;
                size -= newSize;
                thisTail->next = nullptr;
                tail = thisTail;
            }

        }
    }
}

void Deck::handOutCardsTo(int quantity, Deck *to) {

    Card * _card = tail;
    while (_card != nullptr && --quantity > 0) {
        _card = _card->prev;
    };
    tail->turned = true;
    moveCardTo(_card, to);
}

void Deck::fillPerSuit(int number_of_suits, Suit _suit) {
    for (int i = 0; i < number_of_suits; ++i) {
        addFrenchSuit(_suit);
    }
}

void Deck::shuffle() {

}

void Deck::printCards() {
    Card *temp = head;
    while (temp != nullptr) {
        cout << "Id: " << temp->id << " " << temp->getStringSuit() << " " << temp->getStringValue() << " " << endl;
        temp = temp->next;
    }
}

// ---------------------------------------------------------------------------------------

int start(Deck *deck, Deck piles[10]) {
    deck->fillPerSuit(8, SPADES);
    deck->shuffle();
    deck->handOutCardsTo(6, &piles[0]);
    deck->handOutCardsTo(6, &piles[1]);
    deck->handOutCardsTo(6, &piles[2]);
    deck->handOutCardsTo(6, &piles[3]);
    deck->handOutCardsTo(5, &piles[4]);
    deck->handOutCardsTo(5, &piles[5]);
    deck->handOutCardsTo(5, &piles[6]);
    deck->handOutCardsTo(5, &piles[7]);
    deck->handOutCardsTo(5, &piles[8]);
    deck->handOutCardsTo(5, &piles[9]);
}

string printPiles(Deck * pile) {
    string piles = "";
}

string menu() {
    string m = "";
    m += "";
    return m;
}

int main() {
    Deck deck;
    Deck piles[10];
    Deck completedPiles[8];
    start(&deck, piles);
    cout << menu() << endl;

    return 0;
}