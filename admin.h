#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"

class admin : public User
{
protected:
    static admin* instance;
    admin();
public:
    static admin* getInstance();
};

#endif // ADMIN_H
