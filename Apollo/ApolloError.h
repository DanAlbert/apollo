/**
 * @file ApolloError.h
 * @author Dan Albert <dan@gingerhq.net>
 * @date Last updated 06/11/2012
 * @version 0.2.53
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
 * Defines base exception class for Apollo.
 *
 * All exceptions thrown within Apollo MUST be caught by Apollo. Do not allow
 * exceptions to propagate to client applications. The only exception to this
 * rule pertains to RAII. If a client application extends an Apollo class, the
 * derived class will either need to catch and handle an exception thrown by
 * the parent classes constructor, or allow it to propagate out of the derived
 * class.
 * 
 * DO throw exceptions from constructors.
 * Do NOT throw exceptions from destructors. 
 *
 * Unless absolutely unavoidable, exceptions should not be used in engine
 * runtime code (i.e. the main loop). Exceptions to this rule are for functions
 * that need a way to return failure, but the entire domain of the return type
 * could be returned as a valid result; and constructors. For example, if a
 * function that returns and integer in the main loop were to encounter an
 * error to be handled by the caller, the only way to signal an error would be
 * to throw an exception.
 * 
 */
#ifndef APOLLOERROR_H
#define APOLLOERROR_H

#include <stdexcept>

#include "Apollo.h"

namespace Apollo
{
	class APOLLO_API ApolloError : public std::runtime_error
	{
	public:
		explicit ApolloError(const int err) throw();
		const int getErrNo(void) const throw();
		const char* getErrStr(void) const throw();

	private:
		int errNo;
	};
}

#endif // APOLLOERROR_H
