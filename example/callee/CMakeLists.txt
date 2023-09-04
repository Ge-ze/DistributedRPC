
set(SRC_LISt userservice.cc ../user.pb.cc)
# aux_source_directory(. SRC_LISt)
# aux_source_directory(../user.pb.cc USER_LIST)

add_executable(provider ${SRC_LISt})

target_link_libraries(provider rpc protobuf)
