/*
* 
* Copyright (c) 2015, Wieden+Kennedy, 
* Stephen Schieberl, Michael Latzoni
* All rights reserved.
* 
* Redistribution and use in source and binary forms, with or 
* without modification, are permitted provided that the following 
* conditions are met:
* 
* Redistributions of source code must retain the above copyright 
* notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright 
* notice, this list of conditions and the following disclaimer in 
* the documentation and/or other materials provided with the 
* distribution.
* 
* Neither the name of the Ban the Rewind nor the names of its 
* contributors may be used to endorse or promote products 
* derived from this software without specific prior written 
* permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
* COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
* ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
*/

#pragma once

#include "CinderAsio.h"


#include "boost/bind.hpp"
#include <string>
#include <functional>
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>

class DispatcherInterface
{
public:
	~DispatcherInterface();

	template< typename T, typename Y >
	inline void			connectErrorEventHandler( T eventHandler, Y* eventHandlerObject )
	{
		connectErrorEventHandler( std::bind( eventHandler, eventHandlerObject, std::placeholders::_1, std::placeholders::_2 ) );
	}
	void				connectErrorEventHandler( const std::function<void( std::string, size_t )>& eventHandler );
protected:
    DispatcherInterface( const std::shared_ptr<boost::asio::io_service>& io );

    std::shared_ptr<boost::asio::io_service> mIoService;
    boost::asio::strand		mStrand;

	std::function<void( std::string, size_t )>	mErrorEventHandler;
};
