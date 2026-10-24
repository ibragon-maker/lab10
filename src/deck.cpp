#include "deck.h"
#include <random>

/*******************************************************************************
 * These four functions are yours to write. Until you do, the program builds and
 * runs, but every Deck is empty and the Blackjack demonstration tells you so.
 * Do not change the other functions in this file.
 ******************************************************************************/

Deck::Deck() : m_cards(nullptr), m_size(deck_size), m_next(0) {
    m_cards = new Card[m_size];
    
    int index = 0;
    for (int s = 0; s < 4; ++s) {
        Suit current_suit;
        if (s == 0) current_suit = Suit::clubs;
        else if (s == 1) current_suit = Suit::diamonds;
        else if (s == 2) current_suit = Suit::hearts;
        else current_suit = Suit::spades;

        for (int r = 1; r <= 13; ++r) {
            m_cards[index++] = Card(r, current_suit);
        }
    }
}

Deck::~Deck() {
    delete[] m_cards;
    m_cards = nullptr;
    m_size = 0;
    m_next = 0;
}

Deck::Deck(const Deck &other) : m_cards(nullptr), m_size(other.m_size), m_next(other.m_next) {
    if (other.m_size > 0 && other.m_cards != nullptr) {
        m_cards = new Card[m_size];
        for (int i = 0; i < m_size; ++i) {
            m_cards[i] = other.m_cards[i];
        }
    }
}

Deck &Deck::operator=(const Deck &other) {
    if (this == &other) {
        return *this;
    }

    Card *new_cards = nullptr;
    if (other.m_size > 0 && other.m_cards != nullptr) {
        new_cards = new Card[other.m_size];
        for (int i = 0; i < other.m_size; ++i) {
            new_cards[i] = other.m_cards[i];
        }
    }

    delete[] m_cards;

    m_cards = new_cards;
    m_size = other.m_size;
    m_next = other.m_next;

    return *this;
}

/*******************************************************************************
 * Provided: Do Not Change
 ******************************************************************************/

void Deck::shuffle(std::mt19937 &gen) {
    // Fisher-Yates: walk from the last card down, swapping each card with a
    // randomly chosen card at or before it.
    for (int i(m_size - 1); i > 0; --i) {
        std::uniform_int_distribution<int> pick(0, i);
        const int j = pick(gen);
        const Card held = m_cards[i];
        m_cards[i] = m_cards[j];
        m_cards[j] = held;
    }
    m_next = 0;
}

Card Deck::deal() {
    const Card top = m_cards[m_next];
    ++m_next;
    return top;
}

bool Deck::empty() const { return m_next >= m_size; }

int Deck::remaining() const { return m_size - m_next; }
