#pragma once

#include <map>
#include <set>
#include <string>
#include <vector>

using StudentName = std::string;
using TaskName = std::string;

using ScoreTable = std::map<StudentName, std::set<TaskName>>;

class Scorer {
private:
    std::map<StudentName, std::map<TaskName, std::pair<bool, bool>>> info_;
    ScoreTable student_;
    bool IsInInfo(const StudentName& student_name, const TaskName& task_name,
                  std::map<StudentName, std::map<TaskName, std::pair<bool, bool>>>& info);
    void UpdStudent(std::map<StudentName, std::map<TaskName, std::pair<bool, bool>>>& info, ScoreTable& student,
                    const TaskName& task_name, const StudentName& student_name);

public:
    void OnCheckFailed(const StudentName& student_name, const TaskName& task_name);
    void OnCheckSuccess(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestOpen(const StudentName& student_name, const TaskName& task_name);
    void OnMergeRequestClosed(const StudentName& student_name, const TaskName& task_name);
    void Reset();

    ScoreTable GetScoreTable() const;
};
