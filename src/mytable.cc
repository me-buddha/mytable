#include <inttypes.h>
#include "xchain/xchain.h"
#include "xchain/table/types.h"
#include "xchain/table/table.tpl.h"
#include "mytable.pb.h"
#include "xchain/json/json.h"
#include "xchain/contract.pb.h"

#include <string>
using namespace std ;

#define mycout cout << __FILE__ << "(" << __LINE__ << ") [" << __FUNCTION__ << "] " 


// 1. rowkey can not be same with index
struct myinfo: public mytable::MyInfo {
    DEFINE_ROWKEY(id);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();


    xchain::json to_json() {
        xchain::json j = {
            {"id", id()},
            {"name", name()},
        };

        return j;
    }
};

struct myaddress: public mytable::MyAddress {
    DEFINE_ROWKEY(id, address);
    DEFINE_INDEX_BEGIN(1)
        DEFINE_INDEX_ADD(0, id)
    DEFINE_INDEX_END();

    xchain::json to_json() {
        xchain::json j = {
            {"id", id()},
            {"address", address()},
        };

        return j;
    }
};

//data mytableing
struct MyInfo : public xchain::Contract {
public:
    MyInfo():
        _myinfo(this->context(), "myinfo"),
        _myaddress(this->context(), "myaddress"),
        
        ctx(context())
    {}


private:
    xchain::cdt::Table<myinfo> _myinfo;
    xchain::cdt::Table<myaddress> _myaddress;

    xchain::Context* ctx;

public:
    decltype(_myinfo)& get_info()           {     return _myinfo;     }
    decltype(_myaddress)& get_address()     {     return _myaddress;  }

    void _log_error(const string&, const string&, const int, const string& ="") ;
    void _log_error(const string&, const string&, const int, const string&, const xchain::json&) ;
    void _log_ok(const string&, const string&, const int, const string& ="") ;
    void _log_ok(const string&, const string&, const int, const string&, const xchain::json&) ;

    void initialize();
    void get();
    void set();
    void del();
    void scan();
    void size();
    void clear();
};



void MyInfo::_log_error(const string& file, const string& fun, const int line, const string& message) {
    cout << file << "(" << line << ") [" << fun << "] " << message << endl;
    xchain::json ret ;
    ret["result"] = false;
    ret["message"] = message;

    ctx->ok(ret.dump());
}


void MyInfo::_log_error(const string& file, const string& fun, const int line, const string& message, const xchain::json& j) {
    cout << file << "(" << line << ") [" << fun << "] " << j.dump() << endl;
    xchain::json ret ;
    ret["result"] = false;
    ret["message"] = message;
    ret["value"] = j;
    if(j.is_array())
        ret["size"] = j.size();

    ctx->ok(ret.dump());
}

void MyInfo::_log_ok(const string& file, const string& fun, const int line, const string& message) {
    cout << file << "(" << line << ") [" << fun << "] " << message << endl;
    xchain::json ret ;
    ret["result"] = true;
    ret["message"] = message;
    ctx->ok(ret.dump());
}

void MyInfo::_log_ok(const string& file, const string& fun, const int line, const string& message, const xchain::json& j) {
    cout << file << "(" << line << ") [" << fun << "] " << j.dump() << endl;
    xchain::json ret ;
    ret["result"] = true;
    ret["message"] = message;
    ret["value"] = j;
    if(j.is_array())
        ret["size"] = j.size();

    ctx->ok(ret.dump());
}

//初始化
void MyInfo::initialize() {
    xchain::Context* ctx = context();
    ctx->ok("initialize succeed");
}

void MyInfo::get() {
    xchain::Context* ctx = context();
    const std::string& id = ctx->arg("id");
    myinfo info;
    if (get_info().find({{"id", id}}, &info)) {
        std::string re = "{";
        re += std::to_string(info.id()) + ",";
        re += info.name() + "}";
        ctx->ok(re);
        return;
    }
    ctx->error("can not find " + id);
}

void MyInfo::set() {
    xchain::Context* ctx = context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    auto it = get_address().scan({{"id",id}});
    while(it->next() ) {
        myaddress ent;
        if (!it->get(&ent) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "myaddress table get failure : " + it->error(true) );
            return;
        }

        if( !get_address().del(ent) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "delete myaddress failure ." );
            return;
        }

        _log_ok(__FILE__, __FUNCTION__, __LINE__, "delete myaddress success ." );
    }

    myaddress address ;
    address.set_id(std::stoll(id));
    address.set_address("111");
    get_address().put(address);


    myinfo info;
    info.set_id(std::stoll(id));
    info.set_name(name.c_str());
    get_info().put(info);



    _log_ok(__FILE__, __FUNCTION__, __LINE__, "create", info.to_json());

}

void MyInfo::del() {
    xchain::Context* ctx = context();
    const std::string& id= ctx->arg("id");
    const std::string& name = ctx->arg("name");

    myinfo info;
    info.set_id(std::stoll(id));
    info.set_name(name.c_str());
    get_info().del(info);

    std::string re = "{";
    re += id + ",";
    re += name + "} del success";
    ctx->ok(re);
}

void MyInfo::scan() {
    xchain::Context* ctx = context();
    const std::string& id = ctx->arg("id");

    xchain::json ja ;
    auto it = get_info().scan({{"id", id}});
    while(it->next() ) {
        myinfo ent;
        if (!it->get(&ent) ) {
            _log_error(__FILE__, __FUNCTION__, __LINE__, "myinfo table get failure : " + it->error(true) );
            return;
        }

        ja.push_back(ent.to_json());
    }

    _log_ok(__FILE__, __FUNCTION__, __LINE__, "scan", ja);
}

void MyInfo::size() {
    xchain::Context* ctx = context();
    auto it = get_info().scan({});
    int i = 0;
    std::string re = "{";
    while(it->next()) {
        myinfo info;
        if (it->get(&info)) {
            std::string obj = "{";
            obj += std::to_string(info.id()) + ",";
            obj += info.name() + "}";
            re += obj;
            i += 1;
        } else {
            std::cout << "get error" << std::endl;
        }
    }
    std::cout << i << std::endl;
    if (it->error()) {
        std::cout << it->error(true) << std::endl;
    }
    re += "}";
    ctx->ok(std::to_string(i) + " -> " + re);
}

void MyInfo::clear() {
    xchain::Context* ctx = context();
    auto it = get_info().scan({});
    int i = 0;
    while(it->next()) {
        myinfo info;
        if (it->get(&info)) {
            get_info().del(info);
            i += 1;
        } else {
            std::cout << "get error" << std::endl;
        }
    }
    std::cout << i << std::endl;
    if (it->error()) {
        std::cout << it->error(true) << std::endl;
    }
    ctx->ok(std::to_string(i));
}


DEFINE_METHOD(MyInfo, initialize)     { self.initialize();      }
DEFINE_METHOD(MyInfo, get)            { self.get();             }
DEFINE_METHOD(MyInfo, set)            { self.set();             }
DEFINE_METHOD(MyInfo, del)            { self.del();             }
DEFINE_METHOD(MyInfo, size)           { self.size();            }
DEFINE_METHOD(MyInfo, scan)           { self.scan();            }
DEFINE_METHOD(MyInfo, clear)          { self.clear();           }
