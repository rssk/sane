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

#include "test_usb_device.h"
#include "low.h"

namespace genesys {

TestUsbDevice::TestUsbDevice(std::uint16_t vendor, std::uint16_t product,
                             std::uint16_t bcd_device) :
    vendor_{vendor},
    product_{product},
    bcd_device_{bcd_device}
{
}

TestUsbDevice::~TestUsbDevice()
{
    if (is_open()) {
        DBG(DBG_error, "TestUsbDevice not closed; closing automatically");
        close();
    }
}

void TestUsbDevice::open(const char* dev_name)
{
    DBG_HELPER(dbg);

    if (is_open()) {
        throw SaneException("device already open");
    }
    name_ = dev_name;
    is_open_ = true;
}

void TestUsbDevice::clear_halt()
{
    DBG_HELPER(dbg);
    assert_is_open();
}

void TestUsbDevice::reset()
{
    DBG_HELPER(dbg);
    assert_is_open();
}

void TestUsbDevice::close()
{
    DBG_HELPER(dbg);
    assert_is_open();

    is_open_ = false;
    name_ = "";
}

std::uint16_t TestUsbDevice::get_vendor_id()
{
    DBG_HELPER(dbg);
    assert_is_open();
    return vendor_;
}

std::uint16_t TestUsbDevice::get_product_id()
{
    DBG_HELPER(dbg);
    assert_is_open();
    return product_;
}

std::uint16_t TestUsbDevice::get_bcd_device()
{
    DBG_HELPER(dbg);
    assert_is_open();
    return bcd_device_;
}

void TestUsbDevice::control_msg(int rtype, int reg, int value, int index, int length,
                                std::uint8_t* data)
{
    (void) reg;
    (void) value;
    (void) index;
    DBG_HELPER(dbg);
    assert_is_open();
    if (rtype == REQUEST_TYPE_IN) {
        std::memset(data, 0, length);
    }
}

void TestUsbDevice::bulk_read(std::uint8_t* buffer, std::size_t* size)
{

    DBG_HELPER(dbg);
    assert_is_open();
    std::memset(buffer, 0, *size);
}

void TestUsbDevice::bulk_write(const std::uint8_t* buffer, std::size_t* size)
{
    (void) buffer;
    (void) size;
    DBG_HELPER(dbg);
    assert_is_open();
}

void TestUsbDevice::assert_is_open() const
{
    if (!is_open()) {
        throw SaneException("device not open");
    }
}

} // namespace genesys
