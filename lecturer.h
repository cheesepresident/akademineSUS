#ifndef LECTURER_H
#define LECTURER_H
#include "user.h"
#include <vector>
using namespace std;
class lecturer : public User
{
protected:
    static lecturer* instance;
    lecturer();
    vector<QString> subjects;
    vector<QString> subjectSGroups;
    vector<QString> subjectsID;
    vector<QString> subjectSGroupsID;

public:
    static lecturer* getInstance();
    void setSubjects();
    vector<QString> getSubjects();
    vector<QString> getSubjectSGroups();
    vector<QString> getSubjectsID();
    vector<QString> getSubjectSGroupsID();
};

#endif // LECTURER_H
