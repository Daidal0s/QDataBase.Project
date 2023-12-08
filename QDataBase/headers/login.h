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
}

inline Login::ROLE setLogin();

#endif // LOGIN_H