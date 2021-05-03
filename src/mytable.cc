#include <inttypes.h>
#include "xchain/xchain.h"
#include "thetable.h"
#include "mytable.pb.h"
#include "mytable.h"
#include <iostream>

using namespace std;

//初始化
DEFINE_METHOD(MyTable, initialize) {
    xchain::Context* ctx = self.context();
    ctx->ok("initialize succeed");
}



DEFINE_METHOD(MyTable, findname) {
    xchain::Context* ctx = self.context();
    const std::string& name = ctx->arg("name");
    thetable ent;
    if (self.get_thetable().find({{"name", name}}, &ent)) {
        std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
        ctx->ok(obj);
        return;
    }
    ctx->error("can not find " + name);
}

DEFINE_METHOD(MyTable, add) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    cout << __func__ << "[" << __LINE__ << "] " << "id=" << id << endl;

    thetable ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name.c_str());
    self.get_thetable().put(ent);

    ctx->ok(ent.to_string());
}
