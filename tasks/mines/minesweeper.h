#pragma once

#include <string>
#include <vector>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    void UpdFieldDigit(const size_t& y, const size_t& x);
    void MakeEmptyField();
    void GameOver();
    void GameWin();
    void Clear();
    void AlgoOpenCell(const Cell& cell);
    std::vector<std::vector<char>> field_;
    std::vector<std::vector<int>> opened_cells_field_;
    size_t height_;
    size_t width_;
    size_t opened_cells_ = 0;
    size_t all_cells_;
    size_t all_mines_;
    time_t overall_time_ = 0;
    time_t time_begin_ = 0;
    GameStatus game_status_ = GameStatus::NOT_STARTED;
};
