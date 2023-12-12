#include "login.h"

Login::ROLE Login::setLogin(int indexFromDB)
{
    switch (indexFromDB)
    {
    case 1:
        return Login::ROLE::ADMIN;
        break;
    case 2:
        return Login::ROLE::DEV;
        break;
    case 3:
        return Login::ROLE::TEAMLEADER;
        break;
    default:
        break;
    }
    return Login::ROLE::DEV;
}
