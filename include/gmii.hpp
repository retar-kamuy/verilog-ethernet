#ifndef GMII_HPP_
#define GMII_HPP_
#include <systemc.h>
#include <vector>
#include <reset.hpp>
// #include <join.hpp>

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))

template <typename TYPE, std::size_t SIZE>
std::size_t array_length(const TYPE (&)[SIZE]) {
    return SIZE;
}

class GmiiFrame {
 private:
    const char *name;
    std::vector<unsigned char> data;
    std::vector<int> error;
    int sim_time_start;
    int sim_time_sfd;
    int sim_time_end;
    // auto tx_complete;

 public:
    explicit GmiiFrame(const GmiiFrame &_data) {
        // data = new unsigned char[sizeof(_data.data)];
        data = _data.data;
        error = _data.error;
        sim_time_start = _data.sim_time_start;
        sim_time_sfd = _data.sim_time_start;
        sim_time_end = _data.sim_time_end;
        // tx_complete = _data.tx_complete;
    }

    // GmiiFrame(unsigned char *_data, int *_error, auto _tx_complete) {
    GmiiFrame(std::vector<unsigned char> _data, std::vector<int> _error) {
        std::cout << "_data.size()=" << _data.size() << std::endl;
        for (const auto &d : _data) {
            std::cout << (int)d << ' ' << std::endl;
        }
        std::cout << "_error.size()=" << _error.size() << std::endl;
        for (const auto &e : _error) {
            std::cout << e << ' ' << std::endl;
        }
        data.resize(_data.size());
        data = _data;
        error.resize(_error.size());
        error = _error;
        // tx_complete = _tx_complete;
    }

    const char *repr(void) {
        std::cout << "test=" << data.size() << std::endl;
        for (const auto &d : data) {
            if(data.size())
            std::cout << static_cast<int>(d) << ' ' << std::endl;
        }
        std::string str_data = (std::string)name;
        str_data += "[";
        int datas = 0;
        for (const auto &d : data) {
            str_data += ((std::to_string)(static_cast<int>(d))+", ").c_str();
        }
        // str_data[3] = NULL;
        str_data += "]";
        std::cout << "data=" << str_data << std::endl;
        //std::to_string(new_state);
        // static std::string test = (std::string)name+"(data="+static_cast<int>(data);
        //return ("test").c_str();
        static std::string str =(std::string)("test");
        return (str_data).c_str();
    }
};

class GmiiSource:
    public Reset
{
 private:
    bool active = 0;
    // self.queue = Queue()
    // self.dequeue_event = Event()
    // self.current_frame = None
    // self.idle_event = Event()
    // self.idle_event.set()
    // self.active_event = Event()

    int ifg = 12;
    bool mii_mode = 0;

    int queue_occupancy_bytes = 0;
    int queue_occupancy_frames = 0;

    int queue_occupancy_limit_bytes = -1;
    int queue_occupancy_limit_frames = -1;

    int width = 8;
    int byte_width = 1;

    const char* name = "GmiiSource";
    // sc_in<bool> clock;
    // sc_in<unsigned char> data;
    // sc_in<bool> er;
    // sc_in<bool> dv;
    // sc_in<bool> enable;
    // sc_in<bool> mii_select;

    sc_signal<bool> _reset_signal;
    // sc_signal<bool> reset_active_level;
 public:
    void full(void);
    void send(GmiiFrame frame);

    SC_CTOR(GmiiSource):
        Reset("Reset")
    {
        SC_REPORT_INFO(name, "GMII source");
        // reset_active_level = 1;
        // active_level(reset_active_level);
    }

    ~GmiiSource() {
    }
};

#endif  // GMII_HPP_
