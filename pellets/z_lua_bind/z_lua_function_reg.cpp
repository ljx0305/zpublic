/*************************************************************************
 *                                                                       *
 *  I|*j^3Cl|a   "+!*%                  qt          Nd   gW              *
 *  l]{y+l?MM*  !#Wla\NNP               NW          MM   I|              *
 *        PW    ?E|    tWg              Wg  sC!     AW           ~@v~    *
 *       NC     ?M!    yN|  WW     MK   MW@K1Y%M@   RM   #Q    QP@tim    *
 *     CM|      |WQCljAE|   MD     Mg   RN     cM~  NM   WQ   MQ         *
 *    #M        aQ?         MW     M3   Mg      Q(  HQ   YR  IM|         *
 *   Dq         {Ql         MH    iMX   Mg     MM   QP   QM   Eg         *
 * !EWNaPRag2$  +M"          $WNaHaN%   MQE$%EXW    QQ   CM    %M%a$D    *
 *                                                                       *
 *                               ZPublic                                 *
 *                  Developer: zapline(278998871@qq.com)                 *
 *               Website: https://github.com/zpublic/zpublic             *
 *                                                                       *
 ************************************************************************/
#include "stdafx.h"
#include "z_lua_function_reg.h"

z_lua_function_reg::z_lua_function_reg() : libname_("z")
{

}

z_lua_function_reg::~z_lua_function_reg()
{

}

void z_lua_function_reg::insert_no_prefix( const char *name, lua_CFunction func )
{
    if (name 
        && *name != 0
        && func)
    {
        funcs_[std::string(name)] = func;
    }
}

void z_lua_function_reg::insert_no_prefix( const luaL_Reg* pfuncs )
{
    if (pfuncs)
    {
        for (int n = 0; pfuncs[n].name != 0; ++n)
        {
            insert_no_prefix(pfuncs[n].name, pfuncs[n].func);
        }
    }
}

void z_lua_function_reg::insert( const char *name, lua_CFunction func )
{
    if (name 
        && *name != 0
        && func)
    {
        std::string s = prefix_ + name;
        insert_no_prefix(s.c_str(), func);
    }
}

void z_lua_function_reg::insert( const luaL_Reg* pfuncs )
{
    if (pfuncs)
    {
        for (int n = 0; pfuncs[n].name != 0; ++n)
        {
            insert(pfuncs[n].name, pfuncs[n].func);
        }
    }
}

void z_lua_function_reg::erase( const char *name )
{
    if (name && *name != 0)
    {
        std::map<std::string, lua_CFunction>::iterator itFind =
            funcs_.find(std::string(name));
        if (itFind != funcs_.end())
        {
            funcs_.erase(itFind);
        }
    }
}

luaL_Reg* z_lua_function_reg::create()
{
    if (funcs_.size() > 0)
    {
        luaL_Reg* pfuncs = new luaL_Reg[funcs_.size() + 1];
        int i = 0;
        std::map<std::string, lua_CFunction>::iterator it = funcs_.begin();
        while (it != funcs_.end())
        {
            ///> 好吧 这里的内存相当危险 不能乱加减函数 就这样吧
            pfuncs[i].name = it->first.c_str();
            pfuncs[i].func = it->second;
            ++i;
            ++it;
        }
        pfuncs[i].name = 0;
        pfuncs[i].func = 0;
        return pfuncs;
    }
    return NULL;
}

void z_lua_function_reg::close( luaL_Reg* pfuncs )
{
    if (pfuncs)
    {
        delete[] pfuncs;
    }
}
