# 测试主键是否起作用


```bash

#关闭原来的链
pkill xchain
rm -rvf data/blockchain/

#创建链，后台启动链
xchain-cli createChain
nohup xchain --vm ixvm &


#创建合约账户
xchain-cli account new --account 1234567890111111 --fee 1000
xchain-cli transfer --to XC1234567890100000@xuper --amount 10000000000 --keys data/keys

xchain-cli account new --account 1234567890222222 --fee 1000
xchain-cli transfer --to XC1234567890222222@xuper --amount 10000000000 --keys data/keys

```


> protobuf 版本注意只能使用 3.7.1， fuck， 坑。

```bash
#生成协议源文件
cd src/
protoc --cpp_out=. mytable.proto

cd ..
xdev build


xchain-cli wasm deploy --account XC1234567890100000@xuper --cname mytable --fee 5000000 --runtime c ../mytable/mytable.wasm

xchain-cli wasm upgrade --account XC1234567890100000@xuper --cname mytable --fee 5000000 ../mytable/mytable.wasm


xchain-cli wasm invoke --fee 1000000 mytable --method findid -a '{"id":"44733"}'
xchain-cli wasm invoke --fee 1000000 mytable --method findid -a '{"id":"2"}'
xchain-cli wasm invoke --fee 1000000 mytable --method findname -a '{"name":"myname"}'
date
xchain-cli wasm invoke --fee 1000000000000 mytable --method scan -a '{"name":"myname"}'
date
xchain-cli wasm invoke --fee 1000000 mytable --method scan -a '{"id":"1"}'
xchain-cli wasm invoke --fee 1000000 mytable --method scan
xchain-cli wasm invoke --fee 1000000 mytable --method add -a '{"id": "1", "name":"myname"}'
xchain-cli wasm invoke --fee 1000000 mytable --method add -a '{"id": "2", "name":"myname"}'
xchain-cli wasm invoke --fee 1000000 mytable --method add -a '{"id": "3", "name":"myname"}'

xchain-cli wasm invoke --fee 1000000 mytable --method count
xchain-cli wasm invoke --fee 1000000 mytable --method clear


xchain-cli wasm upgrade --account XC1234567890100000@xuper --cname mytable --fee 5000000 ../mytable/mytable.wasm


xchain-cli wasm invoke --fee 1000000 mytable  --account XC1234567890100000@xuperv --method findname -a '{"name":"myname"}'

```
