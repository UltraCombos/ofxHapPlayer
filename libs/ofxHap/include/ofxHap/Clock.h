/*
 Clock.h
 ofxHapPlayer

 Copyright (c) 2016, Tom Butterworth. All rights reserved.
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef Clock_h
#define Clock_h

#include <cstdint>

namespace ofxHap {
    class Clock {
    public:
		typedef int64_t(*fn_tick)(void*);

        enum class Mode {
            Once,
            Loop,
            Palindrome
        };
        enum class Direction {
            Forwards,
            Backwards
        };
        Clock();
		
		inline void setFnTick(fn_tick fn, void* arg) { _fn_tick = fn; _arg = arg; }

		int64_t		tick();
		inline int64_t getTick() { return _tick; }

        void		syncAt(int64_t pos, int64_t t);
        int64_t		getTime() const;
        int64_t		getTimeAt(int64_t t) const;
        int64_t		setTimeAt(int64_t t);
        void		setPausedAt(bool paused, int64_t t);
        bool		getPaused() const;
        Direction   getDirectionAt(int64_t t) const;
        float		getRate() const;
        void		setRateAt(float r, int64_t t);
        bool		getDone() const;
        void		rescale(int old, int next);

        Mode    mode;

		inline int64_t getPeriod() const { return _period; }
		inline void setPeriod(int64_t p) { _period = p; }

    private:
		int64_t volatile _tick;
		int64_t	_period;
		int64_t	_start;
		int64_t	_time;
		bool	_paused;
		float	_rate;
		fn_tick	_fn_tick;
		void*	_arg;
    };
}

#endif /* Clock_h */
