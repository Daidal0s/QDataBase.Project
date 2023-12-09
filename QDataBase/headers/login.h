#ifndef LOGIN_H
#define LOGIN_H

#pragma once

namespace Login
{
    enum ROLE
    {
        ADMIN,
        DEV,
        TEAMLEADER
    };

    Login::ROLE setLogin(int indexFromDB);
}


#endif // LOGIN_H