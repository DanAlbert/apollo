/**
 * @file StringUtil.h
 * @author Dan Albert <dan@gingerhq.net>
 *
 * @section LICENSE
 * 
 * Apollo 2D Rendering Engine
 * Copyright (C) 2012 Dan Albert
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * @section DESCRIPTION
 * 
 * Defines some string utility functions that are not included in the C strings
 * library or the C++ std::string interface.
 * 
 */
#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include "Apollo.h"

#include <algorithm>
#include <string>

void Chomp(std::string& str);
void TrimSpaces(std::string& str);
void TrimLeadingSpaces(std::string& str);
void TrimTrailingSpaces(std::string& str);
std::string APOLLO_API ToLower(const std::string& str);
std::string APOLLO_API ToUpper(const std::string& str);

#endif // STRINGUTIL_H
