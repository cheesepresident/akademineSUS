#include "admin.h"

admin* admin::instance = nullptr;

admin::admin()
{}
admin* admin::getInstance()
{
    if (!instance)
    {
        instance = new admin();
    }
    return instance;
}
