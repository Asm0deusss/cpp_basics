#include "scorer.h"

bool Scorer::IsInInfo(const StudentName& student_name, const TaskName& task_name,
                      std::map<StudentName, std::map<TaskName, std::pair<bool, bool>>>& info) {
    if (!info[student_name].contains(task_name)) {
        info[student_name][task_name].first = false;
        info[student_name][task_name].second = true;
    }
    return true;
}

void Scorer::UpdStudent(std::map<StudentName, std::map<TaskName, std::pair<bool, bool>>>& info, ScoreTable& student,
                        const TaskName& task_name, const StudentName& student_name) {
    if (info[student_name][task_name].first && info[student_name][task_name].second) {
        student[student_name].insert(task_name);
    } else {
        student[student_name].erase(task_name);
    }
    if (student_[student_name].empty()) {
        student_.erase(student_name);
    }
}

void Scorer::OnCheckFailed(const StudentName& student_name, const TaskName& task_name) {
    IsInInfo(student_name, task_name, info_);
    info_[student_name][task_name].first = false;
    UpdStudent(info_, student_, task_name, student_name);
};
void Scorer::OnCheckSuccess(const StudentName& student_name, const TaskName& task_name) {
    IsInInfo(student_name, task_name, info_);
    info_[student_name][task_name].first = true;
    UpdStudent(info_, student_, task_name, student_name);
};
void Scorer::OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name) {
    IsInInfo(student_name, task_name, info_);
    info_[student_name][task_name].second = false;
    UpdStudent(info_, student_, task_name, student_name);
};
void Scorer::OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name) {
    IsInInfo(student_name, task_name, info_);
    info_[student_name][task_name].second = true;
    UpdStudent(info_, student_, task_name, student_name);
};
void Scorer::Reset() {
    info_.clear();
    student_.clear();
};

ScoreTable Scorer::GetScoreTable() const {
    return student_;
};
