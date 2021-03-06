/* sane - Scanner Access Now Easy.

   Copyright (C) 2019 Povilas Kanapickas <povilas@radix.lt>

   This file is part of the SANE package.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef BACKEND_GENESYS_REGISTER_CACHE_H
#define BACKEND_GENESYS_REGISTER_CACHE_H

#include "register.h"

namespace genesys {

template<class Value>
class RegisterCache
{
public:
    void update(std::uint16_t address, Value value)
    {
        if (regs_.has_reg(address)) {
            regs_.set(address, value);
        } else {
            regs_.init_reg(address, value);
        }
    }

    void update(const Genesys_Register_Set& regs)
    {
        for (const auto& reg : regs) {
            update(reg.address, reg.value);
        }
    }

    Value get(std::uint16_t address) const
    {
        return regs_.get(address);
    }

private:
    RegisterContainer<Value> regs_;

    template<class V>
    friend std::ostream& operator<<(std::ostream& out, const RegisterCache<V>& cache);
};

template<class Value>
std::ostream& operator<<(std::ostream& out, const RegisterCache<Value>& cache)
{
    out << cache.regs_;
    return out;
}

} // namespace genesys

#endif // BACKEND_GENESYS_LINE_BUFFER_H
