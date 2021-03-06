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

#ifndef BACKEND_GENESYS_TEST_USB_DEVICE_H
#define BACKEND_GENESYS_TEST_USB_DEVICE_H

#include "usb_device.h"

namespace genesys {

class TestUsbDevice : public IUsbDevice {
public:
    TestUsbDevice(std::uint16_t vendor, std::uint16_t product, std::uint16_t bcd_device);
    ~TestUsbDevice() override;

    bool is_open() const override { return is_open_; }

    const std::string& name() const override { return name_; }

    void open(const char* dev_name) override;

    void clear_halt() override;
    void reset() override;
    void close() override;

    std::uint16_t get_vendor_id() override;
    std::uint16_t get_product_id() override;
    std::uint16_t get_bcd_device() override;

    void control_msg(int rtype, int reg, int value, int index, int length,
                     std::uint8_t* data) override;
    void bulk_read(std::uint8_t* buffer, std::size_t* size) override;
    void bulk_write(const std::uint8_t* buffer, std::size_t* size) override;
private:
    void assert_is_open() const;

    std::string name_;
    bool is_open_ = false;
    std::uint16_t vendor_ = 0;
    std::uint16_t product_ = 0;
    std::uint16_t bcd_device_ = 0;
};

} // namespace genesys

#endif // BACKEND_GENESYS_TEST_USB_DEVICE_H
