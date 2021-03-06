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

#define DEBUG_DECLARE_ONLY

#include "test_settings.h"

namespace genesys {

namespace {

bool s_testing_mode = false;
std::uint16_t s_vendor_id = 0;
std::uint16_t s_product_id = 0;
std::uint16_t s_bcd_device = 0;
TestCheckpointCallback s_checkpoint_callback;

} // namespace

bool is_testing_mode()
{
    return s_testing_mode;
}

void disable_testing_mode()
{
    s_testing_mode = false;
    s_vendor_id = 0;
    s_product_id = 0;
    s_bcd_device = 0;
}

void enable_testing_mode(std::uint16_t vendor_id, std::uint16_t product_id,
                         std::uint16_t bcd_device,
                         TestCheckpointCallback checkpoint_callback)
{
    s_testing_mode = true;
    s_vendor_id = vendor_id;
    s_product_id = product_id;
    s_bcd_device = bcd_device;
    s_checkpoint_callback = checkpoint_callback;
}

std::uint16_t get_testing_vendor_id()
{
    return s_vendor_id;
}

std::uint16_t get_testing_product_id()
{
    return s_product_id;
}

std::uint16_t get_testing_bcd_device()
{
    return s_bcd_device;
}

std::string get_testing_device_name()
{
    std::string name;
    unsigned max_size = 50;
    name.resize(max_size);
    name.resize(std::snprintf(&name.front(), max_size, "test device:0x%04x:0x%04x",
                              s_vendor_id, s_product_id));
    return name;
}

TestCheckpointCallback get_testing_checkpoint_callback()
{
    return s_checkpoint_callback;
}

} // namespace genesys
