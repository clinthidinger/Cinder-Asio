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

#include "DispatcherInterface.h"
#include <boost/asio/deadline_timer.hpp>

typedef std::shared_ptr<class WaitTimer> WaitTimerRef;

class WaitTimer : public DispatcherInterface, public std::enable_shared_from_this<WaitTimer>
{
public:
	static WaitTimerRef		create( asio::io_service& io );
	~WaitTimer();

	virtual void			wait( size_t millis, bool repeat );

	template< typename T, typename Y >
	inline void				connectWaitEventHandler( T eventHandler, Y* eventHandlerObject )
	{
		connectWaitEventHandler( std::bind( eventHandler, eventHandlerObject ) );
	}

	void					connectWaitEventHandler( const std::function<void ()>& eventHandler );
protected:
	WaitTimer( asio::io_service& io );

    boost::asio::deadline_timer	mTimer;
	size_t					mTimerInterval;
	bool					mTimerRepeat;

	virtual void			onWait( const asio::error_code& err );

	std::function<void ()>	mWaitEventHandler;
};
