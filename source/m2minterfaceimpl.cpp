#include <assert.h>
#include "include/m2minterfaceimpl.h"
#include "include/eventdata.h"
#include "lwm2m-client/m2minterfaceobserver.h"
#include "include/m2mconnectionhandler.h"
#include "include/m2mnsdlinterface.h"
#include "lwm2m-client/m2msecurity.h"
#include "lwm2m-client/m2mconstants.h"

M2MInterfaceImpl::M2MInterfaceImpl(M2MInterfaceObserver& observer,
                                   const String &ep_name,
                                   const String &ep_type,
                                   const uint32_t l_time,
                                   const String &dmn,
                                   BindingMode mode ,                                   
                                   M2MInterface::NetworkStack stack,
                                   const String &con_addr)
: _observer(observer),
  _connection_handler(new M2MConnectionHandler(*this,stack)),
  _nsdl_interface(new M2MNsdlInterface(*this)),
  _current_state(0),
  _max_states( STATE_MAX_STATES ),
  _event_generated(false),
  _event_data(NULL),
  _endpoint_name(ep_name),
  _endpoint_type(ep_type),
  _domain( dmn),
  _life_time(l_time),
  _binding_mode(mode),
  _context_address(con_addr)
{    
    _nsdl_interface->create_endpoint(_endpoint_name,
                                     _endpoint_type,
                                     _life_time,
                                     _domain,
                                     (uint8_t)_binding_mode,
                                     _context_address);
}


M2MInterfaceImpl::~M2MInterfaceImpl()
{
    delete _nsdl_interface;
    delete _connection_handler;   
}

void M2MInterfaceImpl::bootstrap(M2MSecurity *security)
{
    // Transition to a new state based upon
    // the current state of the state machine
    M2MSecurityData* data = new M2MSecurityData();
    data->_object = security;
    BEGIN_TRANSITION_MAP                                    // - Current State -
        TRANSITION_MAP_ENTRY (STATE_BOOTSTRAP)              // state_idle
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state__bootstrap_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap_resource_created
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrapped
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_resource_created
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_registered
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_update_registration
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregister
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregistered
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_sending_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_sent
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_receiving_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_received
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_processing_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_processed
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_waiting
    END_TRANSITION_MAP(data)
}

void M2MInterfaceImpl::cancel_bootstrap()
{
//TODO: Do we need this ?
}

void M2MInterfaceImpl::register_object(M2MSecurity *security, const M2MObjectList &object_list)
{
    // Transition to a new state based upon
    // the current state of the state machine
    M2MRegisterData *data = new M2MRegisterData();
    data->_object = security;
    data->_object_list = object_list;
    BEGIN_TRANSITION_MAP                                    // - Current State -
        TRANSITION_MAP_ENTRY (STATE_REGISTER)               // state_idle
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state__bootstrap_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap_resource_created
        TRANSITION_MAP_ENTRY (STATE_REGISTER)               // state_bootstrapped
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_resource_created
        TRANSITION_MAP_ENTRY (STATE_REGISTER)               // state_registered
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_update_registration
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregister
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregistered
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_sending_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_sent
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_receiving_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_received
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_processing_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_processed
        TRANSITION_MAP_ENTRY (STATE_REGISTER)               // state_waiting
    END_TRANSITION_MAP(data)
}

void M2MInterfaceImpl::update_registration(const uint32_t lifetime)
{
    // Transition to a new state based upon
    // the current state of the state machine
    M2MUpdateRegisterData *data = new M2MUpdateRegisterData();
    data->_lifetime = lifetime;
    BEGIN_TRANSITION_MAP                                    // - Current State -
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)               // state_idle
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state__bootstrap_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap_resource_created
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrapped
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_resource_created
        TRANSITION_MAP_ENTRY (STATE_UPDATE_REGISTRATION)    // state_registered
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_update_registration
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregister
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregistered
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_sending_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_sent
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_receiving_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_received
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_processing_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_processed
        TRANSITION_MAP_ENTRY (STATE_UPDATE_REGISTRATION)    // state_waiting
    END_TRANSITION_MAP(data)
}

void M2MInterfaceImpl::unregister_object(M2MSecurity* /*security*/)
{
    // Transition to a new state based upon
    // the current state of the state machine
    BEGIN_TRANSITION_MAP                                // - Current State -
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_idle
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state__bootstrap_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrap_resource_created
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_bootstrapped
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_address_resolved
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_register_resource_created
        TRANSITION_MAP_ENTRY (STATE_UNREGSITER)             // state_registered
        TRANSITION_MAP_ENTRY (STATE_UNREGSITER)             // state_update_registration
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregister
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_unregistered
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_sending_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_sent
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_receiving_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_received
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_processing_coap_data
        TRANSITION_MAP_ENTRY (EVENT_IGNORED)                // state_coap_data_processed
        TRANSITION_MAP_ENTRY (STATE_UNREGSITER)             // state_waiting
    END_TRANSITION_MAP(NULL)

}

void M2MInterfaceImpl::coap_message_ready(uint8_t *data_ptr,
                                          uint16_t data_len,
                                          sn_nsdl_addr_s *address_ptr)
{
    if(_connection_handler->send_data(data_ptr,data_len,address_ptr)) {
        internal_event(STATE_SENDING_COAP_DATA);
    } else {
        _observer.error(M2MInterface::NetworkError);
        internal_event( STATE_IDLE);
    }
}

void M2MInterfaceImpl::client_registered()
{
    //Inform client is registered.
    _observer.object_registered();
    internal_event(STATE_REGISTERED);
}

void M2MInterfaceImpl::registration_error(uint8_t /*error_code*/)
{
    _observer.error(M2MInterface::NotRegistered);
    internal_event(STATE_IDLE);
}

void M2MInterfaceImpl::client_unregistered()
{
    _observer.object_unregistered(NULL);
    internal_event(STATE_UNREGSITERED);
}

void M2MInterfaceImpl::bootstrap_done(M2MSecurity *security_object)
{
    internal_event(STATE_BOOTSTRAPPED);
    _observer.bootstrap_done(security_object);
}

void M2MInterfaceImpl::bootstrap_error()
{
    _observer.error(M2MInterface::BootstrapFailed);
    internal_event(STATE_IDLE);
}

void M2MInterfaceImpl::coap_data_processed()
{
    internal_event(STATE_COAP_DATA_PROCESSED);
}

void M2MInterfaceImpl::data_available(uint8_t* data,
                                      uint16_t data_size,
                                      const M2MConnectionObserver::SocketAddress &address)
{
    ReceivedData *event = new ReceivedData();
    event->_data = data;
    event->_size = data_size;
    event->_address = &address;
    internal_event(STATE_COAP_DATA_RECEIVED, event);
}

void M2MInterfaceImpl::socket_error(uint8_t error_code)
{
    M2MInterface::Error error = M2MInterface::NetworkError;
    //TODO: remove hardcoding
    if(2 == error_code ) {
        error = M2MInterface::InvalidParameters;
    }
    _observer.error(error);
    internal_event(STATE_IDLE);
}

void M2MInterfaceImpl::address_ready(const M2MConnectionObserver::SocketAddress &address,
                                     M2MConnectionObserver::ServerType server_type,
                                     const uint16_t server_port)
{
    ResolvedAddressData *data = new ResolvedAddressData();
    data->_address = &address;
    data->_port = server_port;
    if( M2MConnectionObserver::Bootstrap == server_type) {
        internal_event(STATE_BOOTSTRAP_ADDRESS_RESOLVED, data);
    } else {
        internal_event(STATE_REGISTER_ADDRESS_RESOLVED, data);
    }
}

void M2MInterfaceImpl::data_sent()
{
    internal_event(STATE_COAP_DATA_SENT);
}

// state machine sits here.
void M2MInterfaceImpl::state_idle(EventData* /*data*/)
{
    // Handle Idle state here
    // Cleanup all resources, if necessary
}

void M2MInterfaceImpl::state_bootstrap( EventData *data)
{
    // Start with bootstrapping preparation
    bool success = false;
    if(data) {
        M2MSecurityData *event = (M2MSecurityData *)data;
        M2MSecurity *security = event->_object;
        if(security) {
            if(M2MSecurity::Bootstrap == security->server_type()) {
                String server_address = security->resource_value_string(M2MSecurity::M2MServerUri);
                String ip_address;
                uint16_t port;
                //TODO: provide API to set listen port
                uint16_t listen_port = 8000;
                if(server_address.compare(0,COAP.size(),COAP) == 0) {
                    server_address = server_address.substr(COAP.size(),
                                                           server_address.size()-COAP.size());
                    //TODO: Implement function for find_last_of()
                    int colonFound = 10;//server_address.find_last_of( ":" );
                    if(colonFound != -1) {
                       ip_address = server_address.substr(0,colonFound);
                       port = atoi(server_address.substr(colonFound+1,
                                                         server_address.size()-ip_address.size()).c_str());

                       // If bind and resolving server address succeed then proceed else
                       // return error to the application and go to Idle state.
                       if( _connection_handler->bind_connection(listen_port) &&
                          _connection_handler->resolve_server_address(ip_address,
                                                                      port,
                                                                      M2MConnectionObserver::Bootstrap)) {
                           success = true;
                       }
                    }
                }
            }
        }
    }
    if(!success) {
        _observer.error(M2MInterface::InvalidParameters);
        internal_event(STATE_IDLE);
    }
}

void M2MInterfaceImpl::state_bootstrap_address_resolved( EventData *data)
{
    ResolvedAddressData *event = (ResolvedAddressData *)data;
    sn_nsdl_addr_s address;

    M2MInterface::NetworkStack stack = event->_address->_stack;

    if(M2MInterface::LwIP_IPv4 == stack) {
        address.type = SN_NSDL_ADDRESS_TYPE_IPV4;
        address.addr_len = 4;
    } else if((M2MInterface::LwIP_IPv6 == stack) ||
              (M2MInterface::Nanostack_IPv6 == stack)) {
        address.type = SN_NSDL_ADDRESS_TYPE_IPV6;
        address.addr_len = 16;
    }
    address.port = event->_port;
    address.addr_ptr = (uint8_t*)event->_address->_address;
    address.addr_len = event->_address->_length;
    if(_nsdl_interface->create_bootstrap_resource(&address)) {
       internal_event(STATE_BOOTSTRAP_RESOURCE_CREATED);
    } else{
        // If resource creation fails then inform error to application
        _observer.error(M2MInterface::InvalidParameters);
        internal_event(STATE_IDLE);
    }
}

void M2MInterfaceImpl::state_bootstrap_resource_created( EventData */*data*/)
{
}

void M2MInterfaceImpl::state_bootstrapped( EventData */*data*/)
{
}

void M2MInterfaceImpl::state_register( EventData *data)
{
    // Start with registration preparation
    bool success = false;
    if(data) {
        M2MRegisterData *event = (M2MRegisterData *)data;
        M2MSecurity *security = event->_object;        
        if(security) {
            if(M2MSecurity::M2MServer == security->server_type()) {
                if(_nsdl_interface->create_nsdl_list_structure(event->_object_list)) {
                    // If the nsdl resource structure is created successfully
                    String server_address = security->resource_value_string(M2MSecurity::M2MServerUri);
                    String ip_address;
                    uint16_t port;
                    //TODO: provide API to set listen port
                    uint16_t listen_port = 8000;
                    if(server_address.compare(0,COAP.size(),COAP) == 0) {
                        server_address = server_address.substr(COAP.size(),
                                                               server_address.size()-COAP.size());
                        //TODO: Implement function for find_last_of()
                        int colonFound = 10;//server_address.find_last_of( ":" );
                        if(colonFound != -1) {
                           ip_address = server_address.substr(0,colonFound);
                           port = atoi(server_address.substr(colonFound+1,
                                                             server_address.size()-ip_address.size()).c_str());


                           // If bind and resolving server address succeed then proceed else
                           // return error to the application and go to Idle state.
                           if( _connection_handler->bind_connection(listen_port) &&
                              _connection_handler->resolve_server_address(ip_address,
                                                                          port,
                                                                          M2MConnectionObserver::M2MServer)) {
                               success = true;
                           }
                        }
                    }
                }
            }
        }
    }
    if(!success) {
        _observer.error(M2MInterface::InvalidParameters);
        internal_event(STATE_IDLE);
    }
}

void M2MInterfaceImpl::state_register_address_resolved( EventData *data)
{
    if(data) {
        ResolvedAddressData *event = (ResolvedAddressData *)data;

        sn_nsdl_addr_type_e address_type = SN_NSDL_ADDRESS_TYPE_IPV6;

        M2MInterface::NetworkStack stack = event->_address->_stack;

        if(M2MInterface::LwIP_IPv4 == stack) {
            address_type = SN_NSDL_ADDRESS_TYPE_IPV4;
        } else if((M2MInterface::LwIP_IPv6 == stack) ||
                  (M2MInterface::Nanostack_IPv6 == stack)) {
            address_type = SN_NSDL_ADDRESS_TYPE_IPV6;
        }

        if(_nsdl_interface->send_register_message((uint8_t*)event->_address->_address,event->_port, address_type)) {
           internal_event(STATE_REGISTER_RESOURCE_CREATED);
        } else{
            // If resource creation fails then inform error to application
            _observer.error(M2MInterface::InvalidParameters);
            internal_event(STATE_IDLE);
        }
    }
}

void M2MInterfaceImpl::state_register_resource_created( EventData */*data*/)
{

}

void M2MInterfaceImpl::state_registered( EventData */*data*/)
{

}

void M2MInterfaceImpl::state_update_registration( EventData *data)
{
    // Start with registration preparation
    bool success = false;
    if(data) {
        M2MUpdateRegisterData *event = (M2MUpdateRegisterData *)data;
        success = _nsdl_interface->send_update_registration(event->_lifetime);

    }
    if(!success) {
        _observer.error(M2MInterface::InvalidParameters);
        internal_event(STATE_IDLE);
    }
}

void M2MInterfaceImpl::state_unregister( EventData */*data*/)
{
    if(_nsdl_interface->send_unregister_message()) {
       internal_event(STATE_SENDING_COAP_DATA);
    } else {
        _observer.error(M2MInterface::NotRegistered);
        internal_event(STATE_IDLE);
    }
}

void M2MInterfaceImpl::state_unregistered( EventData */*data*/)
{
    internal_event(STATE_IDLE);
}

void M2MInterfaceImpl::state_sending_coap_data( EventData */*data*/)
{
}

void M2MInterfaceImpl::state_coap_data_sent( EventData */*data*/)
{
    if(_connection_handler->listen_for_data()) {
        internal_event(STATE_RECEIVING_COAP_DATA);
    } else {
        _observer.error(M2MInterface::NetworkError);
        internal_event(STATE_IDLE);
    }
}

void M2MInterfaceImpl::state_receiving_coap_data( EventData */*data*/)
{
}

void M2MInterfaceImpl::state_coap_data_received( EventData *data)
{
    if(data) {
        ReceivedData *event = (ReceivedData*)data;
        sn_nsdl_addr_s *address = (sn_nsdl_addr_s *)malloc(sizeof(sn_nsdl_addr_s));
        memset(address,0,sizeof(sn_nsdl_addr_s));

        M2MInterface::NetworkStack stack = event->_address->_stack;

        if(M2MInterface::LwIP_IPv4 == stack) {
            address->type = SN_NSDL_ADDRESS_TYPE_IPV4;
            address->addr_len = 4;
        } else if((M2MInterface::LwIP_IPv6 == stack) ||
                  (M2MInterface::Nanostack_IPv6 == stack)) {
            address->type = SN_NSDL_ADDRESS_TYPE_IPV6;
            address->addr_len = 16;
        }
        address->port = event->_address->_port;
        address->addr_ptr = (uint8_t*)event->_address->_address;

        // Process received data
        if(_nsdl_interface->process_received_data(event->_data,
                                                  event->_size,
                                                  address)) {
            internal_event(STATE_PROCESSING_COAP_DATA);
        } else {
            _observer.error(M2MInterface::ResponseParseFailed);
            internal_event(STATE_IDLE);
        }
    }
}

void M2MInterfaceImpl::state_processing_coap_data( EventData */*data*/)
{

}

void M2MInterfaceImpl::state_coap_data_processed( EventData */*data*/)
{
    internal_event(STATE_WAITING);
}

void M2MInterfaceImpl::state_waiting( EventData */*data*/)
{
}

// generates an external event. called once per external event
// to start the state machine executing
void M2MInterfaceImpl::external_event(uint8_t new_state,
                                     EventData* p_data)
{
    // if we are supposed to ignore this event
    if (new_state == EVENT_IGNORED) {
        // just delete the event data, if any
        if (p_data) {
            delete p_data;
            p_data = NULL;
        }
    }
    else {
        // generate the event and execute the state engine
        internal_event(new_state, p_data);
    }
}

// generates an internal event. called from within a state
// function to transition to a new state
void M2MInterfaceImpl::internal_event(uint8_t new_state,
                                      EventData* p_data)
{
    _event_data = p_data;
    _event_generated = true;
    _current_state = new_state;
    state_engine();
}

// the state engine executes the state machine states
void M2MInterfaceImpl::state_engine (void )
{
    EventData* p_data_temp = NULL;

    // while events are being generated keep executing states
    while (_event_generated) {
        p_data_temp = _event_data;  // copy of event data pointer
        _event_data = NULL;       // event data used up, reset ptr
        _event_generated = false;  // event used up, reset flag

        assert(_current_state < _max_states);

        state_function( _current_state, p_data_temp );

        // if event data was used, then delete it
        if (p_data_temp) {
            delete p_data_temp;
            p_data_temp = NULL;
        }
    }
}

void M2MInterfaceImpl::state_function( uint8_t current_state, EventData* data )
{
    switch( current_state ) {
    case STATE_IDLE:
            M2MInterfaceImpl::state_idle(data);
            break;
        case STATE_BOOTSTRAP:
            M2MInterfaceImpl::state_bootstrap(data);
            break;
        case STATE_BOOTSTRAP_ADDRESS_RESOLVED:
            M2MInterfaceImpl::state_bootstrap_address_resolved(data);
            break;
        case STATE_BOOTSTRAP_RESOURCE_CREATED:
            M2MInterfaceImpl::state_bootstrap_resource_created(data);
            break;
        case STATE_BOOTSTRAPPED:
            M2MInterfaceImpl::state_bootstrapped(data);
            break;
        case STATE_REGISTER:
            M2MInterfaceImpl::state_register(data);
            break;
        case STATE_REGISTER_ADDRESS_RESOLVED:
            M2MInterfaceImpl::state_register_address_resolved(data);
            break;
        case STATE_REGISTER_RESOURCE_CREATED:
            M2MInterfaceImpl::state_register_resource_created(data);
            break;
        case STATE_REGISTERED:
            M2MInterfaceImpl::state_registered(data);
            break;
        case STATE_UPDATE_REGISTRATION:
            M2MInterfaceImpl::state_update_registration(data);
            break;
        case STATE_UNREGSITER:
            M2MInterfaceImpl::state_unregister(data);
            break;
        case STATE_UNREGSITERED:
            M2MInterfaceImpl::state_unregistered(data);
            break;
        case STATE_SENDING_COAP_DATA:
            M2MInterfaceImpl::state_sending_coap_data(data);
            break;
        case STATE_COAP_DATA_SENT:
            M2MInterfaceImpl::state_coap_data_sent(data);
            break;
        case STATE_RECEIVING_COAP_DATA:
            M2MInterfaceImpl::state_receiving_coap_data(data);
            break;
        case STATE_COAP_DATA_RECEIVED:
            M2MInterfaceImpl::state_coap_data_received(data);
            break;
        case STATE_PROCESSING_COAP_DATA:
            M2MInterfaceImpl::state_processing_coap_data(data);
            break;
        case STATE_COAP_DATA_PROCESSED:
            M2MInterfaceImpl::state_coap_data_processed(data);
            break;
        case STATE_WAITING:
            M2MInterfaceImpl::state_waiting(data);
            break;
    }
}