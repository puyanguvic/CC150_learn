#include <iostream>
#include <vector>
#include <string>

class Song {
public:
    Song(std::string title, std::string artist, int duration)
        : m_title(title), m_artist(artist), m_duration(duration) {}

    std::string getTitle() const { return m_title; }
    std::string getArtist() const { return m_artist; }
    int getDuration() const { return m_duration; }

private:
    std::string m_title;
    std::string m_artist;
    int m_duration; // 单位：秒
};

class Playlist {
public:
    void addSong(const Song& song) {
        m_songs.push_back(song);
    }

    void removeSong(const Song& song) {
        // 实现移除歌曲的逻辑
    }

    Song getNextSong() {
        // 实现获取下一首歌的逻辑
        return m_songs[0]; // 简化示例
    }

private:
    std::vector<Song> m_songs;
};

class CoinSlot {
public:
    bool insertCoin(int amount) {
        m_balance += amount;
        return true;
    }

    bool hasSufficientFunds(int price) {
        return m_balance >= price;
    }

    void deductFunds(int price) {
        m_balance -= price;
    }

private:
    int m_balance = 0;
};

class Display {
public:
    void showMessage(const std::string& message) {
        std::cout << message << std::endl;
    }

    void showSongList(const std::vector<Song>& songs) {
        // 实现显示歌曲列表的逻辑
    }
};

class AudioSystem {
public:
    void playSong(const Song& song) {
        std::cout << "Now playing: " << song.getTitle() << " by " << song.getArtist() << std::endl;
    }

    void stop() {
        std::cout << "Playback stopped." << std::endl;
    }
};

class Jukebox {
public:
    Jukebox() : m_currentSong(nullptr) {}

    void insertCoin(int amount) {
        if (m_coinSlot.insertCoin(amount)) {
            m_display.showMessage("Coin inserted. Balance: " + std::to_string(amount));
        }
    }

    void selectSong(const Song& song) {
        if (m_coinSlot.hasSufficientFunds(1)) { // 假设每首歌费用为1
            m_coinSlot.deductFunds(1);
            m_playlist.addSong(song);
            m_display.showMessage("Song added to playlist: " + song.getTitle());
            if (!m_currentSong) {
                playNextSong();
            }
        } else {
            m_display.showMessage("Insufficient funds. Please insert more coins.");
        }
    }

    void playNextSong() {
        if (m_currentSong) {
            m_audioSystem.stop();
        }
        m_currentSong = &m_playlist.getNextSong();
        m_audioSystem.playSong(*m_currentSong);
    }

private:
    Playlist m_playlist;
    CoinSlot m_coinSlot;
    Display m_display;
    AudioSystem m_audioSystem;
    const Song* m_currentSong;
};

int main() {
    Jukebox jukebox;

    jukebox.insertCoin(5);

    Song song1("Bohemian Rhapsody", "Queen", 354);
    Song song2("Imagine", "John Lennon", 183);

    jukebox.selectSong(song1);
    jukebox.selectSong(song2);

    return 0;
}