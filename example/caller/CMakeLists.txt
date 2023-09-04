
set(SRC_LISt calluservice.cc ../user.pb.cc)
# aux_source_directory(. SRC_LISt)
# aux_source_directory(../user.pb.cc USER_LIST)

add_executable(caller ${SRC_LISt})

target_link_libraries(caller rpc protobuf)
