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

#ifndef BACKEND_GENESYS_CALIBRATION_H
#define BACKEND_GENESYS_CALIBRATION_H

#include "sensor.h"
#include "settings.h"
#include <ctime>

namespace genesys {

struct Genesys_Calibration_Cache
{
    Genesys_Calibration_Cache() = default;
    ~Genesys_Calibration_Cache() = default;

    // used to check if entry is compatible
    SetupParams params;

    std::time_t last_calibration = 0;

    Genesys_Frontend frontend;
    Genesys_Sensor sensor;

    ScanSession session;
    size_t average_size = 0;
    std::vector<std::uint16_t> white_average_data;
    std::vector<std::uint16_t> dark_average_data;

    bool operator==(const Genesys_Calibration_Cache& other) const
    {
        return params == other.params &&
            last_calibration == other.last_calibration &&
            frontend == other.frontend &&
            sensor == other.sensor &&
            session == other.session &&
            average_size == other.average_size &&
            white_average_data == other.white_average_data &&
            dark_average_data == other.dark_average_data;
    }
};

template<class Stream>
void serialize(Stream& str, Genesys_Calibration_Cache& x)
{
    serialize(str, x.params);
    serialize_newline(str);
    serialize(str, x.last_calibration);
    serialize_newline(str);
    serialize(str, x.frontend);
    serialize_newline(str);
    serialize(str, x.sensor);
    serialize_newline(str);
    serialize(str, x.session);
    serialize(str, x.average_size);
    serialize_newline(str);
    serialize(str, x.white_average_data);
    serialize_newline(str);
    serialize(str, x.dark_average_data);
}

} // namespace genesys

#endif // BACKEND_GENESYS_CALIBRATION_H
