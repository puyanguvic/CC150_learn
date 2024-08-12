#include <vector>

using namespace std;

enum class Suit {
    HEARTS, DIAMONDS, CLUBS, SPADES
};

class Card {
protected:
    Suit suit;
    int value;  // 2-10 为数字牌，11-13 分别代表 J、Q、K，1 代表 A

public:
    Card(Suit s, int v) : suit(s), value(v) {}
    virtual int getValue() const { return value; }
    Suit getSuit() const { return suit; }
    virtual void display() const {
        // 显示卡牌信息
    }
};

class Deck {
protected:
    vector<Card*> cards;

public:
    Deck() {
        // 初始化52张牌
    }
    virtual void shuffle() {
        // 洗牌算法
    }
    virtual Card* drawCard() {
        // 抽一张牌
    }
    virtual void reset() {
        // 重置牌组
    }
};

class Hand {
protected:
    vector<Card*> cards;

public:
    virtual void addCard(Card* card) {
        cards.push_back(card);
    }
    virtual int getScore() const {
        // 计算手牌分数
    }
    virtual void clear() {
        cards.clear();
    }
};


class BlackjackCard : public Card {
public:
    BlackjackCard(Suit s, int v) : Card(s, v) {}
    int getValue() const override {
        if (value > 10) return 10;  // J、Q、K 都算10点
        return value;
    }
};

class BlackjackDeck : public Deck {
public:
    BlackjackDeck() {
        // 初始化52张 BlackjackCard
    }
    // 可以根据需要重写其他方法
};


class BlackjackHand : public Hand {
public:
    int getScore() const override {
        int score = 0;
        int aceCount = 0;
        for (const auto& card : cards) {
            BlackjackCard* bjCard = static_cast<BlackjackCard*>(card);
            if (bjCard->getValue() == 1) {
                aceCount++;
            } else {
                score += bjCard->getValue();
            }
        }
        // 处理 A 的特殊情况
        for (int i = 0; i < aceCount; i++) {
            if (score + 11 <= 21) {
                score += 11;
            } else {
                score += 1;
            }
        }
        return score;
    }
    bool isBusted() const {
        return getScore() > 21;
    }
};

class BlackjackGame {
private:
    BlackjackDeck deck;
    BlackjackHand playerHand;
    BlackjackHand dealerHand;

public:
    void start() {
        // 游戏开始逻辑
    }
    void playerHit() {
        // 玩家要牌
    }
    void dealerPlay() {
        // 庄家玩牌逻辑
    }
    void determineWinner() {
        // 判断赢家
    }
};
