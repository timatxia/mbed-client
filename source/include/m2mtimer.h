#ifndef M2M_TIMER_H
#define M2M_TIMER_H

#include <stdint.h>
#include "m2mtimerobserver.h"

//FORWARD DECLARATION
class M2MTimerImpl;

/**
* M2MTimer.
* Timer class for mbed client.
*/
class M2MTimer : public M2MTimerObserver {

public:

    // Prevents the use of assignment operator
    M2MTimer& operator=(const M2MTimer& /*other*/);

    // Prevents the use of copy constructor
    M2MTimer(const M2MTimer& other);

    /**
    * Constructor.
    */
    M2MTimer(M2MTimerObserver& observer);

    /**
    * Destructor.
    */
    virtual ~M2MTimer();

    /**
    * Starts timer
    * @param interval Timer's interval in milliseconds
    * @param single_shot defines if timer is ticked
    * once or is it restarted everytime timer is expired.
    */
    void start_timer(uint64_t interval,
                     Type type,
                     bool single_shot = true);

    /**
    * Stops timer.
    * This cancels the ongoing timer.
    */
    void stop_timer();

protected: // From M2MTimerObserver

    /**
    * Private implementation will call this.
    */
    virtual void timer_expired(M2MTimerObserver::Type type);

private:

    M2MTimerObserver            &_observer;
    M2MTimerImpl                *_impl;
    M2MTimerObserver::Type      _type;

friend class Test_M2MTimer;
};

#endif // M2M_TIMER_H