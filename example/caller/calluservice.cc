#include<iostream>
#include"rpcApplication.h"
#include"user.pb.h"
#include"rpcChannel.h"
#include"rpcController.h"

int main(int argc,char** argv)
{
    //初始化框架
    RpcApplication::Init(argc,argv);

    fixbug::UserServiceRpc_Stub stub(new MyRpcChannel());
    fixbug::LoginRequest request;
    
    request.set_name("zhang san");
    request.set_pwd("12345687");

    fixbug::LoginResponse response;
    RpcController controller;

    // 发起rpc方法调用
    stub.Login(&controller,&request,&response,nullptr);


    // 一次rpc调用完成，读调用的结果
    if (controller.Failed())
    {
        std::cout << "rpc 方法调用失败，" << controller.ErrorText() << std::endl;
    }
    else
    {
        if (0 == response.result().errcode())
        {
            std::cout << "rpc login response success:" << response.sucess() << std::endl;
        }
        else
        {
            std::cout << "rpc login response error:" << response.result().errmsg() << std::endl;
        }
    }

    return 0;
}






