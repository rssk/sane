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

#ifndef BACKEND_GENESYS_SCANNER_INTERFACE_H
#define BACKEND_GENESYS_SCANNER_INTERFACE_H

#include "fwd.h"
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace genesys {

// Represents an interface through which all low level operations are performed.
class ScannerInterface
{
public:

    virtual ~ScannerInterface();

    virtual bool is_mock() const = 0;

    virtual std::uint8_t read_register(std::uint16_t address) = 0;
    virtual void write_register(std::uint16_t address, std::uint8_t value) = 0;
    virtual void write_registers(const Genesys_Register_Set& regs) = 0;

    virtual void write_0x8c(std::uint8_t index, std::uint8_t value) = 0;
    virtual void bulk_read_data(std::uint8_t addr, std::uint8_t* data, std::size_t size) = 0;
    virtual void bulk_write_data(std::uint8_t addr, std::uint8_t* data, std::size_t size) = 0;

    // GL646, GL841, GL843 have different ways to write to RAM and to gamma tables
    virtual void write_buffer(std::uint8_t type, std::uint32_t addr, std::uint8_t* data,
                              std::size_t size) = 0;

    virtual void write_gamma(std::uint8_t type, std::uint32_t addr, std::uint8_t* data,
                             std::size_t size) = 0;

    // GL845, GL846, GL847 and GL124 have a uniform way to write to RAM tables
    virtual void write_ahb(std::uint32_t addr, std::uint32_t size, std::uint8_t* data) = 0;

    virtual std::uint16_t read_fe_register(std::uint8_t address) = 0;
    virtual void write_fe_register(std::uint8_t address, std::uint16_t value) = 0;

    virtual IUsbDevice& get_usb_device() = 0;

    // sleeps the specified number of microseconds. Will not sleep if testing mode is enabled.
    virtual void sleep_us(unsigned microseconds) = 0;

    void sleep_ms(unsigned milliseconds)
    {
        sleep_us(milliseconds * 1000);
    }

    virtual void record_progress_message(const char* msg) = 0;

    virtual void record_slope_table(unsigned table_nr, const std::vector<std::uint16_t>& steps) = 0;

    virtual void record_key_value(const std::string& key, const std::string& value) = 0;

    virtual void test_checkpoint(const std::string& name) = 0;
};

} // namespace genesys

#endif
