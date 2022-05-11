#include "scorer.h"
#include <tuple>
#include <vector>

bool SortEvent(const Event* first, const Event* second) {
    return (std::tie(first->student_name, first->task_name, first->time) <
            std::tie(second->student_name, second->task_name, second->time));
}

Event* CreateStud(const Event& stud) {
    Event* new_stud = new Event(stud);
    return new_stud;
}

void CheckEvent(const Event& student, bool& is_checked, bool& is_merged) {
    switch (student.event_type) {
        case EventType::CheckFailed:
            is_checked = false;
            break;
        case EventType::CheckSuccess:
            is_checked = true;
            break;
        case EventType::MergeRequestOpen:
            is_merged = false;
            break;
        case EventType::MergeRequestClosed:
            is_merged = true;
            break;
    }
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable ans;
    bool is_checked = true;
    bool is_merged = true;
    std::vector<Event*> upd_events;

    for (auto i : events) {
        if (i.time <= score_time) {
            upd_events.push_back(CreateStud(i));
        }
    }
    std::sort(upd_events.begin(), upd_events.end(), SortEvent);

    for (std::size_t i = 0; i < upd_events.size(); ++i) {
        if (i == 0) {
            CheckEvent(*upd_events[i], is_checked, is_merged);
        } else {
            if (upd_events[i]->student_name == upd_events[i - 1]->student_name &&
                upd_events[i]->task_name == upd_events[i - 1]->task_name) {
                CheckEvent(*upd_events[i], is_checked, is_merged);
            } else {
                if (is_checked && is_merged) {
                    ans[upd_events[i - 1]->student_name].insert(upd_events[i - 1]->task_name);
                }
                is_checked = true;
                is_merged = true;
                CheckEvent(*upd_events[i], is_checked, is_merged);
            }
        }
    }
    if (!upd_events.empty() && is_checked && is_merged) {
        ans[upd_events[upd_events.size() - 1]->student_name].insert(upd_events[upd_events.size() - 1]->task_name);
    }
    for (auto iter = upd_events.begin(); iter != upd_events.end(); ++iter) {
        delete *iter;
    }
    upd_events.clear();
    return ans;
}
