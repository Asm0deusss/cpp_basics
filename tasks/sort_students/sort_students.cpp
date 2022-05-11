#include "sort_students.h"
#include <tuple>

bool NameSort(const Student& student_first, const Student& student_second) {
    return (std::tie(student_first.last_name, student_first.name, student_first.birth_date.year,
                     student_first.birth_date.month, student_first.birth_date.day) <
            std::tie(student_second.last_name, student_second.name, student_second.birth_date.year,
                     student_second.birth_date.month, student_second.birth_date.day));
}

bool DateSort(const Student& student_first, const Student& student_second) {
    return (std::tie(student_first.birth_date.year, student_first.birth_date.month, student_first.birth_date.day,
                     student_first.last_name, student_first.name) <
            std::tie(student_second.birth_date.year, student_second.birth_date.month, student_second.birth_date.day,
                     student_second.last_name, student_second.name));
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Name) {
        std::sort(students.begin(), students.end(), NameSort);
    }
    if (sortKind == SortKind::Date) {
        std::sort(students.begin(), students.end(), DateSort);
    }
}
