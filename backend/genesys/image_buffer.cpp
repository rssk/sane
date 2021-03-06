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

#include "image_buffer.h"
#include "image.h"
#include "utilities.h"

namespace genesys {

ImageBuffer::ImageBuffer(std::size_t size, ProducerCallback producer) :
    producer_{producer},
    size_{size}
{
    buffer_.resize(size_);
}

bool ImageBuffer::get_data(std::size_t size, std::uint8_t* out_data)
{
    const std::uint8_t* out_data_end = out_data + size;

    auto copy_buffer = [&]()
    {
        std::size_t bytes_copy = std::min<std::size_t>(out_data_end - out_data, available());
        std::memcpy(out_data, buffer_.data() + buffer_offset_, bytes_copy);
        out_data += bytes_copy;
        buffer_offset_ += bytes_copy;
    };

    // first, read remaining data from buffer
    if (available() > 0) {
        copy_buffer();
    }

    if (out_data == out_data_end) {
        return true;
    }

    // now the buffer is empty and there's more data to be read
    bool got_data = true;
    do {
        buffer_offset_ = 0;

        std::size_t size_to_read = size_;
        if (remaining_size_ != BUFFER_SIZE_UNSET) {
            size_to_read = std::min<std::uint64_t>(size_to_read, remaining_size_);
            remaining_size_ -= size_to_read;
        }

        std::size_t aligned_size_to_read = size_to_read;
        if (remaining_size_ == 0 && last_read_multiple_ != BUFFER_SIZE_UNSET) {
            aligned_size_to_read = align_multiple_ceil(size_to_read, last_read_multiple_);
        }

        got_data &= producer_(aligned_size_to_read, buffer_.data());
        curr_size_ = size_to_read;

        copy_buffer();

        if (remaining_size_ == 0 && out_data < out_data_end) {
            got_data = false;
        }

    } while (out_data < out_data_end && got_data);

    return got_data;
}

} // namespace genesys
