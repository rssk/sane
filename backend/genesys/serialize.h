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

#ifndef BACKEND_GENESYS_SERIALIZE_H
#define BACKEND_GENESYS_SERIALIZE_H

#include "error.h"
#include <array>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

namespace genesys {

// it would be best to use something like boost.serialization

inline void serialize_newline(std::ostream& str) { str << '\n'; }
inline void serialize_newline(std::istream& str) { (void) str; }

inline void serialize(std::ostream& str, bool x) { str << static_cast<unsigned>(x) << " "; }
inline void serialize(std::istream& str, bool& x) { unsigned v; str >> v; x = v; }
inline void serialize(std::ostream& str, char x) { str << static_cast<int>(x) << " "; }
inline void serialize(std::istream& str, char& x) { int v; str >> v; x = v; }
inline void serialize(std::ostream& str, unsigned char x) { str << static_cast<unsigned>(x) << " "; }
inline void serialize(std::istream& str, unsigned char& x) { unsigned v; str >> v; x = v; }
inline void serialize(std::ostream& str, signed char x) { str << static_cast<int>(x) << " "; }
inline void serialize(std::istream& str, signed char& x) { int v; str >> v; x = v; }
inline void serialize(std::ostream& str, short x) { str << x << " "; }
inline void serialize(std::istream& str, short& x) { str >> x; }
inline void serialize(std::ostream& str, unsigned short x) { str << x << " "; }
inline void serialize(std::istream& str, unsigned short& x) { str >> x; }
inline void serialize(std::ostream& str, int x) { str << x << " "; }
inline void serialize(std::istream& str, int& x) { str >> x; }
inline void serialize(std::ostream& str, unsigned int x) { str << x << " "; }
inline void serialize(std::istream& str, unsigned int& x) { str >> x; }
inline void serialize(std::ostream& str, long x) { str << x << " "; }
inline void serialize(std::istream& str, long& x) { str >> x; }
inline void serialize(std::ostream& str, unsigned long x) { str << x << " "; }
inline void serialize(std::istream& str, unsigned long& x) { str >> x; }
inline void serialize(std::ostream& str, long long x) { str << x << " "; }
inline void serialize(std::istream& str, long long& x) { str >> x; }
inline void serialize(std::ostream& str, unsigned long long x) { str << x << " "; }
inline void serialize(std::istream& str, unsigned long long& x) { str >> x; }
inline void serialize(std::ostream& str, float x) { str << x << " "; }
inline void serialize(std::istream& str, float& x) { str >> x; }
inline void serialize(std::ostream& str, double x) { str << x << " "; }
inline void serialize(std::istream& str, double& x) { str >> x; }
inline void serialize(std::ostream& str, const std::string& x) { str << x << " "; }
inline void serialize(std::istream& str, std::string& x) { str >> x; }

template<class T>
void serialize(std::ostream& str, std::vector<T>& x)
{
    serialize(str, x.size());
    serialize_newline(str);

    for (auto& item : x) {
        serialize(str, item);
        serialize_newline(str);
    }
}

template<class T>
void serialize(std::istream& str, std::vector<T>& x,
               size_t max_size = std::numeric_limits<size_t>::max())
{
    size_t new_size;
    serialize(str, new_size);

    if (new_size > max_size) {
        throw SaneException("Too large std::vector to deserialize");
    }
    x.reserve(new_size);
    for (size_t i = 0; i < new_size; ++i) {
        T item;
        serialize(str, item);
        x.push_back(item);
    }
}

template<class T, size_t Size>
void serialize(std::ostream& str, std::array<T, Size>& x)
{
    serialize(str, x.size());
    serialize_newline(str);

    for (auto& item : x) {
        serialize(str, item);
        serialize_newline(str);
    }
}

template<class T, size_t Size>
void serialize(std::istream& str, std::array<T, Size>& x)
{
    size_t new_size;
    serialize(str, new_size);

    if (new_size > Size) {
        throw SaneException("Incorrect std::array size to deserialize");
    }
    for (auto& item : x) {
        serialize(str, item);
    }
}

} // namespace genesys

#endif
