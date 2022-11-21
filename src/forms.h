#pragma once

#include <cmath>

#include "constants.h"

namespace smail
{
    namespace detail
    {
        template <typename in_t> auto f_mod(const in_t& inp, const in_t& modu)
        {
            // return ()%modu;
            if (inp>0) return fmod(inp, modu);
            return fmod(inp + ((int)(-inp/modu) + 1)*modu, modu);
            // return 
        }
    }
    
    //all forms are periodic over (0,2*pi)
    
    //"woo"
    template <typename in_t> auto sin(const in_t& inp) { return std::sin(inp); }
    
    //"woo"
    template <typename in_t> auto cos(const in_t& inp) { return std::cos(inp); }
    
    //dull buzz
    template <typename in_t> auto sqr(const in_t& inp)
    {
        auto md = detail::f_mod(inp, 2.0*pi);
        return (md < pi)?(1):(-1);
    }
    
    //sharp buzz
    template <typename in_t> auto saw(const in_t& inp)
    {
        auto md = detail::f_mod(inp, 2.0*pi);
        return (md/(pi))-1.0;
    }
}