#include <iostream>

#include <vector>
#include <map>
#include <string>

using namespace std;

// This file is read-only. Any changes made to this file will be ignored.

struct Student {
    std::string name_;
    std::map<std::string, double> grades_;
};

class GradesDB {
public:
    size_t GetStudentCount() const;

    enum class AddResult { NewEntry, NewGrade, GradeOverwritten };
    AddResult Add(const std::string& name, const std::string& subject, double grade);
    
    std::pair<bool, double> GetAverageForStudent(const std::string& name) const;
    std::pair<bool, double> GetAverageForSubject(const std::string& subject) const;
private:
    std::vector<Student> database_;
};


int main(){





    cout << "Hello World!";
    return 0;
}


size_t GradesDB::GetStudentCount() const {
    //count of students in the database_
    return database_.size();
}

GradesDB::AddResult GradesDB::Add(const std::string& name, const std::string& subject, double grade) {
    std::cout << "This is debug output " << name << "\n";
    //add grade information for the selected student
    //if the student is not in the database, add the student to the database
    // //if the student is in the database, add the grade to the student's grades
    // //if the student is in the database and the subject is in the student's grades, overwrite the grade
    // //return the result of the operation
    // //if the student is not in the database, return NewEntry
    // //if the student is in the database and the subject is not in the student's grades, return NewGrade
    // //if the student is in the database and the subject is in the student's grades, return GradeOverwritten
    if(database_.size() == 0){
        Student new_student;
        new_student.name_ = name;
        new_student.grades_[subject] = grade;
        database_.push_back(new_student);
        return AddResult::NewEntry;
    }
    else{
        for(auto& student: database_){
            if(student.name_ == name){
                if(student.grades_.find(subject) != student.grades_.end()){
                    //grade found
                    student.grades_[subject] = grade;
                    return AddResult::GradeOverwritten;
                }
                else{
                    //grade not found
                    student.grades_[subject] = grade;
                    return AddResult::NewGrade;
                }
            }
        }
        Student new_student;
        new_student.name_ = name;
        new_student.grades_[subject] = grade;
        database_.push_back(new_student);
        return AddResult::NewEntry;
    }
    
    // database_.push_back(Student{name, {{subject, grade}}});
    // if(database_.size() == 1){
    //     return AddResult::NewEntry;
    // }
    // else if(database_.size() > 1){
    //     return AddResult::NewGrade;
    // }
    // else{
    //     return AddResult::GradeOverwritten;
    // }
}

std::pair<bool, double> GradesDB::GetAverageForStudent(const std::string& name) const {
    //return the average grade for the selected student
    //if the student is not in the database, return false
    //if the student is in the database, return true and the average grade
    double sum = 0;
    int count = 0;
    for(auto& student: database_){
        if(student.name_ == name){
            for(auto& grade: student.grades_){
                sum += grade.second;
                count++;
            }
            return {true, sum/count};
        }
    }
    return {false, 0};
}

std::pair<bool, double> GradesDB::GetAverageForSubject(const std::string& subject) const {
    //return the average grade for the selected subject
    //if the subject is not in the database, return false
    //if the subject is in the database, return true and the average grade
    double sum = 0;
    int count = 0;
    for(auto& student: database_){
        if(student.grades_.find(subject) != student.grades_.end()){
            sum += student.grades_.at(subject);
            count++;
        }
    }
    if(count == 0){
        return {false, 0};
    }
    else{
        return {true, sum/count};
    }
}



/*
#include "grades.h"
#include <iostream>

size_t GradesDB::GetStudentCount() const {
    return database_.size();
}

GradesDB::AddResult GradesDB::Add(const std::string& name, const std::string& subject, double grade) {
    std::cout << "This is debug output " << name << "\n";
    if(database_.size() == 0){
        Student new_student;
        new_student.name_ = name;
        new_student.grades_[subject] = grade;
        database_.push_back(new_student);
        return AddResult::NewEntry;
    }
    else{
        for(auto& student: database_){
            if(student.name_ == name){
                if(student.grades_.find(subject) != student.grades_.end()){
                    //grade found
                    student.grades_[subject] = grade;
                    return AddResult::GradeOverwritten;
                }
                else{
                    //grade not found
                    student.grades_[subject] = grade;
                    return AddResult::NewGrade;
                }
            }
        }
        Student new_student;
        new_student.name_ = name;
        new_student.grades_[subject] = grade;
        database_.push_back(new_student);
        return AddResult::NewEntry;
    }
}

std::pair<bool, double> GradesDB::GetAverageForStudent(const std::string& name) const {
    double sum = 0;
    int count = 0;
    for(auto& student: database_){
        if(student.name_ == name){
            for(auto& grade: student.grades_){
                sum += grade.second;
                count++;
            }
            return {true, sum/count};
        }
    }
    return {false, 0};
}

std::pair<bool, double> GradesDB::GetAverageForSubject(const std::string& subject) const {
    //return the average grade for the selected subject
    //if the subject is not in the database, return false
    //if the subject is in the database, return true and the average grade
    double sum = 0;
    int count = 0;
    for(auto& student: database_){
        if(student.grades_.find(subject) != student.grades_.end()){
            sum += student.grades_.at(subject);
            count++;
        }
    }
    if(count == 0){
        return {false, 0};
    }
    else{
        return {true, sum/count};
    }
}
*/



///  // if (is_packet_started) {
    //     collected_packets.push_back(current_packet);
    //     current_packet = "";
    //     current_id = 0;
    //     current_control_sum = 0;
    // }
    // is_packet_started = true;

    // if (!is_packet_started) {
    //     return false;
    // }
    // if (id != current_id) {
    //     numof_failed_parts++;
    //     return false;
    // }
    // if (controlSum != std::hash<std::string>{}(data)) {
    //     numof_failed_parts++;
    //     return false;
    // }
    // current_packet += data;
    // current_id++;
    // current_control_sum += controlSum;
    // return true;