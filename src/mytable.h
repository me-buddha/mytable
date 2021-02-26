#include "xchain/xchain.h"
#include "mytable.pb.h"
#include "thetable.h"

struct MyTable : public xchain::Contract {
public:
    MyTable(): _thetable(this->context(), "thetable") {}

private:
    xchain::cdt::Table<thetable> _thetable;

public:
    decltype(_thetable)& get_thetable() {
        return _thetable;
    }
};
