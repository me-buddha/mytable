# 测试表中是否可以存在嵌套字段, 最终结构是不行。


```bash
#生成协议源文件
cd src/
protoc --cpp_out=. mytable.proto

cd ..
xdev build


xchain-cli wasm deploy --account XC1234567890111111@xuper --cname mytable --fee 5000000 --runtime c ../mytable/mytable.wasm

xchain-cli wasm invoke --fee 11000 mytable --method get -a '{"name":"myname"}'
xchain-cli wasm invoke --fee 11000 mytable --method set -a '{"id":"1","name":"myname","address":{"label":"myhome","address":"myaddress1"}}'

xchain-cli wasm invoke --fee 11000 mytable --method size
xchain-cli wasm invoke --fee 11000 mytable --method clear


xchain-cli wasm upgrade --account XC1234567890111111@xuper --cname mytable --fee 5000000 ../mytable/mytable.wasm

```
