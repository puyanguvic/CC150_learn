#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

enum class EdgeType { FLAT, INNER, OUTER };

class Edge {
public:
    Edge(int id, EdgeType type) : m_id(id), m_type(type) {}

    bool fitsWith(const Edge& other) const {
        // 在实际实现中，这里应该有更复杂的匹配逻辑
        return m_id == other.m_id && m_type != other.m_type;
    }

private:
    int m_id;
    EdgeType m_type;
};

class Piece {
public:
    Piece(int id) : m_id(id), m_edges(4, nullptr) {}

    void setEdge(int index, Edge* edge) {
        m_edges[index] = edge;
    }

    Edge* getEdge(int index) const {
        return m_edges[index];
    }

    int getId() const { return m_id; }

private:
    int m_id;
    std::vector<Edge*> m_edges;  // 0: top, 1: right, 2: bottom, 3: left
};

class Puzzle {
public:
    Puzzle(int n) : m_size(n), m_board(n, std::vector<Piece*>(n, nullptr)) {}

    void addPiece(Piece* piece) {
        m_pieces.push_back(piece);
    }

    bool solve() {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(m_pieces.begin(), m_pieces.end(), g);

        return solveRecursive(0, 0);
    }

    void display() const {
        for (const auto& row : m_board) {
            for (const auto& piece : row) {
                if (piece) {
                    std::cout << piece->getId() << "\t";
                } else {
                    std::cout << "X\t";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    bool solveRecursive(int row, int col) {
        if (row == m_size) {
            return true;  // 拼图完成
        }

        if (col == m_size) {
            return solveRecursive(row + 1, 0);  // 移动到下一行
        }

        for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it) {
            Piece* piece = *it;
            if (fits(row, col, piece)) {
                m_board[row][col] = piece;
                m_pieces.erase(it);

                if (solveRecursive(row, col + 1)) {
                    return true;
                }

                // 回溯
                m_board[row][col] = nullptr;
                m_pieces.insert(it, piece);
            }
        }

        return false;
    }

    bool fits(int row, int col, Piece* piece) const {
        // 检查上边
        if (row > 0) {
            if (!piece->getEdge(0)->fitsWith(*m_board[row-1][col]->getEdge(2))) {
                return false;
            }
        }

        // 检查左边
        if (col > 0) {
            if (!piece->getEdge(3)->fitsWith(*m_board[row][col-1]->getEdge(1))) {
                return false;
            }
        }

        return true;
    }

    int m_size;
    std::vector<std::vector<Piece*>> m_board;
    std::vector<Piece*> m_pieces;
};

int main() {
    const int N = 3;  // 3x3 拼图
    Puzzle puzzle(N);

    // 创建拼图块和边
    for (int i = 0; i < N * N; ++i) {
        Piece* piece = new Piece(i);
        for (int j = 0; j < 4; ++j) {
            Edge* edge = new Edge(i * 4 + j, j % 2 == 0 ? EdgeType::INNER : EdgeType::OUTER);
            piece->setEdge(j, edge);
        }
        puzzle.addPiece(piece);
    }

    // 解决拼图
    if (puzzle.solve()) {
        std::cout << "拼图解决成功！" << std::endl;
        puzzle.display();
    } else {
        std::cout << "无法解决拼图。" << std::endl;
    }

    return 0;
}