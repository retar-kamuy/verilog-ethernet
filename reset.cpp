#include "include/reset.hpp"

void Reset::_init_reset(bool _reset_signal, bool _active_level) {
    _local_reset = 0;
    _ext_reset = 0;
    _reset_state = 1;

    _run_reset(_reset_signal, _active_level);

    _update_reset();
}

void Reset::assert_reset(bool val) {
    _local_reset = val;
    _update_reset();
}

void Reset::_update_reset(void) {
    bool new_state = _local_reset | _ext_reset;
    SC_REPORT_INFO(
        name,
        ("new_state="+std::to_string(new_state)+",_reset_state="+std::to_string(_reset_state)).c_str()
    );
    if (_reset_state != new_state) {
        _reset_state = new_state;
        _handle_reset(new_state);
    }
}

void Reset::_run_reset(bool _reset_signal, bool _active_level) {
    reset_signal = _reset_signal;
    active_level = _active_level;
}

void Reset::_run_reset_method(void) {
    std::cout << "Info: " << name << ": " << sc_time_stamp() << ": ";
    std::cout << "reset_signal=" << reset_signal;
    std::cout << ", active_level=" << active_level << std::endl;
    if (reset_signal) {
        next_trigger(reset_signal.negedge_event());
        std::cout << "Info: " << name << ": " << sc_time_stamp() << ": ";
        std::cout << "Negative edge detect" << std::endl;
        _ext_reset = !active_level;
        _update_reset();
    } else {
        next_trigger(reset_signal.posedge_event());
        std::cout << "Info: " << name << ": " << sc_time_stamp() << ": ";
        std::cout << "positive edge detect" << std::endl;
        _ext_reset = active_level;
        _update_reset();
    }
}