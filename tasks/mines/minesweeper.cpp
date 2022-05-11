#include "minesweeper.h"
#include <iostream>
#include <algorithm>
#include <ctime>
#include <queue>
#include <random>

void Minesweeper::Clear() {
    field_.clear();
    opened_cells_field_.clear();
    opened_cells_ = 0;
    game_status_ = GameStatus::NOT_STARTED;
    height_ = 0;
    width_ = 0;
}

void Minesweeper::MakeEmptyField() {
    field_ = std::vector<std::vector<char>>(height_, std::vector<char>(width_, '0'));
    opened_cells_field_ = std::vector<std::vector<int>>(height_, std::vector<int>(width_, 0));
}

void Minesweeper::UpdFieldDigit(const size_t& y, const size_t& x) {
    for (size_t i = std::max(y, static_cast<size_t>(1)); i < std::min(y + 3, height_ + 1); ++i) {
        for (size_t j = std::max(x, static_cast<size_t>(1)); j < std::min(x + 3, width_ + 1); ++j) {
            if (isdigit(field_[i - 1][j - 1])) {
                ++field_[i - 1][j - 1];
            }
        }
    }
}

void Minesweeper::AlgoOpenCell(const Cell& cell) {
    if (field_[cell.y][cell.x] == '*') {
        GameOver();
    } else {
        std::queue<std::pair<size_t, size_t>> q;
        q.push(std::make_pair(cell.y, cell.x));
        while (!q.empty()) {
            size_t y = q.front().first;
            size_t x = q.front().second;
            if (field_[y][x] == '0') {
                for (size_t i = std::max(y, static_cast<size_t>(1)); i < std::min(y + 3, height_ + 1); ++i) {
                    for (size_t j = std::max(x, static_cast<size_t>(1)); j < std::min(x + 3, width_ + 1); ++j) {
                        if (opened_cells_field_[i - 1][j - 1] == 0 && !(i - 1 == y && j - 1 == x)) {
                            q.push(std::make_pair(i - 1, j - 1));
                        }
                    }
                }
            }
            if (opened_cells_field_[y][x] == 0) {
                opened_cells_field_[y][x] = 1;
                ++opened_cells_;
            }
            q.pop();
        }
        if (all_cells_ - all_mines_ == opened_cells_ && opened_cells_ > 0) {
            GameWin();
        }
    }
}

void Minesweeper::GameOver() {
    overall_time_ += time_t(NULL) - time_begin_;
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            opened_cells_field_[i][j] = 1;
        }
    }
    game_status_ = GameStatus::DEFEAT;
}

void Minesweeper::GameWin() {
    overall_time_ += time_t(NULL) - time_begin_;
    game_status_ = GameStatus::VICTORY;
}

Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}

Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}

Minesweeper::RenderedField Minesweeper::RenderField() const {
    Minesweeper::RenderedField rendered_field;
    rendered_field.reserve(field_.size());
    for (size_t i = 0; i < height_; ++i) {
        std::string memo;
        for (size_t j = 0; j < width_; ++j) {
            if (opened_cells_field_[i][j] == 1) {
                if (field_[i][j] == '0') {
                    memo += '.';
                } else {
                    memo += field_[i][j];
                }
            } else if (opened_cells_field_[i][j] == 2) {
                memo += '?';
            } else {
                memo += '-';
            }
        }
        rendered_field.push_back(memo);
    }
    return rendered_field;
}

void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    std::vector<Cell> shuffle_vec;
    shuffle_vec.reserve(height * width);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            shuffle_vec.push_back({.x = j, .y = i});
        }
    }
    std::shuffle(shuffle_vec.begin(), shuffle_vec.end(), std::default_random_engine(time_t(NULL)));
    shuffle_vec.resize(mines_count);
    NewGame(width, height, shuffle_vec);
}

void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    Clear();
    width_ = width;
    height_ = height;
    all_cells_ = width * height;
    all_mines_ = cells_with_mines.size();
    MakeEmptyField();
    for (const auto& cell : cells_with_mines) {
        field_[cell.y][cell.x] = '*';
        UpdFieldDigit(cell.y, cell.x);
    }
}

void Minesweeper::OpenCell(const Cell& cell) {
    if (opened_cells_field_[cell.y][cell.x] == 0) {
        switch (game_status_) {
            case GameStatus::NOT_STARTED:
                time_begin_ = time(NULL);
                game_status_ = GameStatus::IN_PROGRESS;
            case GameStatus::IN_PROGRESS:
                AlgoOpenCell(cell);
                break;
            case GameStatus::VICTORY:
                break;
            case GameStatus::DEFEAT:
                break;
        }
    }
}

void Minesweeper::MarkCell(const Cell& cell) {
    switch (game_status_) {
        case GameStatus::NOT_STARTED:
            time_begin_ = time(NULL);
            game_status_ = GameStatus::IN_PROGRESS;
        case GameStatus::IN_PROGRESS:
            opened_cells_field_[cell.y][cell.x] = abs(opened_cells_field_[cell.y][cell.x] - 2);
            break;
        case GameStatus::VICTORY:
            break;
        case GameStatus::DEFEAT:
            break;
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return game_status_;
}

time_t Minesweeper::GetGameTime() const {
    return overall_time_;
}
