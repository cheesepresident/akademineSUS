#ifndef STUDENT_H
#define STUDENT_H
#include "user.h"
using namespace std;
class student : public User
{
protected:
    static student* instance;
    student();
    QString group;
    int semester, groupID;
    vector<QString> subjects;
    vector<int> subjectsID;
public:
    static student* getInstance();
    QString getGroup();
    int getSemester();
    int getGroupID();
    void loadUserInfo();
    vector<QString> getSubjects();
    vector<int> getSubjectsID();
};

#endif // STUDENT_H
