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

#ifndef BACKEND_GENESYS_TEST_SCANNER_INTERFACE_H
#define BACKEND_GENESYS_TEST_SCANNER_INTERFACE_H

#include "scanner_interface.h"
#include "register_cache.h"
#include "test_usb_device.h"
#include "test_settings.h"

#include <map>

namespace genesys {

class TestScannerInterface : public ScannerInterface
{
public:
    TestScannerInterface(Genesys_Device* dev, std::uint16_t vendor_id, std::uint16_t product_id,
                         std::uint16_t bcd_device);

    ~TestScannerInterface() override;

    bool is_mock() const override;

    const RegisterCache<std::uint8_t>& cached_regs() const { return cached_regs_; }
    const RegisterCache<std::uint16_t>& cached_fe_regs() const { return cached_fe_regs_; }

    std::uint8_t read_register(std::uint16_t address) override;
    void write_register(std::uint16_t address, std::uint8_t value) override;
    void write_registers(const Genesys_Register_Set& regs) override;

    void write_0x8c(std::uint8_t index, std::uint8_t value) override;
    void bulk_read_data(std::uint8_t addr, std::uint8_t* data, std::size_t size) override;
    void bulk_write_data(std::uint8_t addr, std::uint8_t* data, std::size_t size) override;

    void write_buffer(std::uint8_t type, std::uint32_t addr, std::uint8_t* data,
                      std::size_t size) override;
    void write_gamma(std::uint8_t type, std::uint32_t addr, std::uint8_t* data,
                     std::size_t size) override;
    void write_ahb(std::uint32_t addr, std::uint32_t size, std::uint8_t* data) override;

    std::uint16_t read_fe_register(std::uint8_t address) override;
    void write_fe_register(std::uint8_t address, std::uint16_t value) override;

    IUsbDevice& get_usb_device() override;

    void sleep_us(unsigned microseconds) override;

    void record_progress_message(const char* msg) override;

    const std::string& last_progress_message() const;

    void record_slope_table(unsigned table_nr, const std::vector<std::uint16_t>& steps) override;

    std::map<unsigned, std::vector<std::uint16_t>>& recorded_slope_tables();

    void record_key_value(const std::string& key, const std::string& value) override;

    std::map<std::string, std::string>& recorded_key_values();

    void test_checkpoint(const std::string& name) override;

    void set_checkpoint_callback(TestCheckpointCallback callback);

private:
    Genesys_Device* dev_;

    RegisterCache<std::uint8_t> cached_regs_;
    RegisterCache<std::uint16_t> cached_fe_regs_;
    TestUsbDevice usb_dev_;

    TestCheckpointCallback checkpoint_callback_;

    std::map<unsigned, std::vector<std::uint16_t>> slope_tables_;

    std::string last_progress_message_;
    std::map<std::string, std::string> key_values_;
};

} // namespace genesys

#endif
