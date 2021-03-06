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

#ifndef BACKEND_GENESYS_IMAGE_BUFFER_H
#define BACKEND_GENESYS_IMAGE_BUFFER_H

#include "enums.h"
#include "row_buffer.h"
#include <algorithm>
#include <functional>

namespace genesys {

// This class allows reading from row-based source in smaller or larger chunks of data
class ImageBuffer
{
public:
    using ProducerCallback = std::function<bool(std::size_t size, std::uint8_t* out_data)>;
    static constexpr std::uint64_t BUFFER_SIZE_UNSET = std::numeric_limits<std::uint64_t>::max();

    ImageBuffer() {}
    ImageBuffer(std::size_t size, ProducerCallback producer);

    std::size_t available() const { return curr_size_ - buffer_offset_; }

    // allows adjusting the amount of data left so that we don't do a full size read from the
    // producer on the last iteration. Set to BUFFER_SIZE_UNSET to ignore buffer size.
    std::uint64_t remaining_size() const { return remaining_size_; }
    void set_remaining_size(std::uint64_t bytes) { remaining_size_ = bytes; }

    // May be used to force the last read to be rounded up of a certain number of bytes
    void set_last_read_multiple(std::uint64_t bytes) { last_read_multiple_ = bytes; }

    bool get_data(std::size_t size, std::uint8_t* out_data);

private:
    ProducerCallback producer_;
    std::size_t size_ = 0;
    std::size_t curr_size_ = 0;

    std::uint64_t remaining_size_ = BUFFER_SIZE_UNSET;
    std::uint64_t last_read_multiple_ = BUFFER_SIZE_UNSET;

    std::size_t buffer_offset_ = 0;
    std::vector<std::uint8_t> buffer_;
};

} // namespace genesys

#endif // BACKEND_GENESYS_IMAGE_BUFFER_H
