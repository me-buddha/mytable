#include <inttypes.h>
#include "xchain/xchain.h"
#include "mytable.pb.h"
#include "thetable.h"
#include <iostream>

using namespace std;

//data mytableing
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

//初始化
DEFINE_METHOD(MyTable, initialize) {
    xchain::Context* ctx = self.context();
    ctx->ok("initialize succeed");
}

DEFINE_METHOD(MyTable, count) {
    xchain::Context* ctx = self.context();
    
    auto it = self.get_thetable().scan({{"id","1"}});
    int i = 0;
    std::string re ;
    while(it->next()) {
        thetable ent;
        if (!it->get(&ent))
            break;

        re += ent.to_string();
        i += 1;
    }
    // if (it->error()) 
    //     ctx->ok(std::to_string(i) + " ++> " + re + " > " + it->error(true));
    ctx->ok(std::to_string(i) + " -> " + re + " > " + it->error(true));
}

DEFINE_METHOD(MyTable, findid) {
    xchain::Context* ctx = self.context();
    const std::string& id = ctx->arg("id");
    thetable ent;
    if (self.get_thetable().find({{"id", id}}, &ent)) {
        std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
        ctx->ok(obj);
        return;
    }
    ctx->error("can not find " + id);
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

DEFINE_METHOD(MyTable, del) {
    xchain::Context* ctx = self.context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    thetable ent;
    ent.set_id(std::stoll(id));
    ent.set_name(name.c_str());
    self.get_thetable().del(ent);

    ctx->ok(ent.to_string());
}

// DEFINE_METHOD(MyTable, scan) {
//     xchain::Context* ctx = self.context();
//     const std::string& name = ctx->arg("name");
//     auto it = self.get_thetable().scan({{"name", name}});
//     thetable ent;
//     int i = 0;
//     std::string re ;
//     std::map<std::string, bool> kv;
//     while(it->next()) {
//         if (it->get(&ent)) {
//             std::string obj ; obj += "{" + std::to_string(ent.id()) + "," + ent.name() + "}";
//             re += obj;

//             if (kv.find(ent.name()) != kv.end()) {
//                 ctx->error("find duplicated key");
//                 return;
//             }
//             kv[ent.name()] = true;
//             i += 1;
//         } else {
//             std::cout << "get error" << std::endl;
//         }
//     }
//     std::cout << i << std::endl;
//     if (it->error()) {
//         std::cout << it->error(true) << std::endl;
//     }
//     re += "}";
//     ctx->ok(std::to_string(i) + " -> " + re);
// }



DEFINE_METHOD(MyTable, scan) {
    xchain::Context* ctx = self.context();
    // auto it = self.get_thetable().scan({});
    // auto it = self.get_thetable().scan({{"id", "1"}});
    // int i = 0;
    // while(it->next()) 
    //     i++;
    // ctx->ok(std::to_string(i));

    auto it = self.get_thetable().scan({{"name", ctx->arg("name").c_str()}});
    int i = 0;
    // std::string ret;
    while(it->next()) {
        thetable ent;
        if (it->get(&ent)) {
            std::cout << __LINE__ << " run" << std::endl;
            i++;
            // ret += ent.to_string();
        }
        else
            std::cout << __LINE__ << " get error : " << it->error(true) << std::endl;
    }
    // ctx->ok(std::to_string(i) + ret);
    ctx->ok(std::to_string(i));
}

