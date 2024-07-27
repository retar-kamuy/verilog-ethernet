#include "include/reset.hpp"

void Reset::_init_reset(bool reset_signal, bool active_level) {
    _local_reset = 0;
    _ext_reset = 0;
    _reset_state = 1;

    _update_reset();
}

void Reset::assert_reset(bool val) {
    _local_reset = val;
    _update_reset();
}

void Reset::_update_reset(void) {
    const char* id = "_update_reset";
    bool new_state = _local_reset | _ext_reset;
    SC_REPORT_INFO(id, ("new_state=" + std::to_string(new_state) + ", _reset_state=" + std::to_string(_reset_state)).c_str());
    if (_reset_state != new_state) {
        _reset_state = new_state;
        _handle_reset(new_state);
    }
}

void Reset::_handle_reset(bool state) {}

void Reset::_run_reset(void) {
    if (reset_signal) {
        next_trigger(reset_signal.negedge_event());
        _ext_reset = !active_level;
        _update_reset();
    } else {
        next_trigger(reset_signal.posedge_event());
        _ext_reset = active_level;
        _update_reset();
    }
}
