#include "admission.h"

bool SortApplicants(const Applicant* student_first, const Applicant* student_second) {
    if (student_first->points == student_second->points) {
        return (std::tie(student_first->student.birth_date.year, student_first->student.birth_date.month,
                         student_first->student.birth_date.day, student_first->student.name) <
                std::tie(student_second->student.birth_date.year, student_second->student.birth_date.month,
                         student_second->student.birth_date.day, student_second->student.name));
    } else {
        return student_first->points > student_second->points;
    }
}

bool SortAns(const Student* student_first, const Student* student_second) {
    return std::tie(student_first->name, student_first->birth_date.year, student_first->birth_date.month,
                    student_first->birth_date.day) < std::tie(student_second->name, student_second->birth_date.year,
                                                              student_second->birth_date.month,
                                                              student_second->birth_date.day);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    AdmissionTable ans;
    std::unordered_map<std::string, std::size_t> max_stud;
    std::vector<const Applicant*> upd_applicants;
    upd_applicants.reserve(applicants.size());
    for (const auto& uni : universities) {
        max_stud[uni.name] = uni.max_students;
    }
    for (const auto& apl : applicants) {
        upd_applicants.push_back(&apl);
    }
    std::sort(upd_applicants.begin(), upd_applicants.end(), SortApplicants);

    for (const auto& stud : upd_applicants) {
        for (const auto& uni : stud->wish_list) {
            if (ans[uni].size() < max_stud[uni]) {
                ans[uni].push_back(&stud->student);
                break;
            }
        }
    }
    for (auto& i : ans) {
        sort(i.second.begin(), i.second.end(), SortAns);
    }
    return ans;
}
