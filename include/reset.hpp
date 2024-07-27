#ifndef RESET_HPP_
#define RESET_HPP_

#include <systemc.h>

SC_MODULE(Reset) {
    sc_in<bool> reset_signal;
    sc_in<bool> active_level;

    bool _local_reset = 0;
    bool _ext_reset = 0;
    bool _reset_state = 1;

    void _init_reset(bool reset_signal, bool active_level);
    void assert_reset(bool val);
    void _update_reset(void);
    void _handle_reset(bool state);
    void _run_reset(void);

    SC_CTOR(Reset) {
        // サブモジュールのインスタンス
        // サブもジュールの信号接続
        // プロセス登録
        // 静的センシティビティ設定
        // ユーザ定義の各種設定
        SC_METHOD(_run_reset);
            sensitive << reset_signal;
    }

    // デストラクタ
    ~Reset() {
    }
};

#endif  // RESET_HPP_
