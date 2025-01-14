/*
 *
 *    Copyright (c) 2021 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#pragma once

#include "Base38.h"

#include <support/Span.h>

#include <stddef.h>

namespace chip {

// out_buf is null-terminated on success
CHIP_ERROR base38Encode(ByteSpan in_buf, MutableCharSpan & out_buf);

// returns size needed to store encoded string given number of input bytes
size_t base38EncodedLength(size_t num_bytes);

} // namespace chip
