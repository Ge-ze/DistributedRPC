#include "test.pb.h"
#include <iostream>

using namespace fixbug;


int main()
{
    LoginRequest reqa;
    reqa.set_name("zhagnsna");
    reqa.set_pwd("123");

    std::cout<<"-----------------protobuf序列化-------------\n";
    //序列化
    std::string send_str;
    if(reqa.SerializeToString(&send_str))
    {
        std::cout<<send_str<<std::endl;

    }

    std::cout<<"-----------------protobuf反序列化-------------\n";
    //反序列化
    LoginRequest reqb;
    if(reqb.ParseFromString(send_str))
    {
        std::cout<<reqb.name()<<std::endl;
        std::cout<<reqb.pwd()<<std::endl;
    }

    std::cout<<"-----------------protobuf序列化-------------\n";

    GetFriendListResponse rspa;

    ResultCode *rc = rspa.mutable_result();
    rc->set_errcode(0);
    
    User *user1 = rspa.add_friendlist();
    user1->set_name("zhangsan");
    user1->set_age(20);
    user1->set_sex(User::MAN);

    User *user2 = rspa.add_friendlist();
    user2->set_name("lihuahu");
    user2->set_age(18);
    user2->set_sex(User::WOMAN);

    for(int i = 0; i < 5; ++i)
    {
        User *user = rspa.add_friendlist();
        std::string name = "zhangsan";
        name += i;
        user->set_name(name.c_str());
        user->set_age(20);
        user->set_sex(User::MAN);

        //delete user;
    }
    std::cout<<"friendlist size: "<<rspa.friendlist_size()<<std::endl;

    // delete rc;
    // delete user1;
    // delete user2;
    std::string send_friendliststr;
    rspa.SerializeToString(&send_friendliststr);
    std::cout<<send_friendliststr<<std::endl;


    std::cout<<"-----------------protobuf反序列化-------------\n";

    GetFriendListResponse rspb;
    if(rspb.ParseFromString(send_friendliststr))
    {
        std::cout<<"errcode:"<<rspb.result().errcode()<<std::endl;
        for(int i = 0; i < rspb.friendlist_size(); ++i)
        {
            User user = rspb.friendlist(i);
            std::cout<<user.name()<<" "<<user.age()<<" "<<user.sex()<<std::endl;
        }         
    }
     





    return 0;
}